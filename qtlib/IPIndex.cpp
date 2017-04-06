// IPIndex.cpp: Implementierung der Klasse CIPIndex.
//
//////////////////////////////////////////////////////////////////////

#include "IPIndex.h"
#include <QMessageBox>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef Q_WS_WIN
 #include <io.h>
#else
 #include <stdio.h>
 #include <iostream>
 #include <unistd.h>
#endif
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef Q_WS_WIN
    int filelength(int handle)
    {
      int cur = lseek(handle,0,SEEK_CUR);//Store current pos
      int len = lseek(handle,0,SEEK_END);// Move to end of file
      lseek(handle, cur, SEEK_SET);	 // Reset file pointer to initial pos
      return len;			 // Return file length
    }
#endif

#ifndef O_BINARY 
#define O_BINARY 0 
#endif


//////////////////////////////////////////////////////////////////////
// macros, constants, data types
//////////////////////////////////////////////////////////////////////
#define  NULLREC      (-1L)
#define  FREE_BLOCK   (-2)

#define  ENT_ADR(pb,off)  ((ENTRY*)((char*)((pb)->entries) + off))
#define  ENT_SIZE(pe)     strlen((pe)->key) + 1 + 2 * sizeof(RECPOS)
#define  BUFDIRTY(j)      (m_mci->cache[j].dirty)
#define  BUFHANDLE(j)     (m_mci->cache[j].handle)
#define  BUFBLOCK(j)      (m_mci->cache[j].mb)
#define  BUFCOUNT(j)      (m_mci->cache[j].count)
#define  CB(j)            (m_ix.pos[j].cblock)
#define  CO(j)            (m_ix.pos[j].coffset)

#define memcpy            memmove
void memmove (char *to, char *from, int  length)
{
    register char *TO, *FROM;

    if (to < from) {
    /* move left to right */
	TO = to;
	FROM = from;
	while (length--)
	    *(TO++) = *(FROM++);
    }
    else {
    /* move right to left */
	TO = to + length - 1;
	FROM = from + length - 1;
	while (length--)
	    *(TO--) = *(FROM--);
    }
}


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIPIndex::CIPIndex()
{
        memset(&m_ix,0, sizeof(IX_DESC));
        memset(&m_bt_buffer,0, sizeof(IX_BUFFER));
        memset(&m_Key,0, sizeof(ENTRY));
	m_mci			= &m_bt_buffer;
	m_block_ptr		= NULL;
	m_spare_block	= NULL;
	m_cache_ptr		= 0;
	m_cache_init	= 0;
	m_split_size	= IXB_SPACE;
	m_comb_size		= (IXB_SPACE/2);
        m_sLastError	= ("");
	m_bDuplicates	= FALSE;
	m_bIsOpen		= FALSE;
}

CIPIndex::~CIPIndex()
{
	Close();
}

/*  file I/O for B-PLUS module  */
void CIPIndex::error(int j, long l)
{
    static char *msg[3] = {"ERROR - CANNOT OPEN/CLOSE FILE",
                           "ERROR WHILE READING FILE",
                           "ERROR WHILE WRITING FILE"};

    m_sLastError = QString(msg[j])+QString(" - Record Number "+QString::number(l));//m_sLastError.Format("%s - Record Number %ld", msg[j], l);
} /* error */


void CIPIndex::read_if(RECPOS start, char *buf, int nwrt)
  {
    long err;
    err = start - lseek(m_ix.ixfile, start, SEEK_SET);
    if (err == 0) err = nwrt - read(m_ix.ixfile, buf, nwrt);
    if (err != 0) error(1, start);
  } /* read_if */


void CIPIndex::write_if(int handle, RECPOS start, char *buf, int nwrt)
  {
    long err;
    err = start - lseek(handle, start, SEEK_SET);
    if (err == 0) err = nwrt - write(handle, buf, nwrt);
    if (err != 0) error(2, start);
  } /* write_if */


int CIPIndex::creat_if(char *fn)
  {
    int   ret;
    ret = open(fn,O_RDWR|O_CREAT|O_TRUNC|O_BINARY,S_IREAD|S_IWRITE);
    if (ret  < 0) error(0,0L);
    return (ret);
  } /* creat_if */


