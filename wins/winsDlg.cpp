// winsDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "winsDlg.h"
#include "ipbitmap.h"				//declaration GetHeightFromPoints
#include <winuser.h>
#include <Winable.h>				//declaration GetWindowModuleFileName
#include "RenameDlg.h"
#include "DlgProcesses.h"
#include "DlgWindows.h"
#include "DlgEfficiency.h"
#include "hyperlink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	HFONT m_hfTitel;
// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_ctrlEmail;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
//	afx_msg void OnEmailSt();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EMAIL_ST, m_ctrlEmail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//ON_BN_CLICKED(IDC_EMAIL_ST, OnEmailSt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinsDlg Dialogfeld



CWinsDlg::CWinsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinsDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	WM_TASKBARCREATED = ::RegisterWindowMessage(TEXT("TaskbarCreated"));
}

void CWinsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinsDlg)
	DDX_Control(pDX, IDC_TREE, m_cTree);
	DDX_Control(pDX, IDC_INFO_ST, m_ctrlInfoSt);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_TREE_CHK, m_cTreeChk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinsDlg, CDialog)
	//{{AFX_MSG_MAP(CWinsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_SHOW_B, OnShowB)
	ON_BN_CLICKED(ID_HIDE_B, OnHideB)
	ON_BN_CLICKED(IDC_INFO_ST, OnInfoSt)
	ON_BN_CLICKED(ID_REFRESH_B, OnRefreshB)
	ON_BN_CLICKED(ID_PROCESSES_B, OnShowProcessesB)
	ON_COMMAND(ID__WINDOWS_M, OnWindows)
	ON_COMMAND(ID__EFFICIENCY, OnEfficiency)
	ON_COMMAND(ID__TOPMOST, OnTopMost)
	ON_BN_CLICKED(ID_RENAME_B, OnRenameB)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_CLOSEAPP_B, OnCloseappB)
	ON_WM_RBUTTONUP()
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_BN_CLICKED(IDC_TREE_CHK, OnTreeChk)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnClickTree)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnDblclkTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnRclickTree)
	ON_MESSAGE(WM_TRAY_ICON_NOTIFY_MESSAGE, OnTrayIconClick)
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, OnTaskBarCreated)
	ON_MESSAGE(WM_MESSAFTERONINIT, OnRefreshMessage)
	ON_COMMAND(ID__REFRESHLIST_M, OnRefreshB)
	ON_COMMAND(ID_EXIT_M, OnExit)
	ON_COMMAND(ID__HIDESHOW_M, OnHideShow)
	ON_COMMAND(ID__HIDESHOWAPP_M, OnHideShowApp)
	ON_COMMAND(ID__CHANGEWINCOLOR, OnChangeWinColor)
	ON_COMMAND(ID_EXIT_B, OnExit)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE, OnItemexpandingTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//ON_MESSAGE(WM_MESSAFTERONINIT, OnRefreshB)
/////////////////////////////////////////////////////////////////////////////
// CWinsDlg Nachrichten-Handler

BOOL EnablePrivilege(HANDLE hToken, LPCTSTR szPrivName, BOOL fEnable)
{
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    LookupPrivilegeValue(NULL, szPrivName, &tp.Privileges[0].Luid);
    tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
    AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
    return((GetLastError() == ERROR_SUCCESS));
}

BOOL CWinsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	HANDLE hToken;
    if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		if(!EnablePrivilege(hToken, SE_DEBUG_NAME, TRUE))
			__Log("__do\tWRN:!EnablePrivilege");
		CloseHandle(hToken);
    }
	else
	{
		__Log("__do\tWRN:!OpenProcessToken");
	}


	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	m_ctrlList.Setup();

	PostMessage(WM_MESSAFTERONINIT, 0, 0);

//lauftext
	m_strbrLauf = _T(" win manager by herczeg3725@hotmail.com ");

	i= 0;
	ii=0;

	SetTimer(0, 90, NULL);
