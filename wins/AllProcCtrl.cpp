// AllProcCtrl.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "AllProcCtrl.h"
#include "DlgWindows.h"
#include "DlgFlash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllProcCtrl

CAllProcCtrl::CAllProcCtrl()
{
}

CAllProcCtrl::~CAllProcCtrl()
{
}


BEGIN_MESSAGE_MAP(CAllProcCtrl, CIPProcTree)
	//{{AFX_MSG_MAP(CAllProcCtrl)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAllProcCtrl 

static HMODULE hModPSAPI = 0;
static PFNENUMPROCESSES EnumProcesses = 0;
static PFNENUMPROCESSMODULES EnumProcessModules = 0;
static PFNGETMODULEFILENAMEEXA GetModuleFileNameExA = 0;


void CAllProcCtrl::Fill()
{
	this->Setup();
	this->DeleteAllItems();

	HWND _hwnd	= ::GetDesktopWindow();
	_hwnd		= ::GetWindow(_hwnd, GW_CHILD);
	CWnd* _pwnd	= CWnd::FromHandle(_hwnd);

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
		DWORD _dwProID;
		GetWindowThreadProcessId(_pwnd->m_hWnd, &_dwProID);

		BOOL bFound=FALSE;
		for(int i=0; i < _aWindata.GetSize(); i++)
		{
			if(_aWindata.GetAt(i).m_dwProcessID == _dwProID)
			{
				_pwnd = _pwnd->GetNextWindow(GW_HWNDNEXT);
				bFound = TRUE;
				break;
			}
		}
		if(bFound) continue;
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

		if(hInstance)
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

		dwProcessID = _dwProID;
		if (_sModFN.IsEmpty())
			_sModFN = DisplayFilename(_dwProID);
		else
			_sModFN = _sModFN + " (" + DisplayFilename(_dwProID) + ")";

		if(_sModFN.GetLength() < 5)
		{
			dwProcessID = _dwProID;
			CIPString s;
			s.FromLong((long)dwProcessID);
			_sModFN = s;
		}

		BOOL _bDlgBased = FALSE;
		if(::GetWindowLong(_pwnd->m_hWnd, DWL_DLGPROC))
			_bDlgBased = TRUE;

		WINDATA _wind;
		_wind.m_HWND		= _pwnd->m_hWnd;
		_wind.m_lCount		= 1;
		_wind.m_sTitle		= _sThisWin;
		_wind.m_bEnabled	= _bEnabled;
		_wind.m_sModFN		= _sModFN;
		_wind.m_bDlgBased	= _bDlgBased;
		_wind.m_dwProcessID = dwProcessID;
		_aWindata.Add(_wind);

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
				}
			}
		}
	}

	long l = m_ImageList.Add(__GetMyDir()+"\\w.bmp");

	for(long _lEntr=0; _lEntr < _aWindata.GetSize(); _lEntr++)
	{
		WINDATA* pwind = new WINDATA;
		*pwind = _aWindata.GetAt(_lEntr);
		HTREEITEM h = InsertItem(pwind->m_sModFN, l, l, TVI_ROOT, TVI_LAST); 
		SetItemData(h, (DWORD)pwind);
		if(pwind->m_HWND != NULL)
		{
			HTREEITEM hchild = InsertItem("", l, l, h, TVI_LAST); 
			SetItemData(hchild, (DWORD)NULL);
		}
		//SetItemState(h, INDEXTOSTATEIMAGEMASK(::IsWindowVisible(pwind->m_HWND) ? 2 : 1), LVIS_STATEIMAGEMASK);
	}
}

void CAllProcCtrl::Empty()
{
	this->DeleteAllItems();
}

void CAllProcCtrl::OnLBClick()
{

}