int CIPIndex::open_if(char *fn, bool bWrite)
  {
    int  ret;

	if(bWrite)
		ret = open(fn,O_RDWR|O_BINARY);
	else
		ret = open(fn,O_RDONLY|O_BINARY);

    if (ret < 1) error(0,0L);

    return (ret);
  } /* open_if */


void CIPIndex::close_if(int handle)
  {
    if(close(handle) < 0)  error(2,0L);
  } /*  close_if */


bool CIPIndex::Open(char *name, bool bWrite /*= FALSE*/)
{
	m_sFilePathName = QString(name);

    m_ix.ixfile = open_if(name, bWrite);
	if(m_ix.ixfile < 1)
	{
		m_bIsOpen = FALSE;
		return FALSE;
	}

	if(m_bDuplicates)
		m_ix.duplicate = 1;
	else
		m_ix.duplicate = 0;

    read_if(0L,(char *)&(m_ix.root), (sizeof(BLOCK) + sizeof(IX_DISK)));
    if (!m_cache_init)
      {
        init_cache();
        m_cache_init = 1;
      }
    GoTop();

	m_bIsOpen = TRUE;
    return TRUE;
} /* open_index */

bool CIPIndex::Close()
{
    int i;

	//>> PS 18.02.2001
	if(!m_bIsOpen) return FALSE;
	//<< PS 18.02.2001

    write_if(m_ix.ixfile, 0L,(char *)&(m_ix.root),
               (sizeof(BLOCK) + sizeof(IX_DISK)));
    for (i = 0; i < NUM_BUFS; i++)
      if (BUFHANDLE(i) == m_ix.ixfile)
        {
          if (BUFDIRTY(i))
            {
              write_if(BUFHANDLE(i),
                       BUFBLOCK(i).brec,
                       (char *) &BUFBLOCK(i),
                       (int) sizeof(BLOCK));
              BUFDIRTY(i) = 0;
            }
          BUFBLOCK(i).brec = NULLREC;
      }
    close_if(m_ix.ixfile);

	m_bIsOpen = FALSE;
    return TRUE;
} /* close_index */

bool CIPIndex::Create(char *name)
{
    m_sFilePathName = QString(name);

    m_ix.ixfile = creat_if(name);
    if(m_ix.ixfile < 0)
    {
            m_bIsOpen = FALSE;
            return FALSE;
    }

    if(m_bDuplicates)
        m_ix.duplicate = 1;
    else
        m_ix.duplicate = 0;
    m_ix.dx.nl = 1;
    m_ix.dx.ff = NULLREC;
    m_ix.level = 0;
    CO(0) = -1;
    CB(0) = 0L;
    m_ix.root.brec = 0L;
    m_ix.root.bend = 0;
    m_ix.root.p0 = NULLREC;
    write_if(m_ix.ixfile, 0L,(char *)&(m_ix.root),
               (sizeof(BLOCK) + sizeof(IX_DISK)));
    if (!m_cache_init)
      {
        init_cache();
        m_cache_init = 1;
      }
    GoTop();

	m_bIsOpen = TRUE;
    return TRUE;
} /* make_index */


/*  cache I/O for BPLUS  */

void CIPIndex::update_block()
  {
    if (m_block_ptr != &(m_ix.root))
       BUFDIRTY(m_cache_ptr) = 1;
  } /* update_block */


void CIPIndex::init_cache()
  {
    register int  j;
    for (j = 0; j < NUM_BUFS; j++)
      {  BUFDIRTY(j) = 0;
         BUFCOUNT(j) = 0;
         BUFBLOCK(j).brec = NULLREC;
      }
  } /* init_cache */


int CIPIndex::find_cache(RECPOS r)
  {
    register int  j;
    for (j = 0; j < NUM_BUFS; j++)
      {
        if((BUFBLOCK(j).brec == r) && (BUFHANDLE(j) == m_ix.ixfile))
         {  m_cache_ptr = j;
            return (1);
      }  }
    return (-1);
  } /* find_cache */