//lauftext end
	PostMessage(WM_TASKBARCREATED, 0, 0);

	COLORREF	crBtnColor;
	crBtnColor = ::GetSysColor(COLOR_BTNFACE) + RGB(30, 30, 30);
	m_cTreeChk.SetColor(CButtonSHI::BTNST_COLOR_BK_IN, crBtnColor);
	m_cTreeChk.SetColor(CButtonSHI::BTNST_COLOR_FG_IN, RGB(255,0,0));
	m_cTreeChk.SetColor(CButtonSHI::BTNST_COLOR_FG_OUT, RGB(58,210,165));
	m_cTreeChk.SetFlat(FALSE, TRUE);

	m_ctrlList.ShowWindow(SW_HIDE);
	m_cTree.ShowWindow(SW_SHOW);
	m_cTreeChk.SetCheck(TRUE, TRUE);

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CWinsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CWinsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CWinsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinsDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if(!m_ctrlList.m_hWnd)
		return;
	
	RECT _rect, _rectB;
	GetClientRect(&_rect);
	GetDlgItem(ID_EXIT_B)->GetClientRect(&_rectB);
	long _lWidth	= _rectB.right  - _rectB.left;
	long _lHeight	= _rectB.bottom - _rectB.top;
	long _lVWidth	= _rect.right   - _rect.left;
	long _lVHeight	= _rect.bottom  - _rect.top;

	//recalculate the given client rect
	_rect.right	 -= (_lWidth + 20);
	m_ctrlList.MoveWindow(&_rect);
	m_cTree.MoveWindow(&_rect);

	GetClientRect(&_rect);

	_rect.bottom	= _lVHeight		- 10;
	_rect.top		= _rect.bottom	- _lHeight;
	_rect.right		= _lVWidth		- 10;
	_rect.left		= _rect.right	- _lWidth;

	GetDlgItem(ID_EXIT_B)->MoveWindow(&_rect);


	_rect.top		-= 45;
	_rect.bottom	-= 45;
	GetDlgItem(IDC_TREE_CHK)->MoveWindow(&_rect);

	CRect _rcRahmen;
	_rcRahmen.bottom= _rect.bottom	+ 10;
	_rcRahmen.left	= _rect.left	- 7;
	_rcRahmen.right = _rect.right	+ 7;

	_rect.top		-= 30;
	_rect.bottom	-= 30;
	GetDlgItem(ID_SHOW_B)->MoveWindow(&_rect);
	_rect.top		-= 30;
	_rect.bottom	-= 30;
	GetDlgItem(ID_HIDE_B)->MoveWindow(&_rect);
	_rect.top		-= 30;
	_rect.bottom	-= 30;
	GetDlgItem(ID_RENAME_B)->MoveWindow(&_rect);
	_rect.top		-= 30;
	_rect.bottom	-= 30;
	GetDlgItem(ID_REFRESH_B)->MoveWindow(&_rect);
	_rect.top		-= 30;
	_rect.bottom	-= 30;
	GetDlgItem(ID_CLOSEAPP_B)->MoveWindow(&_rect);

	_rcRahmen.top	= _rect.top - 20;

	GetDlgItem(IDC_RAHMEN_ST)->MoveWindow(&_rcRahmen);

	_rect.top		-= 50;
	_rect.bottom	-= 50;
	_rect.left += (_rect.right - _rect.left)/2;
	GetDlgItem(IDC_INFO_ST)->MoveWindow(&_rect);

	Invalidate(TRUE);											//REPAINT!!!
}

void CWinsDlg::OnShowB() 
{
	WINDATA* _pwind = GetSelItem();
	if(!_pwind) return;

	::ShowWindow(_pwind->m_HWND, SW_SHOWDEFAULT); 
	::UpdateWindow(_pwind->m_HWND);
	if (m_ctrlList.IsWindowVisible())
		m_ctrlList.SetItem(m_ctrlList.GetSelectedItem());
	else
		m_cTree.SetSelectedItemStateIconAndText();
}

void CWinsDlg::OnHideB() 
{
	WINDATA* _pwind = GetSelItem();
	if(!_pwind) return;

	::ShowWindow(_pwind->m_HWND, SW_HIDE); 
	::UpdateWindow(_pwind->m_HWND); 
	if (m_ctrlList.IsWindowVisible())
		m_ctrlList.SetItem(m_ctrlList.GetSelectedItem());
	else
		m_cTree.SetSelectedItemStateIconAndText();
}


void CWinsDlg::OnOK() 
{

}

void CWinsDlg::OnInfoSt() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

LRESULT CWinsDlg::OnRefreshMessage(WPARAM wp, LPARAM lp) 
{
	OnRefreshB();

	return 0;
}