void CAllProcCtrl::OnLBDblClick()
{
	HTREEITEM h = GetSelectedItem();
	if(!h)return;
	WINDATA* pwind	 = (WINDATA*)GetItemData(h);

	CWnd* pw = CWnd::FromHandle(pwind->m_HWND);

	if(!pw)
		return;

	static HMODULE hUser32=NULL;
	static int (__stdcall *fflashWindowEx)(FLASHWINFO *);

	if (!hUser32)
	{
		hUser32=LoadLibrary("USER32.DLL");
		*((void**)&fflashWindowEx)=GetProcAddress(hUser32,"FlashWindowEx");
	}

	CRect r;
	::GetWindowRect(pwind->m_HWND, &r);
	::SetCursorPos(r.left, r.top);

	if (fflashWindowEx)
	{
		CWnd* pwnd = CWnd::FromHandle(pwind->m_HWND);

		{
			FLASHWINFO fi;
			fi.cbSize	= sizeof(fi);
			fi.hwnd		= pwind->m_HWND;
			fi.dwFlags	= FLASHW_ALL;
			fi.uCount	= 2;
			fi.dwTimeout= 0;
			fflashWindowEx(&fi);
		}
	}
	{
		CDlgFlash dlgtop;
		CDlgFlash dlgbtt;
		CDlgFlash dlglft;
		CDlgFlash dlgrgt;

		HRSRC _hrsrc	= ::FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDD_FLASHDLG), RT_DIALOG);
		HGLOBAL _hRes	= ::LoadResource(AfxGetApp()->m_hInstance, _hrsrc);
		dlgtop.CreateIndirect(_hRes, AfxGetMainWnd());
		dlgbtt.CreateIndirect(_hRes, AfxGetMainWnd());
		dlglft.CreateIndirect(_hRes, AfxGetMainWnd());
		dlgrgt.CreateIndirect(_hRes, AfxGetMainWnd());

		RECT rect;
		::GetWindowRect(pwind->m_HWND, &rect);
		//ScreenToClient(&rect);
		CRect rct(rect);

		int iWdth = rct.right - rct.left;
		int iHght = rct.bottom - rct.top;

		dlgtop.MoveWindow(rct.left,rct.top,iWdth,2, FALSE);
		dlglft.MoveWindow(rct.left,rct.top,2,iHght-2,FALSE);
		dlgbtt.MoveWindow(rct.left,rct.bottom,iWdth,2, FALSE);
		dlgrgt.MoveWindow(rct.left+iWdth-2,rct.top,2,rct.bottom-rct.top,FALSE);

		for(int i=0; i < 9; i++)
		{
			dlgtop.ShowWindow(SW_HIDE);
			dlgbtt.ShowWindow(SW_HIDE);
			dlglft.ShowWindow(SW_HIDE);
			dlgrgt.ShowWindow(SW_HIDE);
			::__IPVSleep(71);
			dlgtop.ShowWindow(SW_SHOW);
			dlgbtt.ShowWindow(SW_SHOW);
			dlglft.ShowWindow(SW_SHOW);
			dlgrgt.ShowWindow(SW_SHOW);
			::__IPVSleep(71);
		}

		dlgtop.DestroyWindow();
		dlgbtt.DestroyWindow();
		dlglft.DestroyWindow();
		dlgrgt.DestroyWindow();

		return;

		CDlgFlash _static;
		_static.CreateIndirect(_hRes, AfxGetMainWnd());
		_static.MoveWindow(&rect, TRUE);

		CWnd* pbTop = _static.GetDlgItem(IDC_TOP_B);
		CWnd* pbBtt = _static.GetDlgItem(IDC_BOTTOM_B);
		CWnd* pbLft = _static.GetDlgItem(IDC_LEFT_B);
		CWnd* pbRgt = _static.GetDlgItem(IDC_RIGHT_B);

		
		/*
		CRect rct;
		_static.GetWindowRect(&rct);
		_static.ScreenToClient(&rct);
		if (rct.top < 0)
			rct.top = 0;
		if (rct.left < 0)
			rct.left = 0;
		*/

		CWnd* p = CWnd::FromHandle(::GetDesktopWindow());
		pbTop->SetParent(p);
		pbBtt->SetParent(p);
		pbLft->SetParent(p);
		pbRgt->SetParent(p);

		pbTop->MoveWindow(rct.left,rct.top,iWdth,2, TRUE);
		pbLft->MoveWindow(rct.left,rct.top,2,iHght-2,TRUE);

		pbBtt->MoveWindow(rct.left,rct.bottom,iWdth,2, TRUE);
		pbRgt->MoveWindow(rct.left+iWdth-2,rct.top,2,rct.bottom-rct.top,TRUE);

		//::SetWindowPos(pbTop->m_hWnd, HWND_TOPMOST,0,0,0,0,SWP_NOSIZE);
		//_static.ShowWindow(SW_SHOW);

		for(i=0; i < 9; i++)
		{
			::__IPVSleep(71);
			{
				//_static.DoShow(FALSE,this);
				BOOL bShow = TRUE;

				pbTop->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				pbBtt->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				pbLft->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				pbRgt->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
			}
			::__IPVSleep(71);
			{
				//_static.DoShow(TRUE,this);
				BOOL bShow = FALSE;

				pbTop->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				pbBtt->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				pbLft->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				pbRgt->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
			}
		}
		_static.DestroyWindow();
		{
			FLASHWINFO fi;
			fi.cbSize	= sizeof(fi);
			fi.hwnd		= pwind->m_HWND;
			fi.dwFlags	= FLASHW_ALL;
			fi.uCount	= 2;
			fi.dwTimeout= 0;
			fflashWindowEx(&fi);
		}
	};
}