int CIPIndex::new_cache()
  {
    register int  i;
    i = (m_cache_ptr + 1) % NUM_BUFS;
    if (BUFDIRTY(i)) write_if(BUFHANDLE(i),
                              BUFBLOCK(i).brec,
                              (char *) &BUFBLOCK(i),
                              sizeof(BLOCK));
    BUFHANDLE(i) = m_ix.ixfile;
    BUFDIRTY(i) = 0;
    return (i);
  } /* new_cache */


void CIPIndex::load_cache(RECPOS r)
  {
    m_cache_ptr = new_cache();
    read_if(r, (char *)&BUFBLOCK(m_cache_ptr), sizeof(BLOCK));
  } /* load_cache */


void CIPIndex::get_cache(RECPOS r)
  {
    if (find_cache(r) < 0)
       load_cache(r);
    m_block_ptr = &BUFBLOCK(m_cache_ptr);
  } /* get_cache */


void CIPIndex::retrieve_block(int j, RECPOS r)
  {
    if (j == 0)
       m_block_ptr = &(m_ix.root);
    else  get_cache(r);
    CB(j) = m_block_ptr->brec;
  } /* retrieve_block */


/*  low level functions of BPLUS  */

int CIPIndex::prev_entry(int off)
  {
     if (off <= 0)
       {
         off = -1;
         CO(m_ix.level) = off;
       }
     else
       off = scan_blk(off);
     return(off);
  } /* prev_entry */


int CIPIndex::next_entry(int off)
  {
     if (off == -1)
       off = 0;
     else
       {
         if (off < m_block_ptr->bend)
            off += ENT_SIZE(ENT_ADR(m_block_ptr,off));
       }
     CO(m_ix.level) = off;
     return (off);
  } /* next_entry */


void CIPIndex::copy_entry(ENTRY *to, ENTRY *from)
  {
    int me;
    me = ENT_SIZE(from);
    (void) memcpy(to, from, me);
  } /* copy_entry */


int CIPIndex::scan_blk(int n)
  {
     register int off, last;
     off = 0;
     last = -1;
     while (off < n )
       {  last = off;
          off += ENT_SIZE(ENT_ADR(m_block_ptr,off));
       }
     CO(m_ix.level) = last;
     return (last);
  } /* scan_blk */


int CIPIndex::last_entry()
  {
     return( scan_blk(m_block_ptr->bend) );
  } /* last_entry */


/*  maintain list of free index blocks  */

void CIPIndex::write_free(RECPOS r, BLOCK *pb)
  {
    pb->p0 = FREE_BLOCK;
    pb->brec = m_ix.dx.ff;
    write_if(m_ix.ixfile, r, (char *) (char *) pb, sizeof(BLOCK));
    m_ix.dx.ff = r;
  } /* write_free */


RECPOS CIPIndex::get_free()
  {
    RECPOS  r, rt;

    r = m_ix.dx.ff;
    if ( r != NULLREC )
      {  read_if(r, (char *)&rt, (int) sizeof( RECPOS ));
         m_ix.dx.ff = rt;
      }
    else
      r = filelength(m_ix.ixfile);
    return (r);
  } /* get_free */


/*  general BPLUS block level functions  */

int CIPIndex::find_block(ENTRY *pe, int *poff)
  {
    register int pos, nextpos, ret;
    pos = -1;
    nextpos = 0;
    ret = 1;
    while ( nextpos < m_block_ptr->bend)
      {
        ret = strcmp((char *)(pe->key),
                     (char *)(ENT_ADR(m_block_ptr, nextpos)->key));
        if (ret <= 0)
          {
             if (ret == 0) pos = nextpos;
             break;
          }
        pos = nextpos;
        nextpos = next_entry(pos);
      }
    CO(m_ix.level) = pos;
    *poff = pos;
    return (ret);
  } /* find_block */


void CIPIndex::movedown(BLOCK *pb, int off, int n)
  {
    memcpy(ENT_ADR(pb, off),
           ENT_ADR(pb, off + n),
           pb -> bend - (off + n));
  } /* movedown */