static HMODULE hModPSAPI = 0;
static PFNENUMPROCESSES EnumProcesses = 0;
static PFNENUMPROCESSMODULES EnumProcessModules = 0;
static PFNGETMODULEFILENAMEEXA GetModuleFileNameExA = 0;

void CWinsDlg::OnRefreshB() 
{
	m_cTree.Empty();
	m_ctrlList.DeleteAllItems();
	OnSize(0,0,0);

	if(!m_ctrlList.IsWindowVisible())
	{
		m_cTree.Fill();
		return;
	}

	HWND _hwnd = ::GetDesktopWindow();
	_hwnd = ::GetWindow(_hwnd, GW_CHILD);
	CWnd* _pwnd=NULL;
	_pwnd = CWnd::FromHandle(_hwnd);

	CArray<WINDATA, WINDATA> _aWindata;
	_aWindata.RemoveAll();
	CIPString sMe(_T(""));

	{
		LPTSTR _szfn;
		_szfn	= (LPTSTR)malloc(1111); 
		ZeroMemory(_szfn, 1111);
		if(::GetModuleFileName(NULL, _szfn, 1111))
			sMe = _szfn;
		::free(_szfn);
	}

	while(_pwnd)
	{
//name
		CString _sThisWin = _T("");
		_pwnd->GetWindowText(_sThisWin);
		_sThisWin.TrimLeft();
		_sThisWin.TrimRight();
//enabled
		BOOL _bEnabled = ::IsWindowEnabled(_pwnd->m_hWnd);
//modfn + processid
		HINSTANCE hInstance = (HINSTANCE) ::GetWindowLong(_pwnd->m_hWnd, GWL_HINSTANCE);
		CIPString _sModFN(_T(""));
		DWORD dwProcessID = NULL;

		/*if (GetVersion() < 0x80000000)              // Windows NT/2000, XP
		{
			DWORD _dwProID;
			GetWindowThreadProcessId(_pwnd->m_hWnd, &_dwProID);
			dwProcessID = _dwProID;
/*			CIPString s;
			s.FromLong((long)dwProcessID);
			_sModFN = s;
* /			_sModFN = DisplayFilename(_dwProID);
			//::GetModuleFileName(
		}
		else */if(hInstance/* && _pwnd->m_hWnd*/)
		{
			LPTSTR _szfn;
			_szfn	= (LPTSTR)malloc(1111); 
			ZeroMemory(_szfn, 1111);
			if(::GetModuleFileName(hInstance, _szfn, 1111) != 0)
				_sModFN = _szfn;
			::free(_szfn);
			if((_sModFN.GetLength() < 4) || ((this != _pwnd) && (_sModFN.CompareNoCase(sMe) == 0)))
				_sModFN.Empty();
		}
		//if(_sModFN.IsEmpty())
		{
			//if (GetVersion() < 0x80000000)              // Windows NT/2000, XP
			{
				DWORD _dwProID;
				GetWindowThreadProcessId(_pwnd->m_hWnd, &_dwProID);
				dwProcessID = _dwProID;
				//CIPString s;
				//s.FromLong((long)dwProcessID);
				//_sModFN = s;
				if(_sModFN.IsEmpty())
					_sModFN = DisplayFilename(_dwProID);
				else
					_sModFN = _sModFN + " (" + DisplayFilename(_dwProID) + ")";
			}
			if(_sModFN.GetLength() < 5)
			{
				DWORD _dwProID;
				GetWindowThreadProcessId(_pwnd->m_hWnd, &_dwProID);
				dwProcessID = _dwProID;
				CIPString s;
				s.FromLong((long)dwProcessID);
				_sModFN = s;
			}
		}

//dlg based
		BOOL _bDlgBased = FALSE;
		if(::GetWindowLong(_pwnd->m_hWnd, DWL_DLGPROC))
			_bDlgBased = TRUE;
//add to array
		//if(this != _pwnd)			//me not!
		{
			/*
			if(_sThisWin.IsEmpty())
				_sThisWin = _T("--- win without name ---");
			*/
			BOOL _bThere = FALSE;
			long _lThere = -1;
			/*
			for(int _iEntries=0; _iEntries < _aWindata.GetSize(); _iEntries++)
			{
				CString _sItem = _aWindata.GetAt(_iEntries).m_sTitle;
				if(_sItem == _sThisWin)
				{
					_bThere = TRUE;
					_lThere = (long)_iEntries;
				}
			}
			*/
			if(!_bThere)
			{
				WINDATA _wind;
				_wind.m_HWND		= _pwnd->m_hWnd;
				_wind.m_lCount		= 1;
				_wind.m_sTitle		= _sThisWin;
				_wind.m_bEnabled	= _bEnabled;
				_wind.m_sModFN		= _sModFN;
				_wind.m_bDlgBased	= _bDlgBased;
				_wind.m_dwProcessID = dwProcessID;
				_aWindata.Add(_wind);
			}
			else
			{
				WINDATA _wind = _aWindata.GetAt(_lThere);
				_wind.m_lCount++;
				if(!_wind.m_bEnabled && _bEnabled)
					_wind.m_bEnabled = _bEnabled;
				if(_wind.m_sModFN.Find(_sModFN) < 0)
					_wind.m_sModFN += _T("; ")+_sModFN;
				_aWindata.SetAt(_lThere, _wind);
			}
		}
		_pwnd = _pwnd->GetNextWindow(GW_HWNDNEXT);
	}
	{
		if(!hModPSAPI)	hModPSAPI = LoadLibrary("PSAPI.DLL");
		if (hModPSAPI)
		if(!EnumProcesses)
		{
			EnumProcesses		= (PFNENUMPROCESSES)GetProcAddress( hModPSAPI,"EnumProcesses" );
			EnumProcessModules	= (PFNENUMPROCESSMODULES)GetProcAddress( hModPSAPI, "EnumProcessModules" );
			GetModuleFileNameExA= (PFNGETMODULEFILENAMEEXA)GetProcAddress( hModPSAPI, "GetModuleFileNameExA" );
		}
		if (EnumProcesses)
		{
			DWORD aProcesses[1024], cbNeeded;
			if(EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded))
			{
				DWORD cProcesses = cbNeeded / sizeof(DWORD);
				for(DWORD i = 0; i < cProcesses; i++ )
				{
					if(aProcesses[i] < 9) continue;
					{
						BOOL bFound=FALSE;
						for(int iwd=0; iwd < _aWindata.GetSize(); iwd++)
						{
							if(_aWindata.GetAt(iwd).m_dwProcessID == aProcesses[i])
							{
								bFound = TRUE;
								break;
							}
						}
						if(bFound) continue;
					}
					HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
					if(hProcess)
					{
						HMODULE hMod;
						DWORD cbNeeded;
						CIPString _sModFN = DisplayFilename(aProcesses[i]);

						if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))	//needs right "PROCESS_VM_READ"
						{
							char szProcessName[1024] = "unknown";
							GetModuleFileNameExA(hProcess, hMod, szProcessName,sizeof(szProcessName));
							CIPString sProcessName(szProcessName);
							_sModFN = sProcessName;
						}
						WINDATA _wind;
						_wind.m_HWND		= NULL;
						_wind.m_lCount		= 1;
						_wind.m_sTitle		= _sModFN;
						_wind.m_bEnabled	= FALSE;
						_wind.m_sModFN		= _sModFN;
						_wind.m_bDlgBased	= FALSE;
						_wind.m_dwProcessID = aProcesses[i];
						_aWindata.Add(_wind);
					}
					else
					{
						AfxMessageBox("3");
					}
				}
			}
			else
			{
				AfxMessageBox("2");
			}
		}
		else
		{
			AfxMessageBox("1");
		}
	}

	for(long _lEntr=0; _lEntr < _aWindata.GetSize(); _lEntr++)
		m_ctrlList.AddItem(&_aWindata.GetAt(_lEntr));

	m_ctrlList.OnColumnclick(NULL,NULL);
}
/*
void CAboutDlg::OnEmailSt() 
{
	ShellExecute( NULL, NULL, _T("mailto:herczeg3725@hotmail.com"), NULL, NULL, SW_SHOW);
}
*/
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_hfTitel = CreateFont(GetHeightFromPoints(10), 0, 0, 0, FW_BOLD,
                          1, 1, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                          DEFAULT_PITCH,
                          TEXT("Arial"));

	//SendDlgItemMessage(IDC_EMAIL_ST, WM_SETFONT, (WPARAM)m_hfTitel, 0L);
	
	return TRUE;
}

