// DlgEfficiency.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "ipfile.h"
#include "perfcounters.h"
#include "DlgEfficiency.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEfficiency 


CDlgEfficiency::CDlgEfficiency(WINDATA* _pwind, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEfficiency::IDD, pParent), m_meter(3)
{
	//{{AFX_DATA_INIT(CDlgEfficiency)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	m_pwind = _pwind;

	m_iMax =0;
	m_iTimerCalls=0;
	m_LASTdcputime_curpr=0;
	m_LASTdrealime_curpr=0;
	m_LASTdcputime_pr=0;
}


void CDlgEfficiency::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEfficiency)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEfficiency, CDialog)
	//{{AFX_MSG_MAP(CDlgEfficiency)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgEfficiency 

void CDlgEfficiency::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgEfficiency::OnInitDialog() 
{
	CDialog::OnInitDialog();

	{
		CRect rect;
		GetWindowRect(rect);
		//GetDlgItem(IDC_SCOPE_D)->DestroyWindow();
		ScreenToClient(rect);
		rect.top += 19;
		m_meter.Create(WS_VISIBLE | WS_CHILD, rect, this, IDC_SCOPE_D);
	}
	m_meter.SetYUnits("Y Achse");
	//m_meter.SetBackgroundColor(COLORREF());	// Background
	//m_meter.SetGridColor(COLORREF());			// Grid
	//m_meter.SetPlotColor(COLORREF(), 0);
	//m_meter.SetPlotColor(COLORREF(), 1);
	//m_meter.SetPlotColor(COLORREF(), 2);
	m_meter.SetYUnits("Y Units");
	m_meter.SetXUnits("X Units");
	m_meter.SetLegendLabel("dcputime_curpr", 0);
	m_meter.SetLegendLabel("drealime_curpr", 1);
	m_meter.SetLegendLabel("dcputime_pr"   , 2);

	double dPlotDataDown[3];
	dPlotDataDown[0] = 0;
	dPlotDataDown[1] = 0;
	dPlotDataDown[2] = 0;
	m_meter.AppendPoints(dPlotDataDown);

	m_iMax = 1;
	m_meter.SetRange(0, m_iMax, 0);
	m_meter.SetRange(0, m_iMax, 1);
	m_meter.SetRange(0, m_iMax, 2);

	m_meter.InvalidateCtrl();

	SetTimer(7353, 400, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgEfficiency::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);	

	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
	rect.top += 19;
	m_meter.MoveWindow(rect, TRUE);
}

const double gTicks = 1.0e-7;

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
double GetCPUTime(HANDLE hProcess)
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

void CDlgEfficiency::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	HANDLE hProcess = GetCurrentProcess();
	double dcputime_curpr = GetCPUTime(hProcess);
	if (dcputime_curpr < 0.001)
		dcputime_curpr = 0.001;
	double drealime_curpr = GetRealTime();
	if (drealime_curpr < 0.001)
		drealime_curpr = 0.001;

	hProcess = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, this->m_pwind->m_dwProcessID);
	if(!hProcess)
	{
		KillTimer(7353);
		return;
	}

	double dcputime_pr = GetCPUTime(hProcess);
	if (dcputime_pr < 0.001)
		dcputime_pr = 0.001;
	CloseHandle(hProcess);

	int iMax = (int)dcputime_curpr;
	if (iMax < (int)drealime_curpr)
		iMax = (int)drealime_curpr;
	if (iMax < (int)dcputime_pr)
		iMax = (int)dcputime_pr;
	if (iMax > 1)
		iMax = 1;
	if (iMax > m_iMax)
	{
		m_iMax = iMax;
		if (m_iMax > 1)
			m_iMax = 1;
		m_meter.SetRange(0, m_iMax, 0);
		m_meter.SetRange(0, m_iMax, 1);
		m_meter.SetRange(0, m_iMax, 2);
		m_meter.InvalidateCtrl();
	}

	double dcputime_curpr_last = dcputime_curpr;
	double drealime_curpr_last = drealime_curpr;
	double dcputime_pr_last	   = dcputime_pr;
	if(m_iTimerCalls > 0)
	{
		dcputime_curpr = dcputime_curpr - m_LASTdcputime_curpr;
		drealime_curpr = drealime_curpr - m_LASTdrealime_curpr;
		dcputime_pr	   = dcputime_pr	- m_LASTdcputime_pr;
	}
	m_LASTdcputime_curpr = dcputime_curpr_last;
	m_LASTdrealime_curpr = drealime_curpr_last;
	m_LASTdcputime_pr	 = dcputime_pr_last;
	m_iTimerCalls++;


	double dPlotDataDown3[3];
	dPlotDataDown3[0] = dcputime_curpr;
	dPlotDataDown3[1] = drealime_curpr;
	dPlotDataDown3[2] = dcputime_pr;
	m_meter.AppendPoints(dPlotDataDown3);

	return;


//222222222222222222222222222222
    m_usage;

	CIPString sTool(this->m_pwind->m_sModFN);
	CIPFile f;
	f.SetFilePath(sTool);
	f.GetName(sTool);

	CCpuUsage* pusage = &m_usage;

	//CCpuUsage usage;
	//CCpuUsage* pusage = &usage;

	int iToal = pusage->GetCpuUsage();
	int iTool = pusage->GetCpuUsage(this->m_pwind->m_dwProcessID);

	if(iToal < 1)	iToal = 1;
	if(iToal >99)	iToal = 99;
	if(iTool < 1)	iTool = 1;
	if(iTool >99)	iTool = 99;

	if (iToal == iTool && iTool == 1)
		iToal = 2;


	double dPlotDataDown[2];
	dPlotDataDown[0] = iToal;
	dPlotDataDown[1] = iTool;

	if(m_iTimerCalls < 99)
	{
		CIPString s;
		s.Format("cpuusage-all: \t %d.000000 \t cpuusage:"+sTool+": \t %d.000000",iToal,iTool);
		__Log("DLG.EFFICIENCY\tINF:(1)"+s);
		s.Format("cpuusage-all: \t %f  \t cpuusage:"+sTool+": \t %f",dPlotDataDown[0],dPlotDataDown[1]);
		__Log("DLG.EFFICIENCY\tINF:(2)"+s);
	}


	m_meter.AppendPoints(dPlotDataDown);
}