void CIPIndex::moveup(BLOCK *pb, int off, int n)
  {
    memcpy(ENT_ADR(pb, off + n),
            ENT_ADR(pb, off),
            pb->bend - off);
  } /* moveup */


void CIPIndex::ins_block(BLOCK *pb, ENTRY *pe, int off)
  {
    int size;
    size = ENT_SIZE(pe);
    moveup(pb,off,size);
    copy_entry(ENT_ADR(pb,off),pe);
    pb->bend += size;
  } /* ins_block */


void CIPIndex::del_block(BLOCK *pb, int off)
  {
    int ne;
    ne = ENT_SIZE(ENT_ADR(pb, off));
    movedown(pb, off, ne);
    pb->bend -= ne;
  } /* del_block */


/*  position at start/end of index  */

bool CIPIndex::GoTop()
{
    m_block_ptr = &(m_ix.root);
    CB(0) = 0L;
    CO(0) = -1;
    m_ix.level = 0;
    while(m_block_ptr->p0 != NULLREC)
      {
        retrieve_block(++(m_ix.level), m_block_ptr->p0);
        CO(m_ix.level) = -1;
      }
    return TRUE;
} /* KeyGoTop */


bool CIPIndex::GoBottom()
{
    long  ads;
    m_block_ptr = &(m_ix.root);
    CB(0) = 0L;
    m_ix.level = 0;
    if(last_entry() >= 0)
      {
        while ((ads = ENT_ADR(m_block_ptr,last_entry())->idxptr) != NULLREC)
             retrieve_block(++(m_ix.level), ads);
      }
    CO(m_ix.level) = m_block_ptr->bend;
    return TRUE;
} /* KeyGoBottom */


/*  get next, previous entries  */

bool CIPIndex::SkipNext()
{
	return SkipNext(&m_Key);
}

int CIPIndex::SkipNext(ENTRY* pe)
{
    RECPOS  address;
    retrieve_block(m_ix.level, CB(m_ix.level));
    if(CO(m_ix.level) == -1) address = m_block_ptr->p0;
    else address = ENT_ADR(m_block_ptr, CO(m_ix.level))->idxptr;
    while (address != NULLREC)
      {
         retrieve_block(++(m_ix.level), address);
         CO(m_ix.level) = -1;
         address = m_block_ptr->p0;
      }
    next_entry(CO(m_ix.level));
    if (CO(m_ix.level) == m_block_ptr->bend)
      {
        do
          { if(m_ix.level == 0)
              {
                GoBottom();
                return FALSE;
              }
            --(m_ix.level);
            retrieve_block(m_ix.level, CB(m_ix.level));
            next_entry(CO(m_ix.level));
          } while (CO(m_ix.level) == m_block_ptr->bend);
      }
    copy_entry(pe, ENT_ADR(m_block_ptr, CO(m_ix.level)));
	return TRUE;
} /* KeySkipNext */


bool CIPIndex::SkipPrev()
{
    RECPOS  address;
    retrieve_block(m_ix.level, CB(m_ix.level));
    prev_entry(CO(m_ix.level));
    if (CO(m_ix.level) == -1)
      address = m_block_ptr->p0;
    else
      address = ENT_ADR(m_block_ptr, CO(m_ix.level))->idxptr;
    if (address != NULLREC)
      { do
          {
            retrieve_block(++(m_ix.level), address);
            address = ENT_ADR(m_block_ptr, last_entry())->idxptr;
          } while (address != NULLREC);
      }
    if (CO(m_ix.level) == -1)
      { do
          {
            if(m_ix.level == 0)
              {
                GoTop();
                return FALSE;
              }
            --(m_ix.level);
          } while (CO(m_ix.level) == -1);
        retrieve_block(m_ix.level, CB(m_ix.level));
      }
    copy_entry(&m_Key, ENT_ADR(m_block_ptr, CO(m_ix.level)));
    return TRUE;
} /* KeySkipPrev */

