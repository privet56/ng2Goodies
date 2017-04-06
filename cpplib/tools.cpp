// tools.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

#define SHARED_MEMORY_IDENTIFIER "exewatcher_shared"

#pragma data_seg ("exewatcher_shared")
DWORD __dwFirstInstanceProcessID = 0;
#pragma data_seg ()

#pragma comment(linker,"/SECTION:exewatcher_shared,RWS")

BEGIN_MESSAGE_MAP(CExeWatcherApp, CWinApp)
	//{{AFX_MSG_MAP(CExeWatcherApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExeWatcherApp Konstruktion

CExeWatcherApp::CExeWatcherApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CExeWatcherApp-Objekt

CExeWatcherApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CExeWatcherApp Initialisierung

BOOL EnablePrivilege(HANDLE hToken, LPCTSTR szPrivName, BOOL fEnable)
{
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    LookupPrivilegeValue(NULL, szPrivName, &tp.Privileges[0].Luid);
    tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
    AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
    return((GetLastError() == ERROR_SUCCESS));
}

BOOL CExeWatcherApp::InitInstance()
{
	HANDLE hToken;
    if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		if(!EnablePrivilege(hToken, SE_DEBUG_NAME, TRUE))
			__Log("initinst\tWRN:!EnablePrivilege");
		CloseHandle(hToken);
    }
	else
	{
		__Log("initinst\tWRN:!OpenProcessToken");
	}

	if(__dwFirstInstanceProcessID != 0)
	{
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, __dwFirstInstanceProcessID);
		__dwFirstInstanceProcessID = 0;
		if(hProcess)
		{
			if(TerminateProcess(hProcess,1))
			{
				__Log("initinst\tINF:TerminateProcess:previous.process AND me...");
				return FALSE;
			}
			__Log("initinst\tWRN:!TerminateProcess");
			return FALSE;
		}
		__Log("initinst\tWRN:!OpenProcess");
		return FALSE;
	}

	__dwFirstInstanceProcessID = ::GetCurrentProcessId();

	__do();
	while(TRUE)__IPVSleep(2123);
	return FALSE;

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.


#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	CExeWatcherDlg dlg;
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
	return FALSE;
}

BOOL __Log(CIPString sEntry, BOOL bInWindow/*=TRUE*/)
{
	CIPString sCurTime(::__GetCurTime());
	while(sCurTime.GetLength() < 15)
		sCurTime += _T(" ");
	CIPString _strToWrite = _T("\n" + sCurTime + "\t" + sEntry);
	int iLittle = FALSE;
	if(sEntry.GetLength() < 3)
	{
		_strToWrite = sEntry;
		iLittle = TRUE;
	}

	if(bInWindow && !iLittle && __GetApp()->m_pMainWnd)
	{
		CEdit* pEdit = NULL;//(CEdit*)((CIPInfoGenerator4ibDlg*)__GetApp()->m_pMainWnd)->GetDlgItem(IDC_OUTPUT_E);
		if(pEdit)
		{
			CIPString _sInNow(_T(""));
			pEdit->GetWindowText(_sInNow);	

			if(_sInNow.GetLength() > 10240)
			{
				_sInNow = _sInNow.Mid(_sInNow.GetLength()/2);
			}

			_sInNow += _strToWrite;
			while(_sInNow.Find(("\n\n"))>-1)		_sInNow.Replace(("\n\n"), "\n");
			while(_sInNow.Find(("\x0d\x0a"))>-1)	_sInNow.Replace(("\x0d\x0a"), "\n");
			_sInNow.Replace(("\n"), "\x0d\x0a");
			_sInNow.Replace(("\t"), "      ");

			pEdit->SetWindowText(_sInNow);

			pEdit->LineScroll(pEdit->GetLineCount());

			__IPVSleep(2);
		}
	}

	CIPString _sDebug = __GetCFG("debug");
	if((_sDebug != "1") && (_sDebug != "2"))
		return FALSE;

	
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
				//2. attempt
				CIPString _sTempFP = _T("");
				::GetTempPath(1024, _sTempFP.GetBuffer(1024));
				_sTempFP.ReleaseBuffer();
				_s += _sTempFP + _T("\\") + _s1 + _T(".log");
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
								_str.GetBuffer(10024), 
								10024, 
								_sFilePath);
	_str.ReleaseBuffer();

	_str.Replace(_T("%CURRENTDIR%"), __GetMyDir());

	return _str;
}
void __SetCFG(CIPString sEntry, CIPString sValue)
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

	//Set value
	::WritePrivateProfileString(_T("CFG"),
								sEntry,
								sValue,
								_sFilePath);
}

