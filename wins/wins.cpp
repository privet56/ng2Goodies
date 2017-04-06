// wins.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "wins.h"
#include "winsDlg.h"
#include "Winperf.h"
#include "ipfile.h"
#include "ipcommon.h"
#include <io.h>
#include "ipmmf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Key "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\009"

#define SHARED_MEMORY_IDENTIFIER "wins_shared"

#pragma data_seg ("wins_shared")
DWORD __dwFirstInstanceProcessID = 0;
#pragma data_seg ()

#pragma comment(linker,"/SECTION:wins_shared,RWS")


#define WM_MESSSINGLEINSTANCE 3002

/////////////////////////////////////////////////////////////////////////////
// CWinsApp

BEGIN_MESSAGE_MAP(CWinsApp, CWinApp)
	//{{AFX_MSG_MAP(CWinsApp)
		ON_MESSAGE(WM_MESSSINGLEINSTANCE, OnMsgSingleInstance)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinsApp Konstruktion

CWinsApp::CWinsApp()
{
	SetDialogBkColor(RGB(255, 255, 200),RGB(0, 0, 255) );
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CWinsApp-Objekt

CWinsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWinsApp Initialisierung

LRESULT CWinsApp::OnMsgSingleInstance(WPARAM wp, LPARAM lp) 
{
	CIPString sMsg(_T(""));
	CIPMMF	  mmf;
	CIPString sPrID;
	sPrID.Format("%d", GetCurrentThreadId());
	if(mmf.Open(sPrID, IPMMF_READ, TRUE, 1024))
	{
		void* _pMMF = mmf.Map();
		::lstrcpy(sMsg.GetBuffer(1024), (LPCTSTR)_pMMF);
		sMsg.ReleaseBuffer();
		mmf.Unmap();
		mmf.Close();
	}

	/*	//THIS WORKS FINE!!!
	HANDLE hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,SHARED_MEMORY_IDENTIFIER);
	LPVOID lpMappedViewOfFile = NULL;
	if(hFileMap)
		lpMappedViewOfFile = MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,1256);
	CIPString sMsg((char*)lpMappedViewOfFile);
	if(lpMappedViewOfFile)
		UnmapViewOfFile(lpMappedViewOfFile);
	if(hFileMap)
		CloseHandle(hFileMap);
	*/

	/*	//WORKS ONLY PROCESS-INTERN!!!
	HGLOBAL _h = (HGLOBAL)wp;
	if(_h)
	{
		CIPString sMsg2((char*)_h);
		sMsg = sMsg2;
		::GlobalFree(_h);
	}
	else
		AfxMessageBox("1");
	/*
	if(_h)
	{
		char* _p = (char*)::GlobalLock(_h);
		if (_p)
		{
			CIPString sMsg2(_p);
			sMsg = sMsg2;
			::GlobalUnlock(_h);
		}
		else
		{
			AfxMessageBox("2");
		}
		::GlobalFree(_h);
	}
	else
		AfxMessageBox("1");
	*/

	if(this->m_pMainWnd)
	{
		this->m_pMainWnd->SetActiveWindow();
		this->m_pMainWnd->SetForegroundWindow();
		this->m_pMainWnd->SetFocus();
		this->m_pMainWnd->BringWindowToTop();
		this->m_pMainWnd->SetActiveWindow();
		this->m_pMainWnd->SetForegroundWindow();
		this->m_pMainWnd->SetFocus();
		this->m_pMainWnd->BringWindowToTop();
	}
	MessageBox(this->m_pMainWnd->m_hWnd, sMsg/*"Only one instance of this application allowed"*/, "single instance application", MB_OK|MB_SETFOREGROUND|MB_TOPMOST);
	return 0;
}

BOOL CWinsApp::InitInstance()
{
	if(__dwFirstInstanceProcessID != 0)
	{
		CIPMMF	  mmf;
		CIPString sPrID;
		sPrID.Format("%d", __dwFirstInstanceProcessID);
		if(mmf.Open(sPrID, IPMMF_WRITE, TRUE, 1024))
		{
			void* _pMMF = mmf.Map();
			::lstrcpy((LPTSTR)_pMMF, (LPCTSTR)"Only one instance of this application allowed");
			mmf.Unmap();			//do not mmf.Close();
			::PostThreadMessage(__dwFirstInstanceProcessID, WM_MESSSINGLEINSTANCE, (WPARAM)_pMMF, 0);
		}

		/*	//THIS WORKS FINE!!!
	    HANDLE hFileMap = CreateFileMapping((HANDLE)-1, NULL,PAGE_READWRITE,NULL,1256,SHARED_MEMORY_IDENTIFIER);
		LPVOID lpMappedViewOfFile = MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,1256);
		::lstrcpy(/ *destination* /(char*)lpMappedViewOfFile,/ *source* /"Only one instance of this application allowed");
		::PostThreadMessage(__dwFirstInstanceProcessID, WM_MESSSINGLEINSTANCE, (WPARAM)lpMappedViewOfFile, 0);
		*/

		/*	//WORKS ONLY PROCESS-INTERN!!!
		HGLOBAL _h = ::GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, 256);
		if (_h)
		{
			::lstrcpy(/ *destination* /(char*)_h,/ *source* /"Only one instance of this application allowed");
			::PostThreadMessage(__dwFirstInstanceProcessID, WM_MESSSINGLEINSTANCE, (WPARAM)_h, 0);
		}
		/*
		if (_h)
		{
			char* _p = (char*)::GlobalLock(_h);
			if (_p)
			{
				::ZeroMemory(_p, 256);
				::lstrcpy(/ *destination* /_p,/ *source* /"Only one instance of this application allowed");
				::GlobalUnlock(_h);
				::PostThreadMessage(__dwFirstInstanceProcessID, WM_MESSSINGLEINSTANCE, (WPARAM)_h, 0);
			}
		}
		*/
		return FALSE;
	}

	__dwFirstInstanceProcessID = ::GetCurrentThreadId();//::GetCurrentProcessId();

	CoInitialize(NULL);
	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	CWinsDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.

	CoUninitialize();

	return FALSE;
}

tagWINDATA::tagWINDATA()
{
	m_HWND = NULL;
	m_lCount = 0;
	m_sTitle = _T("");
	m_bEnabled = FALSE;
	m_sModFN = _T("");
	m_bDlgBased = FALSE;
	m_dwProcessID = NULL;
	iItem = -1;
}

tagTREEITEMDATA::tagTREEITEMDATA()
{

	m_dwProcessID=0;
	m_sTitle=_T("");
	m_sModFN=_T("");
	m_aChildren.RemoveAll();
	uType	= TYPE_NONE;

	me.hModule=NULL;
	me.dwSize=0;
	me.modBaseAddr=0;
	me.th32ModuleID=0;
	me.th32ProcessID=0;

	m_hti=NULL;
}

tagTREEITEMDATA::tagTREEITEMDATA(TREEITEMDATA& tid)
{
	this->operator =(tid);
}

tagTREEITEMDATA& tagTREEITEMDATA::operator =(tagTREEITEMDATA &tid)
{
	m_dwProcessID=tid.m_dwProcessID;
	m_sTitle=tid.m_sTitle;
	m_sModFN=tid.m_sModFN;
	m_aChildren.RemoveAll();
	m_hti	=tid.m_hti;
	uType	= tid.uType;
	me		= tid.me;

	for(int i=0; i < tid.m_aChildren.GetSize(); i++)
		m_aChildren.Add(tid.m_aChildren.GetAt(i));

	return *this;
}

void GetIndex( char *pszCounter, char *szIndex )
{
  char*  pszBuffer;
  char*  pszTemp;
  char   szObject[256] = "";
  DWORD  dwBytes;
  HKEY hKeyIndex;
  int    i = 0;
  int    j = 0;

  // Open the key.
  RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                Key,
                0, KEY_READ,
                &hKeyIndex );

  // Get the size of the counter.
  RegQueryValueEx( hKeyIndex,
                   "Counter",
                   NULL, NULL, NULL,
                   &dwBytes );

  // Allocate memory for the buffer.
  pszBuffer = (char *) HeapAlloc( GetProcessHeap(),
                                  HEAP_ZERO_MEMORY,
                                  dwBytes );

  // Get the titles and counters.
  RegQueryValueEx( hKeyIndex,
                   "Counter",
                   NULL, NULL,
                   (LPBYTE)pszBuffer,
                   &dwBytes );

  // Find the index value for PROCESS.
  pszTemp = pszBuffer;

  while( i != (int)dwBytes )
  {
     while (*(pszTemp+i) != '\0')
     {
        szIndex[j] = *(pszTemp+i);
        i++;
        j++;
     }
     szIndex[j] = '\0';
     i++;
     j = 0;
     while (*(pszTemp+i) != '\0')
     {
        szObject[j] = *(pszTemp+i);
        i++;
        j++;
     }
     szObject[j] = '\0';
     i++;
     j = 0;
     if( *(pszTemp+i) == '\0' )
        i++;
     if( strcmp(szObject, pszCounter) == 0 )
        break;
  }

  // Deallocate the memory.
  HeapFree( GetProcessHeap(), 0, (LPVOID)pszBuffer );

  // Close the key.
  RegCloseKey( hKeyIndex );
} 