int CIPIndex::Skip(int nSkip /*= 1*/)
{
	int nCount = 0;
	int i;
	if(nSkip == 0) return 0;

	if(nSkip > 0)
	{
		for(i=0; i<nSkip; i++)
		{
			if(!SkipNext()) break;
			nCount++;
		}
	}
	else
	{
		nSkip = nSkip * (-1);
		for(i=0; i<nSkip; i++)
		{
			if(!SkipPrev()) break;
			nCount++;
		}
	}
	return nCount;
}


/*  insert new entries into tree  */

void CIPIndex::split(int l, ENTRY *pe, ENTRY *e)
  {
    int  half, ins_pos, size;
    ins_pos = CO(m_ix.level);
    half = scan_blk(m_block_ptr->bend / 2 + sizeof(RECPOS));
    if (half == ins_pos)
      *e = *pe;
    else
      {
         copy_entry(e, ENT_ADR(m_block_ptr, half));
         size = ENT_SIZE(e);
         movedown(m_block_ptr, half, size);
         m_block_ptr->bend -= size;
      }
    m_spare_block = &BUFBLOCK(new_cache());
    memcpy(m_spare_block->entries,
           ENT_ADR(m_block_ptr,half),
           m_block_ptr->bend - half);
    m_spare_block->brec = get_free();
    m_spare_block->bend = m_block_ptr->bend - half;
    m_spare_block->p0 = e->idxptr;
    m_block_ptr->bend = half;
    e->idxptr = m_spare_block->brec;
    if (ins_pos < half)
      ins_block(m_block_ptr,pe,ins_pos);
    else if (ins_pos > half)
      {
         ins_pos -= ENT_SIZE(e);
         ins_block(m_spare_block,pe,ins_pos - half);
         CB(l) = e->idxptr;
         CO(l) = CO(l) - half;
      }
    write_if(m_ix.ixfile, m_spare_block->brec,
             (char *) m_spare_block, sizeof(BLOCK));
  } /* split */


void CIPIndex::ins_level(int l, ENTRY *e)
  {
    int  i;
    if ( l < 0)
	{
		for (i = 1; i < MAX_LEVELS; i++)
		{
			CO(MAX_LEVELS - i) = CO(MAX_LEVELS - i - 1);
			CB(MAX_LEVELS - i) = CB(MAX_LEVELS - i - 1);
		}
		memcpy(m_spare_block, &(m_ix.root), sizeof(BLOCK));
		m_spare_block->brec = get_free();
		write_if(m_ix.ixfile, m_spare_block->brec,
			     (char *) m_spare_block, sizeof(BLOCK));
		m_ix.root.p0 = m_spare_block->brec;
		copy_entry((ENTRY *) (m_ix.root.entries), e);
		m_ix.root.bend = ENT_SIZE(e);
		CO(0) = 0;
		m_ix.level = 0;
		(m_ix.dx.nl)++;
	}
    else
	{
		ins_block(m_block_ptr,e,CO(l));
	}
  } /* ins_level */


int CIPIndex::insert_ix(ENTRY *pe)
  {
    ENTRY    e, ee;
    int h;
    h = 0;
    ee = *pe;
    do
      {
         if(CO(m_ix.level) >= 0)
           CO(m_ix.level) += ENT_SIZE(ENT_ADR(m_block_ptr, CO(m_ix.level)));
         else
           CO(m_ix.level) = 0;
         update_block();
         if( (m_block_ptr->bend + ENT_SIZE(&ee)) <= m_split_size)
           {
             ins_level(m_ix.level, &ee);
             break;
           }
         else
           {
             h = 1;
             split(m_ix.level,&ee, &e);
              ee = e;
              m_ix.level--;
              if (m_ix.level < 0)
                {
                  ins_level(m_ix.level, &e);
                  break;
                }
              retrieve_block(m_ix.level, CB(m_ix.level));
           }
      }
    while (1);
    if (h) find_ix(pe, 0);

    return ( IX_OK );
  } /* insert_ix */


/*  BPLUS find and add key functions  */