void CAllProcCtrl::OnRBClick()
{

}
void CAllProcCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	if (pNMTreeView->action != TVE_EXPAND)
		return;

	WINDATA* pwind	 = (WINDATA*)GetItemData(pNMTreeView->itemNew.hItem);
	HTREEITEM hchild = GetNextItem(pNMTreeView->itemNew.hItem, TVGN_CHILD);

	if(!hchild)						return;
	if(GetItemData(hchild) != NULL)	return;

	DeleteItem(hchild);

	long l = m_ImageList.Add(__GetMyDir()+"\\w.bmp");
	
	if(this->GetParentItem(pNMTreeView->itemNew.hItem) == NULL)
	{
		HWND _hwnd	= ::GetDesktopWindow();
		_hwnd		= ::GetWindow(_hwnd, GW_CHILD);
		CWnd* _pwnd	= CWnd::FromHandle(_hwnd);
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
			DWORD _dwProID;
			GetWindowThreadProcessId(_pwnd->m_hWnd, &_dwProID);
			if(pwind->m_dwProcessID != _dwProID)
			{
				_pwnd = _pwnd->GetNextWindow(GW_HWNDNEXT);
				continue;
			}
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

			if(hInstance)
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

			dwProcessID = _dwProID;
			if (_sModFN.IsEmpty())
				_sModFN = DisplayFilename(_dwProID);
			else
				_sModFN = _sModFN + " (" + DisplayFilename(_dwProID) + ")";

			if(_sModFN.GetLength() < 5)
			{
				dwProcessID = _dwProID;
				CIPString s;
				s.FromLong((long)dwProcessID);
				_sModFN = s;
			}

			BOOL _bDlgBased = FALSE;
			if(::GetWindowLong(_pwnd->m_hWnd, DWL_DLGPROC))
				_bDlgBased = TRUE;

			WINDATA* pwindchild		= new WINDATA;
			pwindchild->m_HWND		= _pwnd->m_hWnd;
			pwindchild->m_lCount	= 1;
			pwindchild->m_sTitle	= _sThisWin;
			pwindchild->m_bEnabled	= _bEnabled;
			pwindchild->m_sModFN	= _sModFN;
			pwindchild->m_bDlgBased	= _bDlgBased;
			pwindchild->m_dwProcessID= dwProcessID;

			{
				long l2	= m_ImageList.Add(__GetMyDir()+"\\"+CDlgWindows::GetWinIcon(pwindchild->m_HWND)+".bmp");
				if(l2 < 0)
					l2 = l;

				*pwindchild			= *pwind;
				pwindchild->m_HWND	= _pwnd->m_hWnd;
				_pwnd->GetWindowText(pwindchild->m_sTitle);

				HTREEITEM hChild = InsertItem(CDlgWindows::GetWinTxt(_pwnd->m_hWnd,FALSE), l2, l2, pNMTreeView->itemNew.hItem, TVI_LAST);
				SetItemData(hChild, (DWORD)pwindchild);
				SetItemState(hChild, INDEXTOSTATEIMAGEMASK(::IsWindowVisible(pwindchild->m_HWND) ? 2 : 1), LVIS_STATEIMAGEMASK);
				if(::GetWindow(_pwnd->m_hWnd, GW_CHILD) != NULL)
				{
					HTREEITEM hchildchild = InsertItem("", l, l, hChild, TVI_LAST);
					SetItemData(hchildchild, (DWORD)NULL);
				}
			}
			_pwnd = _pwnd->GetNextWindow(GW_HWNDNEXT);
		}
	}
	else	//NOT ROOT
	{
		HWND hwndchild  = ::GetWindow(pwind->m_HWND, GW_CHILD);
		CWnd* pwndchild	= CWnd::FromHandle(hwndchild);
		while(pwndchild != NULL)
		{
			long l2	= m_ImageList.Add(__GetMyDir()+"\\"+CDlgWindows::GetWinIcon(pwndchild->m_hWnd)+".bmp");
			if(l2 < 0)
				l2 = l;

			WINDATA* pwindchild = new WINDATA;
			*pwindchild			= *pwind;
			pwindchild->m_HWND	= pwndchild->m_hWnd;
			pwndchild->GetWindowText(pwindchild->m_sTitle);

			HTREEITEM hChild = InsertItem(CDlgWindows::GetWinTxt(pwndchild->m_hWnd,FALSE), l2, l2, pNMTreeView->itemNew.hItem, TVI_LAST);

			if(!IsWindow(pwindchild->m_HWND))
				return;

			SetItemData(hChild, (DWORD)pwindchild);
			SetItemState(hChild, INDEXTOSTATEIMAGEMASK(::IsWindowVisible(pwindchild->m_HWND) ? 2 : 1), LVIS_STATEIMAGEMASK);
			if(::GetWindow(pwndchild->m_hWnd, GW_CHILD) != NULL)
			{
				HTREEITEM hchildchild = InsertItem("", l, l, hChild, TVI_LAST);
				SetItemData(hchildchild, (DWORD)NULL);
			}

			pwndchild = pwndchild->GetNextWindow(GW_HWNDNEXT);
		}
	}
}