void CWinsDlg::OnRenameB()
{
	WINDATA* _pwind = GetSelItem();
	if(!_pwind) return;

	if(_pwind->m_HWND == NULL) return;

	CWnd* _pwnd = NULL;
	_pwnd = CWnd::FromHandle(_pwind->m_HWND);
	CString _sThisWin = _T("");
	_pwnd->GetWindowText(_sThisWin);

	CRenameDlg _dlg;
	_dlg.m_sTxt = _sThisWin;
	if(_dlg.DoModal() != IDOK)
		return;

	_pwnd->SetWindowText(_dlg.m_sTxt);
	_pwnd->UpdateWindow();
	_pwnd->RedrawWindow();

	if (m_ctrlList.IsWindowVisible())
		m_ctrlList.SetItem(m_ctrlList.GetSelectedItem());
	else
		m_cTree.SetSelectedItemStateIconAndText();
}

void CWinsDlg::Lauf()
{
	CString _inE;
	//es sollte in Resourcen "kein Umbruch" angeklickt sein, wenn edit-field
	GetWindowText(_inE);

	RECT _rct;
	GetWindowRect(&_rct);
	long _st_laenge = _rct.right - _rct.left;
	long _grenze = _st_laenge - m_strbrLauf.GetLength();

	long iii = _grenze/(m_strbrLauf.GetLength());
	if(iii < 1)
		iii = 1;

	if(ii < iii)
	{
		if(i < m_strbrLauf.GetLength())
		{
			_inE = m_strbrLauf.GetAt((m_strbrLauf.GetLength()-1) - i) + _inE;
			_inE = _inE.Left(_st_laenge);
			i++;
		}
		else
		{
			_inE = " " + _inE;
			_inE = _inE.Left(_st_laenge);
			ii++;
		}
		SetWindowText(_inE);
	}
	else
	{
		ii = 0;
		i  = 0;
	}
}