int CIPIndex::find_ix(ENTRY *pe, int find)
  {
    int      level, off, ret;
    RECPOS   ads;
//    ENTRY    found;
    ads = 0L;
    level = ret = 0;
    while (ads != NULLREC)
      {  m_ix.level = level;
         retrieve_block(level, ads);
         if (find_block(pe, &off) == 0) ret = 1;
         if (ret && find) break;
         if (off == -1)
           ads = m_block_ptr->p0;
         else
           ads = ENT_ADR(m_block_ptr, off)->idxptr;
         CO(level++) = off;
       }
     return ( ret );
   } /* find_ix */


bool CIPIndex::Find(QString& sKey)
{
	//>> PS 12.02.2001
        if(sKey.isEmpty()) return IX_FAIL;
	//<< PS 12.02.2001

	//>>PS: 24.01.2003
	//Avoid oversized strings
        if(sKey.length() >= MAXKEY)
                sKey = sKey.left(MAXKEY-1);
	//<<PS: 24.01.2003

        memcpy(m_Key.key, (char*)sKey.toLatin1().data(), sKey.length());
        return Find(&m_Key);

} /* KeyFind */

int CIPIndex::Find(ENTRY *pe)
{
    int ret;
    ret = find_ix(pe, 1);
    if ( ret ) copy_entry(pe, ENT_ADR(m_block_ptr, CO(m_ix.level)));
    return ( ret );
} /* KeyFind */


bool CIPIndex::Add(QString& sKey)
{
    int ret;
	//>> PS 12.02.2001
        if(sKey.isEmpty())
        {
            return IX_FAIL;
        }
	//<< PS 12.02.2001

	//>>PS: 24.01.2003
	//Avoid oversized strings
        if(sKey.length() >= MAXKEY)
                sKey = sKey.left(MAXKEY-1);
	//<<PS: 24.01.2003

        memcpy(m_Key.key, (char*)sKey.toLatin1().data(), sKey.length());

    ret = find_ix(&m_Key, 0);
    if (ret && (m_ix.duplicate == 0))
    {
        return ( IX_FAIL );
    }
    m_Key.idxptr = NULLREC;
	ret = insert_ix(&m_Key);

    return ret;
} /* add_key */


bool CIPIndex::Locate(QString& sKey)
{
    //>> PS 12.02.2001
    if(sKey.isEmpty()) return FALSE;
    //<< PS 12.02.2001

    //>>PS: 24.01.2003
    //Avoid oversized strings
    if(sKey.length() >= MAXKEY)
            sKey = sKey.left(MAXKEY-1);
    //<<PS: 24.01.2003

    memcpy(m_Key.key, (char*)sKey.toLatin1().data(), sKey.length());

    int ret = find_ix(&m_Key, 1);

    if(ret)
        copy_entry(&m_Key, ENT_ADR(m_block_ptr, CO(m_ix.level)));
    else if(SkipNext() == EOIX)
    {
        ::memset(&m_Key,0,sizeof(ENTRY));
        return FALSE;
    }

    //It seems we have a partial match -> compare partial strings
    copy_entry(&m_Key, ENT_ADR(m_block_ptr, CO(m_ix.level)));
    QString _sFound(m_Key.key);
    QString _sKey(sKey);
    _sFound.toUpper();
    _sKey.toUpper();
    if((_sFound.indexOf(_sKey) == 0) && FindExactAsString(QString(m_Key.key)))
    {
        return TRUE;
    }

    return FALSE;
  } /* locate_key */

int CIPIndex::FindExact(ENTRY *pe)
{
    int  ret;
    ENTRY e;
    copy_entry(&e, pe);
    ret = Find(&e);
    if ( ret && m_ix.duplicate)
      {
        do
          {
            ret = (e.recptr == pe->recptr);
            if( !ret )  ret = SkipNext(&e);
            if (ret) ret = (strcmp(e.key, pe->key) == 0);
            if ( !ret ) return ( 0 );
          } while ( !ret );
      }
    copy_entry(pe, &e);
    return ( ret );
}
bool CIPIndex::FindExactAsString(QString sKey)
{
    return FindExact(sKey);
}
bool CIPIndex::FindExact(QString& sKey)
{
	//>> PS 12.02.2001
        if(sKey.isEmpty()) return IX_FAIL;
	//<< PS 12.02.2001

	//>>PS: 24.01.2003
	//Avoid oversized strings
        if(sKey.length() >= MAXKEY)
                sKey = sKey.left(MAXKEY-1);
	//<<PS: 24.01.2003

        memcpy(m_Key.key, (char*)sKey.toLatin1().data(), sKey.length());
	return FindExact(&m_Key);
}