CIPString __GetPath(CIPString _sTitle)
{
	CIPString _sDir = _T("");

	BROWSEINFO _bi;									//show dialog for choosing a directory!				
	LPITEMIDLIST _lpidl = NULL;

	_bi.hwndOwner = AfxGetMainWnd()->m_hWnd;
	_bi.pidlRoot = NULL;
	_bi.pszDisplayName = _sDir.GetBuffer(255 + 1);
	_sDir.ReleaseBuffer();
	_bi.lpszTitle = _sTitle;
	_bi.ulFlags = BIF_RETURNONLYFSDIRS;
	_bi.lpfn = NULL;
	_bi.lParam = 0l;
	_bi.iImage = 0;	
	_lpidl = ::SHBrowseForFolder(&_bi);
	if (!_lpidl)
		return _T("");
	::SHGetPathFromIDList(_lpidl, _sDir.GetBuffer(255 + 1));
	_sDir.ReleaseBuffer();

	return _sDir;
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
CIPString __ReplaceExt(CIPString sFN, CIPString sNewExt)
{
	CIPString sPath(_T("")), sFileName(_T(""));
	CIPFile f;
	f.SetFilePath(sFN);
	f.GetPath(sPath);
	f.GetName(sFileName);
	if(sNewExt.IsEmpty())
		return _T(sPath+"\\"+sFileName);
	return _T(sPath+"\\"+sFileName+"."+sNewExt);
}
void __IPVSleep(int nMilliSeconds, HWND _hwnd/*=NULL*/)
{
	AfxGetApp()->DoWaitCursor(1);

	DWORD n = ::GetTickCount() + nMilliSeconds;
	MSG msg;

	while(::GetTickCount() <= n)
	{
		while (::PeekMessage(&msg, _hwnd, 0, 0, PM_NOREMOVE))      
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
CExeWatcherApp* __GetApp()
{
	return (CExeWatcherApp*)AfxGetApp();
}


static HMODULE hModPSAPI = 0;
static PFNENUMPROCESSES EnumProcesses = 0;
static PFNENUMPROCESSMODULES EnumProcessModules = 0;
static PFNGETMODULEFILENAMEEXA GetModuleFileNameExA = 0;
static int __nIDTimer = 0;
CArray<PR, PR> __apr2watch;
int ___iCHECKS=0;


void __do()
{
	__Log("__do\tINF:begin...");
	if(__nIDTimer != 0)
	{
		if(!::KillTimer(NULL, __nIDTimer))
			__Log("__do\tERR:!killtimer:1");
		__nIDTimer = 0;
	}

	__apr2watch.RemoveAll();

	if(!hModPSAPI)	hModPSAPI = LoadLibrary("PSAPI.DLL");

	if(!hModPSAPI)
	{
		__Log("__do\tERR:r.1:hModPSAPI");
		return;
	}

	if(!EnumProcesses)
	{
		EnumProcesses		= (PFNENUMPROCESSES)GetProcAddress( hModPSAPI,"EnumProcesses" );
		EnumProcessModules	= (PFNENUMPROCESSMODULES)GetProcAddress( hModPSAPI, "EnumProcessModules" );
		GetModuleFileNameExA= (PFNGETMODULEFILENAMEEXA)GetProcAddress( hModPSAPI, "GetModuleFileNameExA" );
	}
	if(!EnumProcesses || !EnumProcessModules || !GetModuleFileNameExA)
	{
		__Log("__do\tERR:r.2:!EnumProcesses fu ptr in psapi.dll");
		return;
	}

	DWORD aProcesses[1024], cbNeeded;

	if(!EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		__Log("__do\tERR:r.3:!EnumProcesses from psapi");
		return;
	}

	DWORD cProcesses = cbNeeded / sizeof(DWORD);
	
	CIPString spr2watch(__GetCFG("pr2watch"));
	if (spr2watch.IsEmpty())
		spr2watch = "tomcat5";

	for(DWORD i = 0; i < cProcesses; i++ )
	{
		if(aProcesses[i] < 9) continue;
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);

		if(hProcess)
		{
			HMODULE hMod;
			DWORD cbNeeded;
			if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))	//needs right "PROCESS_VM_READ"
			{
				char szProcessName[1024] = "unknown";
				GetModuleFileNameExA(hProcess, hMod, szProcessName,sizeof(szProcessName));
				CIPString sProcessName(szProcessName);
				CIPFile f;
				f.SetFilePath(sProcessName);
				f.GetName(sProcessName);
				if(sProcessName.CompareNoCase(spr2watch)==0)
				{
					PR pr;
					pr.dwProcessID	= aProcesses[i];
					pr.hMod			= hMod;
					pr.sPathName	= szProcessName;
					__apr2watch.Add(pr);
					//__Log("__do\tINF:sProcessName2watch:"+CIPString(szProcessName));
				}
				else
				{
					//__Log("__do\tINF:sProcessName2ignore:'"+sProcessName+"' \t "+CIPString(szProcessName));
				}
			}
			else
			{
				CIPString s;
				s.Format("pid:%d hProcess:%d",aProcesses[i], hProcess);
				__Log("__do\tWRN!EnumProcessModules:"+s);
			}
			CloseHandle( hProcess );
		}
		else
		{
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0, /* Default language */(LPTSTR) &lpMsgBuf,0,NULL);
			CIPString sSys((LPCTSTR)lpMsgBuf);
			sSys.Remove("\n");sSys.Remove("\n");sSys.Replace('\xD',' ');sSys.Replace('\xA',' ');

			LocalFree(lpMsgBuf);

			CIPString s;
			s.Format("%d",aProcesses[i]);
			__Log("__do\tWRN!OpenProcess:pid:"+s+"\n\tgetlasterror:"+sSys);
		}
	}

	int iapr = __apr2watch.GetSize();
	if (iapr < 4)			//SPECIAL4WHISKEY:4TOMCATS
	{
		__Log("__do\tERR:r.5 ((iapr < 4).apps2watch found!)");
		__nIDTimer = SetTimer(NULL, 2 + GetCurrentProcessId(), 9999, (TIMERPROC)Timer2Proc);
		return;
	}
	if (iapr < 1)
	{
		__Log("__do\tERR:r.4 (no.apps2watch found!)");
		__nIDTimer = SetTimer(NULL, 2 + GetCurrentProcessId(), 9999, (TIMERPROC)Timer2Proc);
		return;
	}
	__nIDTimer = SetTimer(NULL, 2 + GetCurrentProcessId(), 999, (TIMERPROC)Timer2Proc);
	CIPString siapr;
	siapr.FromInt(iapr);
	__Log("__do\tINF:processes found4watch..... ("+siapr+" processes2watch)");
}
double GetRealTime()
{
#if defined(R__MAC)
   return(Double_t)clock() / gTicks;
#elif defined(R__UNIX)
   struct tms cpt;
   Double_t trt =  (Double_t)times(&cpt);
   return trt / (double)gTicks;
#elif defined(R__VMS)
  return(Double_t)clock()/gTicks;
#elif defined(WIN32)
  union
  {
	  FILETIME ftFileTime;
      __int64  ftInt64;
  } ftRealTime; // time the process has spent in kernel mode
  SYSTEMTIME st;
  GetSystemTime(&st);
  SystemTimeToFileTime(&st,&ftRealTime.ftFileTime);
  return (double)ftRealTime.ftInt64 * gTicks;
#endif
}
double GetCPUTime(HANDLE hProcess, int* piTotalMinutesFromProcessStart)
{
#if defined(R__MAC)
   return(Double_t)clock() / gTicks;
#elif defined(R__UNIX)
   struct tms cpt;
   times(&cpt);
   return (Double_t)(cpt.tms_utime+cpt.tms_stime) / gTicks;
#elif defined(R__VMS)
   return(Double_t)clock()/gTicks;
#elif defined(WIN32)

  OSVERSIONINFO OsVersionInfo;

//*-*         Value                      Platform
//*-*  ----------------------------------------------------
//*-*  VER_PLATFORM_WIN32s          Win32s on Windows 3.1
//*-*  VER_PLATFORM_WIN32_WINDOWS       Win32 on Windows 95
//*-*  VER_PLATFORM_WIN32_NT            Windows NT
//*-*
  OsVersionInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
  GetVersionEx(&OsVersionInfo);
  if (OsVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
  {
    DWORD       ret;
    FILETIME    ftCreate,       // when the process was created
                ftExit;         // when the process exited

    union     {FILETIME ftFileTime;
               __int64  ftInt64;
              } ftKernel; // time the process has spent in kernel mode

    union     {FILETIME ftFileTime;
               __int64  ftInt64;
              } ftUser;   // time the process has spent in user mode

    
    ret = GetProcessTimes (hProcess, &ftCreate, &ftExit,
                                     &ftKernel.ftFileTime,
                                     &ftUser.ftFileTime);
    if (ret != TRUE)
	{
      ret = GetLastError ();
      __Log("GetCPUTime\tWRN: Error on GetProcessTimes 0x%lx");
    }
	else
	{
		if(piTotalMinutesFromProcessStart != NULL)
		{
			CTime time_cur = CTime::GetCurrentTime();
			CTime time_pro(ftCreate);
			CTimeSpan timespan = time_cur - time_pro;
			*piTotalMinutesFromProcessStart = timespan.GetTotalMinutes();
			/*
			if(timespan.GetTotalMinutes() < 1)
			{
				__Log("GetCPUTime\tINF:process.now.starting...");
				return 0;
			}
			*/
		}


		/*
		CIPString s;
		s.Format("kernel:%d, user:%d",ftKernel.ftInt64, ftUser.ftInt64);
		__Log("GetCPUTime\tINF:got:"+s);
		*/
	}

    /*
     * Process times are returned in a 64-bit structure, as the number of
     * 100 nanosecond ticks since 1 January 1601.  User mode and kernel mode
     * times for this process are in separate 64-bit structures.
     * To convert to floating point seconds, we will:
     *
     *          Convert sum of high 32-bit quantities to 64-bit int
     */

      return (double) (ftKernel.ftInt64 + ftUser.ftInt64) * gTicks;
  }
  else
      return GetRealTime();

#endif
}


VOID CALLBACK Timer2Proc(	HWND hWnd,		// handle of window for timer messages
							UINT uMsg,		// WM_TIMER message
							UINT idEvent,	// timer identifier
							DWORD dwTime	// current system time
						)
{
	int iapr = __apr2watch.GetSize();
	if (iapr < 1)
	{
		if(!::KillTimer(NULL, idEvent))
			__Log("Timer2Proc\tERR:!killtimer:1");
		__nIDTimer = 0;
		__Log("Timer2Proc\tERR:r.1:__apr2watch.GetSize < 1");
		__do();
		return;
	}
	for(int i=0; i < iapr; i++)
	{
		//if(__apr2watch[i].iHangDeterminated > 0)
		//	continue;

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, __apr2watch[i].dwProcessID);
		if(!hProcess)
		{
			if(!::KillTimer(NULL, idEvent))
				__Log("Timer2Proc\tERR:!killtimer:2");
			__nIDTimer = 0;
			CIPString s;
			s.Format("pid: %d",  __apr2watch[i].dwProcessID);
			__Log("Timer2Proc\tERR:r.2:!OpenProcess:"+s+" \t "+ __apr2watch[i].sPathName);
			__do();
			return;
		}
		int iMinutesAfterStart = 0;
		double dcputime = GetCPUTime(hProcess, &iMinutesAfterStart);
		CloseHandle(hProcess);

		if(iMinutesAfterStart < 2)
		{
			__apr2watch[i].iHangDeterminated = 0;
			//__Log("Timer2Proc\tINF:iMinutesAfterStart<1 \t "+__apr2watch[i].sPathName);
			continue;
		}

		for(int iprt=1; iprt < PR_TIMES_LENGTH; iprt++)
		{
			__apr2watch[i].dwTimes[iprt-1] = __apr2watch[i].dwTimes[iprt];
		}

		CIPString scputime;
		scputime.Format("%.0f",dcputime);
		DWORD dwcputime = (DWORD)atoi(scputime);
		__apr2watch[i].dwTimes[PR_TIMES_LENGTH-1] = dwcputime;

		//scputime.Format("pid:%d, hmod:%d, cputime:'%.0f' == '%f' == '%d' == '%d'", __apr2watch.GetAt(i).dwProcessID,__apr2watch.GetAt(i).hMod, dcputime, dcputime, dwcputime, __apr2watch[i].dwTimes[PR_TIMES_LENGTH-1]);
		//__Log("Timer2Proc\tINF:"+scputime);

		int iHangs		= 0;
		int iNoHangs	= 0;


		for(iprt=1; iprt < PR_TIMES_LENGTH; iprt++)
		{
			if(__apr2watch[i].dwTimes[iprt-1] < __apr2watch[i].dwTimes[iprt])
			{
				//time increasing...
				iHangs++;
			}
			else
			{
				iNoHangs++;
			}
		}

		BOOL bHing = !(__apr2watch[i].sHangLogsDir.IsEmpty());

		if(!bHing)
		{							//hing noch nicht...
			if(iNoHangs > 0)		//hängt jetzt auch nicht...
			{
				__apr2watch[i].iHangDeterminated = 0;
				continue;
			}
			else
			{
									//hing noch nicht + jetzt hängt --> __CopyNewLogs
			}
		}
		else
		{
									//hing schon mal...
			if(iNoHangs > 6)		//jetzt nicht mehr...
			{
				__DelNewLogsDir(__apr2watch[i]);
				scputime.Format("pid:%d, hmod:%d, cputime:'%.0f' == '%f'", __apr2watch.GetAt(i).dwProcessID,__apr2watch.GetAt(i).hMod, dcputime, dcputime);
				__Log("Timer2Proc\tINF:NO_MORE_HANGS:'"+__apr2watch.GetAt(i).sPathName+"' \t "+scputime);
				__apr2watch[i].iHangDeterminated = 0;
			}
			else
			{
									//hing + hängt immer noch --> logs already copied...
				continue;
			}
			continue;
		}

		___iCHECKS=0;

		scputime.Format("pid:%d, hmod:%d, cputime:'%.0f' == '%f'", __apr2watch.GetAt(i).dwProcessID,__apr2watch.GetAt(i).hMod, dcputime, dcputime);
		__Log("Timer2Proc\tINF:HANGS:'"+__apr2watch.GetAt(i).sPathName+"' \t "+scputime);

		__apr2watch[i].iHangDeterminated++;
		
		__CopyNewLogs(__apr2watch[i]);
	}

	___iCHECKS++;
	if(___iCHECKS > 1000)
	{
		___iCHECKS = 0;
		__Log("Timer2Proc\tINF:checking...............");
	}
}
void __DelNewLogsDir(PR& pr)
{
	if(pr.sHangLogsDir.IsEmpty())
	{
		__Log("__DelNewLogs\tERR:isempty:"+pr.sHangLogsDir);
		return;
	}
	CFileFind finder;
	if(!finder.FindFile(pr.sHangLogsDir+"\\*.*"))
	{
		__Log("__DelNewLogs\tERR:fnf:"+pr.sHangLogsDir);
		return;
	}
	BOOL bWorking	= TRUE;
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDots())							continue;
		if(finder.IsDirectory())
		{
			__Log("__DelNewLogs\tERR:subdir:"+pr.sHangLogsDir+" ===> "+finder.GetFileName());
			continue;
		}
		if(!DeleteFile(pr.sHangLogsDir+"\\"+finder.GetFileName()))
			__Log("__DelNewLogs\tERR:!deletefile:"+pr.sHangLogsDir+"\\"+finder.GetFileName());
	}
	if(!RemoveDirectory(pr.sHangLogsDir))
		__Log("__DelNewLogs\tERR:!removedir:"+pr.sHangLogsDir);
	pr.sHangLogsDir.Empty();
}
void __CopyNewLogs(PR& pr)
{
	CIPString sPID;
	sPID.Format("%d", pr.dwProcessID);
	CIPString sCurTime(::__GetCurTime());

	CTime time_cur = CTime::GetCurrentTime();

	CIPString sDate;
	sDate.Format("%d.%d.%d..",time_cur.GetYear(),time_cur.GetMonth(),time_cur.GetDay());


	sCurTime.Replace(':','.');
	CIPString sToDir(__GetMyDir()+"\\"+sDate+sCurTime+"..pid."+sPID);
	CIPFile::MkDirFull(sToDir);
	if(!pr.sHangLogsDir.IsEmpty())
	{
		__Log("__CopyNewLogs\tERR:sHangLogsDir.change:"+pr.sHangLogsDir+" ===> "+sToDir);
	}
	pr.sHangLogsDir = sToDir;

	for(int i=1; i < 6; i++)
	{
		CIPString s;
		s.FromInt(i);
		CIPString slogs("C:\\Programme\\Apache Group\\Tomcat 5.5\\instances\\"+s+"\\logs");
		if(i==5)
		{
			slogs = _T("C:\\Programme\\Apache Group\\Apache2\\logs");
			s = _T("apache");
		}

		CFileFind finder;
		if(!finder.FindFile(slogs+"\\*.*"))
		{
			__Log("__CopyNewLogs\tERR:fnf:"+slogs);
			continue;
		}
		BOOL bWorking	= TRUE;
		int iFileFound	= 0;
		while(bWorking)
		{
			bWorking = finder.FindNextFile();
			if(finder.IsDots())							continue;
			if(finder.IsDirectory())					continue;

			CTime timef;
			finder.GetLastWriteTime(timef);
			CTimeSpan timespan = time_cur - timef;
			if(timespan.GetTotalMinutes() < 2)
			{
				if(!CopyFile(slogs+"\\"+finder.GetFileName(), sToDir+"\\"+s+"__"+finder.GetFileName(), TRUE))
					__Log("__CopyNewLogs\tERR:!copy:'"+slogs+"\\"+finder.GetFileName()+"' ==> '"+sToDir+"\\"+s+"__"+finder.GetFileName()+"'");
			}
		}
	}	
}