void CWinsDlg::OnTimer(UINT nIDEvent) 
{
	Lauf();

	CDialog::OnTimer(nIDEvent);
}


LRESULT CWinsDlg::OnTrayIconClick(WPARAM wp, LPARAM lp)
{
	UINT _uMouseMsg = (UINT) lp; 
 
    if (_uMouseMsg == WM_RBUTTONDOWN) 
	{ 
		CMenu _me;
		CMenu* _pme;
		_me.LoadMenu(IDR_TASKBARMENU);

		CPoint pt;
		GetCursorPos(&pt);

		_pme = _me.GetSubMenu(0);

		_pme->GetSubMenu(1);
		CIPString _st;
		_pme->GetMenuString(1, _st, 0);

		if(::IsWindowVisible(this->m_hWnd))
			_pme->ModifyMenu(1, MF_BYPOSITION, ID__HIDESHOW_M, "Hide");
		else
			_pme->ModifyMenu(1, MF_BYPOSITION, ID__HIDESHOW_M, "Show");

		_pme->TrackPopupMenu(TPM_BOTTOMALIGN | TPM_LEFTBUTTON, pt.x, pt.y+200, this);
	}
	return 1;
}


LRESULT CWinsDlg::OnTaskBarCreated(WPARAM wp, LPARAM lp)
{
	//tray-icon
	NOTIFYICONDATA _nid;
	_nid.cbSize = sizeof(NOTIFYICONDATA);
	_nid.uID = IDR_MAINFRAME + 1234;
	_nid.uCallbackMessage = WM_TRAY_ICON_NOTIFY_MESSAGE;
	_nid.szTip[0] = 0;
	lstrcpyn(_nid.szTip, m_strbrLauf, sizeof(_nid.szTip));
	_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
	_nid.hWnd = this->m_hWnd;			//important!
	
	HICON _hiTry = (HICON)LoadImage(AfxGetApp()->m_hInstance,
								MAKEINTRESOURCE(IDR_MAINFRAME),
								IMAGE_ICON,
								16,
								16,
								LR_DEFAULTCOLOR);
								
	_nid.hIcon = _hiTry;

	Shell_NotifyIcon(NIM_ADD, &_nid);

	if (_hiTry) 
		DestroyIcon(_hiTry);

	return 1;
}