/* BPLUS delete key functions */

bool CIPIndex::Delete(QString& sKey)
  {
     ENTRY   e;
     RECPOS  ads;
     int     h, leveli, levelf;

	//>> PS 12.02.2001
        if(sKey.isEmpty()) return FALSE;
	//<< PS 12.02.2001

	//>>PS: 24.01.2003
	//Avoid oversized strings
        if(sKey.length() >= MAXKEY)
                sKey = sKey.left(MAXKEY-1);
	//<<PS: 24.01.2003

        memcpy(m_Key.key, (char*)sKey.toLatin1().data(), sKey.length());

     if (!FindExact(&m_Key))  return FALSE;
     h = 1;
     if ((ads = m_Key.idxptr) != NULLREC)
       {
          leveli = m_ix.level;
          do
            {
               retrieve_block(++(m_ix.level), ads);
               CO(m_ix.level) = -1;
            }
          while ((ads = m_block_ptr->p0) != NULLREC);
          CO(m_ix.level) = 0;
          copy_entry(&e, ENT_ADR(m_block_ptr, CO(m_ix.level)));
          levelf = m_ix.level;
          m_ix.level = leveli;
          replace_entry(&e);
          m_ix.level = levelf;
       }
     while ( h )
       {
          retrieve_block(m_ix.level, CB(m_ix.level));
          del_block(m_block_ptr, CO(m_ix.level));
          update_block();
          if ( (m_ix.level == 0) && (m_block_ptr->bend == 0))
          /* tree was reduced in height */
            {
              if (m_ix.root.p0 != NULLREC)
                {
                  retrieve_block(++m_ix.level, m_ix.root.p0);
                  memcpy(&(m_ix.root), m_block_ptr, sizeof(BLOCK));
                  (m_ix.dx.nl)--;
                  write_free(m_block_ptr->brec, m_block_ptr);
                  BUFDIRTY(m_cache_ptr) = 0;
                  BUFHANDLE(m_cache_ptr) = 0;
                }
              break;
            }
          h = (m_block_ptr->bend < m_comb_size) && (m_ix.level > 0);
          if ( h )
              h = combineblk(CB(m_ix.level), m_block_ptr->bend);
       }
    find_ix(&m_Key,0);
    return( IX_OK );
  } /* KeyDelete */