void CAllProcCtrl::Setup()
{
	static BOOL bSetup = FALSE;
	if(bSetup) return;
	bSetup = TRUE;

	CIPProcTree::Setup();

	m_ImageListStatus.Create(IDB_IMGLIST1, 16, 3, RGB(255, 0, 255));
	SetImageList(&(m_ImageListStatus), LVSIL_STATE);

/*
	HIMAGELIST hImageList2 = ImageList_Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 11);

	// Load 256 colour bitmap containing the images...
	HBITMAP hBitmap2(HBITMAP(LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_IMGLIST),IMAGE_BITMAP,0, 0,LR_COLOR)));
	_ASSERTE(hBitmap2);

	if(hBitmap2)
	{
		// Plonk bitmap into image list...
		ImageList_AddMasked(hImageList2, hBitmap2, RGB(255,0,255));       
		// Destroy bitmap
		DeleteObject(hBitmap2);
	}

	m_ImageListStatus.Attach(hImageList2);
	SetImageList(&m_ImageListStatus, LVSIL_STATE);
	m_ImageListStatus.Detach();
*/
}

void CAllProcCtrl::SetSelectedItemStateIconAndText()
{
	HTREEITEM h = GetSelectedItem();
	if(!h) return;

	if(GetParentItem(h) == NULL)
		return;

	WINDATA* p = (WINDATA*)GetItemData(h);
	if(!p) return;

	SetItemState(h, INDEXTOSTATEIMAGEMASK(::IsWindowVisible(p->m_HWND) ? 2 : 1), LVIS_STATEIMAGEMASK);
	/*
	CString s = _T("");
	CWnd* _pwnd	= CWnd::FromHandle(p->m_HWND);
	_pwnd->GetWindowText(s);
	*/
	this->SetItemText(h,CDlgWindows::GetWinTxt(p->m_HWND,FALSE));
}