void CWinsDlg::OnDestroy() 
{
	//remove taskbar-icon
	NOTIFYICONDATA tnid; 
    tnid.cbSize = sizeof(NOTIFYICONDATA); 
    tnid.hWnd = this->m_hWnd; 
    tnid.uID = IDR_MAINFRAME + 1234;
    Shell_NotifyIcon(NIM_DELETE, &tnid); 

	CDialog::OnDestroy();	
}

void CWinsDlg::OnExit()
{
	CDialog::OnCancel();
	
	exit(0);
}

void CWinsDlg::OnHideShow()
{
	if(::IsWindowVisible(this->m_hWnd))
	{
		CSystemTray::MinimiseToTray(this, TRUE);
		this->ShowWindow(FALSE);
	}
	else
	{
		CSystemTray::MaximiseFromTray(this, TRUE);
		this->ShowWindow(TRUE);
	}
}

void CWinsDlg::OnCloseappB() 
{
	WINDATA* _pwind = GetSelItem();
	if(!_pwind) return;

	if(_pwind->m_dwProcessID)
	{
		HANDLE _hProcess = OpenProcess( PROCESS_TERMINATE, FALSE, _pwind->m_dwProcessID);
		if(_hProcess)
		{
			if(!TerminateProcess(_hProcess, 0))
			{
				CloseHandle(_hProcess);
			}
			else
			{
				CloseHandle(_hProcess);
				return;
			}
		}
	}

	CWnd* _pwnd = NULL;
	_pwnd = CWnd::FromHandle(_pwind->m_HWND);
	::SendNotifyMessage(_pwind->m_HWND, WM_CLOSE, 0,0);
	::SendNotifyMessage(_pwind->m_HWND, WM_QUIT, 0,0);
}

void CWinsDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{	
	CDialog::OnRButtonUp(nFlags, point);

	CMenu _me;
	CMenu* _pme;
	_me.LoadMenu(IDR_TASKBARMENU);

	CPoint pt;
	GetCursorPos(&pt);

	_pme = _me.GetSubMenu(0);

	_pme->GetSubMenu(1);
	CIPString _st;
	_pme->GetMenuString(1, _st, 0);

	if(::IsWindowVisible(this->m_hWnd))
		_pme->ModifyMenu(1, MF_BYPOSITION, ID__HIDESHOW_M, "Hide");
	else
		_pme->ModifyMenu(1, MF_BYPOSITION, ID__HIDESHOW_M, "Show");

	_pme->TrackPopupMenu(TPM_TOPALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
}

void CWinsDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//HTREEITEM _hti = pNMTreeView->itemNew.hItem;

    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	CMenu _me;
	CMenu* _pme;
	_me.LoadMenu(IDR_LISTMENU);

	CPoint pt;
	GetCursorPos(&pt);

	_pme = _me.GetSubMenu(0);

	_pme->GetSubMenu(1);
	CIPString _st;
	_pme->GetMenuString(1, _st, 0);

	if(_pwind->m_HWND)
	{
		_pme->EnableMenuItem(1, MF_ENABLED);
		if(::IsWindowVisible(_pwind->m_HWND))
			_pme->ModifyMenu(1, MF_BYPOSITION, ID__HIDESHOWAPP_M, "Hide");
		else
			_pme->ModifyMenu(1, MF_BYPOSITION, ID__HIDESHOWAPP_M, "Show");

		{
			BOOL bIsTopMost = FALSE;

			CWnd* pWnd		= CWnd::FromHandle(_pwind->m_HWND);
			DWORD dwStyle	= pWnd->GetStyle();
			DWORD dwExStyle	= pWnd->GetExStyle();

			if(pWnd->GetExStyle() & WS_EX_TOPMOST)
				bIsTopMost = TRUE;

			_pme->ModifyMenu(2, MF_BYPOSITION, ID__TOPMOST, bIsTopMost ? "set NonTopMost" : "set TopMost");
		}
	}
	else
	{
		_pme->EnableMenuItem(1, MF_DISABLED);
	}

	_pme->TrackPopupMenu(TPM_TOPALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
	if(pResult)*pResult = 0;
}

void CWinsDlg::OnHideShowApp()
{
    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	if(::IsWindowVisible(_pwind->m_HWND))
		this->OnHideB();
	else
		this->OnShowB();
}

void CWinsDlg::OnShowProcessesB()
{
    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	CDlgProcesses _dlg(_pwind->m_dwProcessID, NULL);
	_dlg.DoModal();
}

void CWinsDlg::OnWindows()
{
    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	CDlgWindows _dlg(_pwind->m_dwProcessID, _pwind->m_HWND, NULL);
	_dlg.DoModal();
}

void CWinsDlg::OnEfficiency()
{
    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	CDlgEfficiency _dlg(_pwind,NULL);
	_dlg.DoModal();
}


void CWinsDlg::OnTreeChk() 
{
	if (GetDlgItem(IDC_TREE_CHK)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	{
		m_ctrlList.ShowWindow(SW_HIDE);
		m_cTree.ShowWindow(SW_SHOW);
		m_cTreeChk.SetCheck(TRUE, TRUE);
	}
	else
	{
		m_ctrlList.ShowWindow(SW_SHOW);
		m_cTree.ShowWindow(SW_HIDE);
		m_cTreeChk.SetCheck(FALSE, TRUE);
	}
	OnRefreshB();
}

WINDATA* CWinsDlg::GetSelItem()
{
	if(m_ctrlList.IsWindowVisible())
	{
		if(m_ctrlList.GetSelectedItem() < 0)
			return NULL;
		WINDATA* _pwind = (WINDATA*)m_ctrlList.GetItemData(m_ctrlList.GetSelectedItem());
		return _pwind;
	}
	HTREEITEM h = m_cTree.GetSelectedItem();
	if(!h) return NULL;

	//if(m_cTree.GetParentItem(h) == NULL)
	//	return NULL;
	
	return (WINDATA*)m_cTree.GetItemData(h);
}

void CWinsDlg::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cTree.OnLBClick();
	if(pResult)*pResult = 0;
}

void CWinsDlg::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cTree.OnLBDblClick();
	if(pResult)*pResult = 0;
}