int CIPIndex::combineblk(RECPOS ads, int size)
  {
    ENTRY  e;
    RECPOS address;
    int    esize, off, ret, saveoff, ibuff;
    ret = 0;
    saveoff = CO(--(m_ix.level));
    retrieve_block(m_ix.level, CB(m_ix.level));
    if ((off = next_entry( saveoff )) < m_block_ptr->bend)
      /* combine with page on right */
      {
        if ( (ENT_SIZE(ENT_ADR(m_block_ptr, off)) + size) < m_split_size)
          {
            copy_entry(&e, ENT_ADR(m_block_ptr, off));
            address = ENT_ADR(m_block_ptr, CO(m_ix.level))->idxptr;
            retrieve_block(++m_ix.level, address);
            ibuff = m_cache_ptr;
            m_spare_block = m_block_ptr;
            retrieve_block(m_ix.level, ads);
            esize = ENT_SIZE(&e);
            if(((m_block_ptr->bend + m_spare_block->bend + esize) >= m_split_size)
                 && (m_spare_block->bend <= m_block_ptr->bend + esize))
               return( ret );
            e.idxptr = m_spare_block->p0;
            ins_block(m_block_ptr, &e, m_block_ptr->bend);
            update_block();
            if ((m_block_ptr->bend + m_spare_block->bend) < m_split_size)
            /* combine the blocks */
              {
                memcpy(ENT_ADR(m_block_ptr, m_block_ptr->bend),
                       ENT_ADR(m_spare_block, 0),
                       m_spare_block->bend);
                m_block_ptr->bend += m_spare_block->bend;
                write_free(m_spare_block->brec, m_spare_block);
                BUFDIRTY(ibuff) = 0;
                BUFHANDLE(ibuff) = 0;
                --m_ix.level;
                ret = 1;
              }
            else
            /* move an entry up to replace the one moved */
              {
                copy_entry(&e, ENT_ADR(m_spare_block, 0));
                esize = ENT_SIZE(&e);
                movedown(m_spare_block, 0, esize);
                m_spare_block->bend -= esize;
                m_spare_block->p0 = e.idxptr;
                BUFDIRTY(ibuff) = 1;
                --(m_ix.level);
                replace_entry(&e);
              }
          }
      }
    else
      /* move from page on left */
      {
        if ( (ENT_SIZE(ENT_ADR(m_block_ptr, CO(m_ix.level))) + size)
                 < m_split_size)
          {
            copy_entry(&e, ENT_ADR(m_block_ptr, saveoff));
            off = prev_entry(saveoff);
            if (CO(m_ix.level) == -1) address = m_block_ptr->p0;
            else address = ENT_ADR(m_block_ptr, CO(m_ix.level))->idxptr;
            retrieve_block(++m_ix.level, address);
            off = last_entry();
            ibuff = m_cache_ptr;
            m_spare_block = m_block_ptr;
            retrieve_block(m_ix.level, ads);
            esize = ENT_SIZE(&e);
            if(((m_block_ptr->bend + m_spare_block->bend + esize) >= m_split_size)
                 && (m_spare_block->bend <= m_block_ptr->bend + esize))
               return( ret );
            BUFDIRTY(ibuff) = 1;
            CO(m_ix.level) = 0;
            e.idxptr = m_block_ptr->p0;
            ins_block(m_block_ptr, &e, 0);
            if ((m_block_ptr->bend + m_spare_block->bend) < m_split_size)
            /* combine the blocks */
              {
                memcpy(ENT_ADR(m_spare_block, m_spare_block->bend),
                       ENT_ADR(m_block_ptr, 0),
                       m_block_ptr->bend);
                m_spare_block->bend += m_block_ptr->bend;
                write_free(m_block_ptr->brec, m_block_ptr);
                BUFDIRTY(m_cache_ptr) = 0;
                BUFHANDLE(m_cache_ptr) = 0;
                CO(--(m_ix.level)) = saveoff;
                ret = 1;
              }
            else
            /* move an entry up to replace the one moved */
              {
                 m_block_ptr->p0 = ENT_ADR(m_spare_block,off)->idxptr;
                 copy_entry(&e, ENT_ADR(m_spare_block, off));
                 m_spare_block->bend = off;
                 update_block();
                 CO(--(m_ix.level)) = saveoff;
                 replace_entry(&e);
              }
          }
      }
    return ( ret );
  } /* combineblk */


void CIPIndex::replace_entry(ENTRY *pe)
  {
    retrieve_block(m_ix.level, CB(m_ix.level));
    pe->idxptr = ENT_ADR(m_block_ptr, CO(m_ix.level))->idxptr;
    del_block(m_block_ptr, CO(m_ix.level));
    prev_entry(CO(m_ix.level));
    insert_ix(pe);
  } /* replace_entry */

void CIPIndex::GetRecord(QString& sKey)
{
	sKey = QString(m_Key.key);
}

bool CIPIndex::Seek(QString sKey)
{
	//>> PS 12.02.2001
        if(sKey.isEmpty()) return IX_FAIL;
	//<< PS 12.02.2001

        if(sKey.right(1) == ("*"))
	{
            sKey = sKey.left(sKey.length()-1);
            return Locate(sKey);
	}
	else
	{
		return Find(sKey);
	}
}

void CIPIndex::SetDuplicates(bool bAllow /*= FALSE*/)
{
	m_bDuplicates = bAllow;
}

#undef memcpy