CString DisplayFilename( DWORD dwProcessId )
   {
      DWORD                     CurrentProcessId;
      BOOL                      bContinue = TRUE;
      char                      szIndex[256] = "";
      DWORD                     dwBytes = 12000;
      DWORD                     dwProcessIdOffset;
      int                       i;

      PPERF_DATA_BLOCK          pdb;
      PPERF_OBJECT_TYPE         pot;
      PPERF_INSTANCE_DEFINITION pid;
      PPERF_COUNTER_BLOCK       pcb;
      PPERF_COUNTER_DEFINITION  pcd;

      // Get the index for the PROCESS object.
      GetIndex( "Process", szIndex );

      // Get memory for PPERF_DATA_BLOCK.
      pdb = (PPERF_DATA_BLOCK) HeapAlloc( GetProcessHeap(),
                                          HEAP_ZERO_MEMORY,
                                          dwBytes);

      // Get performance data.
      while( RegQueryValueEx(HKEY_PERFORMANCE_DATA, (LPTSTR)szIndex, NULL,
                             NULL, (LPBYTE)pdb, &dwBytes) ==
   ERROR_MORE_DATA )
      {
         // Increase memory.
         dwBytes += 1000;

         // Allocated memory is too small; reallocate new memory.
         pdb = (PPERF_DATA_BLOCK) HeapReAlloc( GetProcessHeap(),
                                               HEAP_ZERO_MEMORY,
                                               (LPVOID)pdb,
                                               dwBytes);
      }

      // Get PERF_OBJECT_TYPE.
      pot = (PPERF_OBJECT_TYPE)((PBYTE)pdb + pdb->HeaderLength);

      // Get the first counter definition.
      pcd = (PPERF_COUNTER_DEFINITION)((PBYTE)pot + pot->HeaderLength);

      // Get index value for ID_PROCESS.
      szIndex[0] = '\0';
      GetIndex( "ID Process", szIndex );

      for( i=0; i< (int)pot->NumCounters; i++ )
      {
         if (pcd->CounterNameTitleIndex == (DWORD)atoi(szIndex))
         {
            dwProcessIdOffset = pcd->CounterOffset;
            break;
         }

         pcd = ((PPERF_COUNTER_DEFINITION)((PBYTE)pcd + pcd->ByteLength));
      }

      // Get the first instance of the object.
      pid = (PPERF_INSTANCE_DEFINITION)((PBYTE)pot + pot->DefinitionLength);

      // Get the name of the first process.
      pcb = (PPERF_COUNTER_BLOCK) ((PBYTE)pid + pid->ByteLength );
      CurrentProcessId = *((DWORD *) ((PBYTE)pcb + dwProcessIdOffset));

      // Find the process object for PID passed in, then print its
      // filename.

      for( i = 1; i < pot->NumInstances && bContinue; i++ )
      {
         if( CurrentProcessId == dwProcessId )
         {
			 CString _sErg = (char *) ((PBYTE)pid + pid->NameOffset);
			 _sErg.Format("%ls.exe", (char *) ((PBYTE)pid + pid->NameOffset) );
			 return _sErg;

            bContinue = FALSE;
         }
         else
         {
            pid = (PPERF_INSTANCE_DEFINITION) ((PBYTE)pcb + pcb->ByteLength);
            pcb = (PPERF_COUNTER_BLOCK) ((PBYTE)pid + pid->ByteLength);
            CurrentProcessId = *((DWORD *)((PBYTE)pcb + dwProcessIdOffset));
         }
      }
      if( bContinue == TRUE )
	  {
		  return _T("");
         printf( "Not found.\b" );
	  }

      // Free the allocated memory.
      if( !HeapFree(GetProcessHeap(), 0, (LPVOID)pdb) )
	  {
		  return _T("");
         printf( "HeapFree failed in main.\n" );
	  }

      // Close handle to the key.
      RegCloseKey( HKEY_PERFORMANCE_DATA );
	  return _T("");
   }