void CWinsDlg::OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnRclickList(0,0);
	m_cTree.OnRBClick();
	if(pResult)*pResult = 0;
}

void CWinsDlg::OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_cTree.OnItemexpanding(pNMHDR, pResult);
	
	if(pResult)*pResult = 0;
}

void CWinsDlg::OnTopMost()
{
    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	if(!::IsWindow(_pwind->m_HWND)) return;

	BOOL bIsTopMost = FALSE;

	CWnd* pWnd		= CWnd::FromHandle(_pwind->m_HWND);
	DWORD dwStyle	= pWnd->GetStyle();
	DWORD dwExStyle	= pWnd->GetExStyle();

	if(pWnd->GetExStyle() & WS_EX_TOPMOST)
		bIsTopMost = TRUE;

	::SetWindowPos(_pwind->m_HWND, (bIsTopMost ? HWND_NOTOPMOST : HWND_TOPMOST), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	
	pWnd->SetWindowPos(bIsTopMost ? &wndNoTopMost : &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}


HHOOK g_hhook	= NULL;
HWND  g_hWnd	= NULL;
HBRUSH g_hBrush = CreateSolidBrush(RGB(255,0,0));	//red
LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	SetClassLong(g_hWnd, GCL_HBRBACKGROUND, (LONG)g_hBrush);
	return(CallNextHookEx(g_hhook, nCode, wParam, lParam));
}
void CWinsDlg::OnChangeWinColor()
{
    WINDATA* _pwind = GetSelItem();
    if(!_pwind) return;

	if(!::IsWindow(_pwind->m_HWND)) return;

/*
	//HBRUSH hBrushNow = (HBRUSH)::GetClassLong(_pwind->m_HWND, GCL_HBRBACKGROUND);
	//HGDIOBJ GetStockObject(WHITE_BRUSH);

	g_hWnd	= _pwind->m_HWND;
	g_hhook = SetWindowsHookEx(WH_MSGFILTER, GetMsgProc, NULL, GetCurrentThreadId());
	if(!g_hhook)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),0, (LPTSTR) &lpMsgBuf, 0, NULL);
		MessageBox((LPCTSTR)lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
*/
	//if(SetClassLong(_pwind->m_HWND, GCL_HBRBACKGROUND, (DWORD)g_hBrush) == 0)
	if(SetClassLong(_pwind->m_HWND, GCL_HBRBACKGROUND, (DWORD)g_hBrush) == 0)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),0, (LPTSTR) &lpMsgBuf, 0, NULL);
		MessageBox((LPCTSTR)lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	::InvalidateRect(_pwind->m_HWND,0,TRUE);
}

