// IPIndex.h: Schnittstelle für die Klasse CIPIndex.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPINDEX_H__F2D159D4_B1DE_11D4_8A8F_0050DA47309E__INCLUDED_)
#define AFX_IPINDEX_H__F2D159D4_B1DE_11D4_8A8F_0050DA47309E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QString>

///////////////////////////////////////////////////////////////////////////
#ifndef SEEK_SET
#define SEEK_SET	0
#endif
//#ifndef O_BINARY
//#define O_BINARY	0
//#endif

#define IX_OK       1
#define IX_FAIL     0
#define EOIX       (-2)
#define MAXKEY      1024//100
#define NUM_BUFS    32//8
#define MAX_LEVELS  16//8
#define IXB_SIZE    2048
#define IXB_SPACE  (IXB_SIZE - sizeof(short) - sizeof(long) * 2)

typedef long RECPOS;

typedef struct                    /*  entry structure in index        */
  {  RECPOS   idxptr;             /*  points to lower index level     */
     RECPOS   recptr;             /*  points to data record           */
     char     key[MAXKEY];        /*  start of record key             */
  }  ENTRY;

typedef struct                    /*  index record format             */
  {  RECPOS   brec;               /*  position in index file          */
                                  /*  or location of next free block  */
     short    bend;               /*  first unused block location     */
     RECPOS   p0;                 /*  points to next level            */
     char     entries[IXB_SPACE]; /*  here are the key entries        */
  }  BLOCK;

typedef struct                    /*  disk file info                  */
  {  RECPOS   ff;                 /*  location of first free block    */
     short    nl;                 /*  number of index levels          */
  }  IX_DISK;

typedef struct                    /*  memory buffer pool of indx blks */
  {  short    dirty;              /*  true if changed                 */
     short    handle;             /*  index file handle               */
     short    count;              /*  number of times referenced      */
     BLOCK    mb;
  }  MEMBLOCK;

typedef struct
  {  MEMBLOCK     cache [ NUM_BUFS ];
  }  IX_BUFFER;

typedef struct                    /*  in-memory index descriptor      */
  {  short    ixfile;
     short    level;              /*  level in btree                  */
     short    duplicate;          /*  no duplicate keys if 0          */
     struct
       {  RECPOS    cblock;       /*  position in index file          */
          short     coffset;      /*  current offset within block     */
       }  pos [ MAX_LEVELS ];
     BLOCK    root;               /*  root index record               */
     IX_DISK  dx;
  }  IX_DESC;


/////////////////////////////////////////////////////////////////////////
class CIPIndex
{
//Construction / Destruction
public:
	CIPIndex();
	virtual ~CIPIndex();

//Member functions
protected:
	/* ================ internal procedures ================ */
	void	error(int, long);
	void	read_if(RECPOS, char *, int);
	void	write_if(int, RECPOS, char *, int);
	int		creat_if(char *);
        int		open_if(char *, bool bWrite);
	void	close_if(int);
	void	update_block(void);
	void	init_cache(void);
	int		find_cache(RECPOS);
	int		new_cache(void);
	void	load_cache(RECPOS);
	void	get_cache(RECPOS);
	void	retrieve_block(int, RECPOS);
	int		prev_entry(int);
	int		next_entry(int);
	void	copy_entry(ENTRY *, ENTRY *);
	int		scan_blk(int);
	int		last_entry(void);
	void	write_free( RECPOS, BLOCK *);
	RECPOS	get_free(void);
	void	movedown(BLOCK *, int, int);
	void	moveup(BLOCK *, int, int);
	void	ins_block(BLOCK *, ENTRY *, int);
	void	del_block(BLOCK *, int);
	void	split(int, ENTRY *, ENTRY *);
	void	ins_level(int, ENTRY *);
	int		insert_ix(ENTRY *);
	int		combineblk(RECPOS, int);
	void	replace_entry(ENTRY *);
	void	print_blk(BLOCK *);
	int		Find(ENTRY* pe);
	int		SkipNext(ENTRY* pe);

public:
	int		find_block(ENTRY *, int *);
	int		find_ix(ENTRY *, int);
	int		FindExact(ENTRY* pe);

	/* ================ external interface ================ */
        bool Open(char *, bool bWrite = FALSE);
        bool Close();
        bool Create(char *);
        bool GoTop();
        bool GoBottom();
	int  Skip(int nSkip = 1);
        bool SkipNext();
        bool SkipPrev();
        bool Find(QString& sKey);
        bool Locate(QString& sKey);
        bool Add(QString& sKey);
        bool Delete(QString& sKey);
//	bool FindFirst(QString& sKey);
        bool FindExact(QString& sKey);
        bool FindExactAsString(QString sKey);
        bool Seek(QString sKey);
	void GetRecord(QString& sKey);
        void SetDuplicates(bool bAllow = FALSE);
        bool IsOpen(){return m_bIsOpen;};
	QString GetFilePathName(){return m_sFilePathName;};

//Member vars
protected:
	IX_DESC		 m_ix;			//Main descriptor
	IX_BUFFER    m_bt_buffer;
	IX_BUFFER    *m_mci;
	BLOCK        *m_block_ptr;
	BLOCK        *m_spare_block;
	int          m_cache_ptr;
	int          m_cache_init;
	int          m_split_size;
	int          m_comb_size;
	QString	 m_sLastError;
	ENTRY		 m_Key;
        bool		 m_bDuplicates;
        bool		 m_bIsOpen;
	QString	 m_sFilePathName;
};

#endif // !defined(AFX_IPINDEX_H__F2D159D4_B1DE_11D4_8A8F_0050DA47309E__INCLUDED_)