int CExeWatcherApp::ExitInstance() 
{
	__Log("ExitInstance\tEND_APPLICATION-----------------");
	return CWinApp::ExitInstance();
}

BOOL __IPLogoff()
{
	UINT _uiToDo = 0;
	CIPString sMode = __GetCFG(_T("mode"));
	sMode.AllTrim();
	sMode.MakeLower();

	__Log("__IPLogoff\tINFO: "+sMode);

	if(sMode == _T("logoff"))
		_uiToDo = EWX_LOGOFF | EWX_FORCE;
	else if(sMode == _T("shutdown"))
		_uiToDo = EWX_SHUTDOWN | EWX_FORCE;
	else if(sMode == _T("reboot"))
		_uiToDo = EWX_REBOOT | EWX_FORCE;
	else if(sMode == _T("poweroff"))
		_uiToDo = EWX_POWEROFF | EWX_FORCE;
	else 
	{
		__Log("__IPLogoff\treturn FALSE 1");
		return FALSE;
	}

    HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 
 
   // Get a token for this process. 
 
   if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
   {
	   __Log("__IPLogoff\treturn FALSE 2");
      //return( FALSE ); 
   }
 
   // Get the LUID for the shutdown privilege. 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
   // Get the shutdown privilege for this process. 
 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
 
   if (GetLastError() != ERROR_SUCCESS) 
   {
	   __Log("__IPLogoff\treturn FALSE 3");
      //return FALSE; 
   }
 
   // Shut down the system and force all applications to close. 
 
   if (!ExitWindowsEx(_uiToDo, 0)) 
   {
	   __Log("__IPLogoff\treturn FALSE 4");
      return FALSE; 
   }

   __Log("__IPLogoff\treturn TRUE");
   return TRUE;
}