BOOL __Log(CIPString _strToWrite)
{
	if(__GetCFG("debug") != "1")
		return TRUE;
	//_strToWrite = _T("\n") + _strToWrite;
	_strToWrite = _T("\n" + __GetCurTime() + " " + _strToWrite);
	CStdioFile _f;
	CFileException Error;
	CIPString _s = _T("");

	CIPFile _ipf;
	::GetModuleFileName(AfxGetInstanceHandle(), _s.GetBuffer(1024), 1024);
	_s.ReleaseBuffer();
	_ipf.SetFilePath(_s);

	CIPString _s1, _s2;
	_ipf.GetName(_s1);
	_ipf.GetPath(_s2);
	_s = _s2 + "\\" + _s1 + ".log";

	TRY
	{
		if(_access(_s, 00) != 0)			//=if(logfile not found)
		{
			if( !_f.Open((LPCTSTR)_s, CFile::modeWrite | CFile::modeCreate, &Error ) )
			{
				_f.Abort();
				return FALSE;
			}
		}
		else
		{
			if( !_f.Open((LPCTSTR)_s, CFile::modeWrite, &Error ) )
			{
				_f.Abort();
				return FALSE;
			}

		}
		_f.SeekToEnd();
		_f.WriteString(_strToWrite);
		_f.Close();
	}
	CATCH(CFileException, e)
	{
		_f.Abort();
		return FALSE;
	}
	END_CATCH

	return TRUE;
}


BOOL GetProcessModule (DWORD dwPID, DWORD dwModuleID, 
     LPMODULEENTRY32 lpMe32, DWORD cbMe32, CArray<MODULEENTRY32, MODULEENTRY32> *paChildren) 
{ 
    BOOL          bRet        = FALSE; 
    BOOL          bFound      = FALSE; 
    HANDLE        hModuleSnap = NULL; 
    MODULEENTRY32 me32        = {0}; 
 
    // Take a snapshot of all modules in the specified process. 

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, dwPID); 
    if (hModuleSnap == INVALID_HANDLE_VALUE) 
	{
		CIPString s;
		s.FromLong((long)dwPID);
		AfxMessageBox("GetProcessModule e1\n"+s);
        return (FALSE); 
	}
 
    // Fill the size of the structure before using it. 

    me32.dwSize = sizeof(MODULEENTRY32); 
 
    // Walk the module list of the process, and find the module of 
    // interest. Then copy the information to the buffer pointed 
    // to by lpMe32 so that it can be returned to the caller. 

	DWORD dwModSearchFor = dwModuleID;

    if (Module32First(hModuleSnap, &me32)) 
    { 
        do 
        { 
/*			CIPString s;
			s.FromLong((long)me32.th32ModuleID);
			CIPString s2;
			s2.FromLong((long)dwModuleID);
			AfxMessageBox("comparing\n"+s+" =?= "+s2);
*/
			MODULEENTRY32 _meChild;
			
            if (((dwModSearchFor == 0) || (me32.th32ModuleID == dwModSearchFor)) && !bFound)
            { 
                CopyMemory (lpMe32, &me32, cbMe32); 
                bFound = TRUE; 
            }
			else 
				CopyMemory (&_meChild, &me32, cbMe32); 

			_meChild = me32;
			paChildren->Add(_meChild);
        } 
        while (Module32Next(hModuleSnap, &me32)); 
 
        bRet = bFound;   // if this sets bRet to FALSE, dwModuleID 
                         // no longer exists in specified process 
		if(!bRet)
			AfxMessageBox("GetProcessModule e3");
    } 
    else 
	{
        bRet = FALSE;           // could not walk module list 
		AfxMessageBox("GetProcessModule e2");

	}
 
    // Do not forget to clean up the snapshot object. 

    CloseHandle (hModuleSnap); 
 
    return (bRet); 
} 

CIPString __GetMyDir()
{
	CIPString _s = _T("");
	CIPFile _f;
	::GetModuleFileName(AfxGetInstanceHandle(), _s.GetBuffer(1024), 1024);
	_s.ReleaseBuffer();
	_f.SetFilePath(_s);
	_f.GetPath(_s);

	return _s;
}

CIPString __GetCFG(CIPString sEntry)
{
	CIPString _str = _T("");

	//Retrieve file name
	CIPString _s = _T("");
	CIPString _sPath = _T("");
	CIPString _sName = _T("");
	CIPString _sFilePath = _T("");
	CIPFile   _f;

	::GetModuleFileName(AfxGetInstanceHandle(), _s.GetBuffer(1024), 1024);
	_s.ReleaseBuffer();
	_f.SetFilePath(_s);
	_f.GetPath(_sPath);
	_f.GetName(_sName); _sName += ".cfg";
	CIPFile::MakeFileName(_sPath, _sName, _sFilePath);

	//Retrieve global setting
	//-------------------------------------------------------------------------------
	::GetPrivateProfileString(	_T("CFG"), 
								sEntry, 
								_T(""), 
								_str.GetBuffer(1024), 
								1024, 
								_sFilePath);
	_str.ReleaseBuffer();

	_str.Replace(_T("%CURRENTDIR%"), _sPath);

	return _str;
}

void __IPVSleep(int nMilliSeconds)
{
	DWORD n = ::GetTickCount() + nMilliSeconds;
	MSG msg;

	while(::GetTickCount() <= n)
	{
		while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))      
		{
			if(::GetTickCount() > n) break;
			if (!AfxGetThread()->PumpMessage()) 
			{ 
				::PostQuitMessage(0); 
				break; 
			}
		}

		Sleep(1);
	}
}

// Macro for adding pointers/DWORDs together without C arithmetic interfering 
// -- Taken from Matt Pietrek's book
// Thought it'd be great to use..
#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr)+(DWORD)(addValue))
