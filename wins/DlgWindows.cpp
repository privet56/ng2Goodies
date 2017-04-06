// DlgWindows.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "WinsDlg.h"
#include "DlgWindows.h"
#include "DlgFlash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgWindows 


CDlgWindows::CDlgWindows(DWORD dwProcID, HWND h, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWindows::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWindows)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	this->m_dwProcID = dwProcID;
	this->m_HWND = h;
}


void CDlgWindows::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWindows)
	DDX_Control(pDX, IDC_WIN_TREE, m_oTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWindows, CDialog)
	//{{AFX_MSG_MAP(CDlgWindows)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_DBLCLK, IDC_WIN_TREE, OnDblclkTree)
	ON_MESSAGE(WM_MESSAFTERONINIT, OnFillTree)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_WIN_TREE, OnItemexpandingWinTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgWindows 

BOOL CDlgWindows::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgWindows::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_oTree.m_hWnd == NULL)
		return;

	RECT _rct;
	GetClientRect(&_rct);	

	m_oTree.MoveWindow(&_rct);	
}

LRESULT CDlgWindows::OnFillTree(WPARAM wp, LPARAM lp) 
{
	if(!this->IsWindowVisible())
	{
		::__IPVSleep(1);
		PostMessage(WM_MESSAFTERONINIT, 0, 0);
		return 0;
	}

	m_oTree.Setup();

	long l		= m_oTree.m_ImageList.Add(__GetMyDir()+"\\1.bmp");
	HTREEITEM h = NULL;

	if(m_HWND != 0)
	{
		h = m_oTree.InsertItem(GetWinTxt(m_HWND), l, l, TVI_ROOT, TVI_LAST);
		if(::GetWindow(m_HWND, GW_CHILD) != NULL)
			m_oTree.InsertItem("", l, l, h, TVI_LAST);
		m_oTree.SetItemData(h, (DWORD)m_HWND);
	}
	else
	{
		tagPROCWINS pwnds;
		pwnds.m_dwProcessID = this->m_dwProcID;
		pwnds.m_ahWnds.RemoveAll();

		EnumWindows(wndEnumProc, (LPARAM)&pwnds);			// Find a window for this process id

		for(int i=0; i < pwnds.m_ahWnds.GetSize(); i++)
		{
			long l2	= m_oTree.m_ImageList.Add(__GetMyDir()+"\\"+GetWinIcon(pwnds.m_ahWnds.GetAt(i))+".bmp");
			if(l2 < 0)
				l2 = l;
			h = m_oTree.InsertItem(GetWinTxt(pwnds.m_ahWnds.GetAt(i)), l2, l2, TVI_ROOT, TVI_LAST);
			if(::GetWindow(pwnds.m_ahWnds.GetAt(i), GW_CHILD) != NULL)
				m_oTree.InsertItem("", l, l, h, TVI_LAST);
			m_oTree.SetItemData(h, (DWORD)pwnds.m_ahWnds.GetAt(i));
		}
	}
	return 0;
}

void CDlgWindows::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	::__IPVSleep(1);
	PostMessage(WM_MESSAFTERONINIT, 0, 0);	
}

int CALLBACK wndEnumProc(HWND hwnd, LPARAM lParam)
{
	tagPROCWINS* pwnds = (tagPROCWINS*)(lParam);
	if((lParam == NULL) || (pwnds->m_dwProcessID == 0))
	{
		return TRUE;
	}
	//Check window
	DWORD dwProcessId=0;
	DWORD dwThreadId =0;
	dwThreadId = GetWindowThreadProcessId(hwnd, &dwProcessId);

	if(dwProcessId == pwnds->m_dwProcessID)
	{
		pwnds->m_ahWnds.Add(hwnd);
		return FALSE;
	}

	return TRUE;
}

#include <afxcview.h>
#include <afxhtml.h>

CIPString CDlgWindows::GetWinTxt(HWND hwnd, BOOL bWithhwnd/*=TRUE*/)
{
	CIPString s(_T(""));
	CIPString shwnd;
	shwnd.FromLong((long)hwnd);
	::GetWindowText(hwnd, s.GetBuffer(256), 255);
	s.ReleaseBuffer();
	s.AllTrim();

	if(!s.IsEmpty())
		s = "==>\"" + s + "\"";

	CIPString sWndStyle(_T(""));

	TCHAR lpszClassName[255];
	GetClassName(hwnd, lpszClassName, 255);
	if(_tcscmp(lpszClassName, _T("Button")) == 0)
	{
		CButton* b = (CButton*)CWnd::FromHandle(hwnd);
		if(b && b->m_hWnd)
		{
			UINT uStyle = b->GetButtonStyle();
			if (uStyle & BS_PUSHBUTTON)
			{
			   //sWndStyle = _T("BUTTON");
			}
			else
			{
				if (uStyle & BS_RADIOBUTTON)
				{
				   //sWndStyle = _T("RADIOBUTTON");
				}
				else if (uStyle & BS_CHECKBOX)
				{
				   //sWndStyle = _T("CHECKBOX");
				}
				else if (uStyle & BS_3STATE)
				{
				   sWndStyle = _T("3STATE");
				}
				if(b->GetCheck()==1)
					sWndStyle+=_T("(checked)");
			}
		}
	}
	else if(_tcscmp(lpszClassName, _T("ScrollBar")) == 0)
	{
		CScrollBar* b = (CScrollBar*)CWnd::FromHandle(hwnd);
		if(b && b->m_hWnd != NULL)
		{
			SCROLLINFO si;
			b->GetScrollInfo(&si, SIF_ALL);
			sWndStyle.Format("min:%d, max:%d, pos:%d", si.nMin, si.nMax, si.nPos);
		}
	}
	else if(_tcscmp(lpszClassName, _T("Static")) == 0)
	{
		//CStatic b;
		//b.FromHandle(hwnd);
	}
	else if(_tcscmp(lpszClassName, _T("Edit")) == 0)
	{
		//CEdit b;
		//b.FromHandle(hwnd);
	}
	else if(_tcscmp(lpszClassName, _T("ComboBox")) == 0)
	{
		CComboBox* b = (CComboBox*)CWnd::FromHandle(hwnd);
		if(b && b->m_hWnd != NULL)
		{
			int iCount	= b->GetCount();
			int iSel	= b->GetCurSel();
			CIPString sTxt(_T(""));
			if(CB_ERR != iSel)
			{
				int n = b->GetLBTextLen(iSel);
				b->GetLBText(iSel, sTxt.GetBuffer(n));
				sTxt.ReleaseBuffer();
			}
			else
				sTxt = "<no selection>";
			
			sWndStyle.Format("elements:%d, selected:%d = \"",iCount,iSel);
			sWndStyle += sTxt+"\"";
		}
	}
	else
	{
		CIPString sCl(lpszClassName);
		sCl.MakeLower();
		if(sCl.Find("tabcontrol")>-1)
		{

		}
		if(sCl.Find("treeview")>-1)
		{
			CTreeView* c = (CTreeView*)CWnd::FromHandle(hwnd);
			if( c && c->m_hWnd != NULL && (c->GetTreeCtrl().m_hWnd != NULL))
				sWndStyle = "treerootitem:"+c->GetTreeCtrl().GetItemText(c->GetTreeCtrl().GetRootItem());
		}
		if((sCl.Find("internetexplorer")>-1) || (sCl.Find("internet explorer")>-1))
		{
			CHtmlView* v = (CHtmlView*)(CWnd::FromHandle(hwnd));
			if(v && (v->m_hWnd != NULL) && ::IsWindow(v->m_wndBrowser.m_hWnd) && (v->GetHtmlDocument() != NULL) && (v->GetContainer() != NULL) && (v->GetApplication() != NULL) && (v->GetParentBrowser() != NULL))
				sWndStyle = "URL:"+v->GetLocationURL();
		}
		if(sCl.Find("listview")>-1)
		{
			CListView* v = (CListView*)CWnd::FromHandle(hwnd);
			CListCtrl* plc = &(v->GetListCtrl());
			if(v && (v->m_hWnd != NULL) && (plc->m_hWnd != NULL) && ::IsWindow(plc->m_hWnd) && IsWindow(hwnd))
			{
				int iCount		= plc->GetItemCount();
				int iSels		= plc->GetSelectedCount();
				CHeaderCtrl* ph = plc->GetHeaderCtrl();
				if(ph && ::IsWindow(ph->m_hWnd) && IsWindow(hwnd))
				{
					int iHCount = ph->GetItemCount();
					CIPString sH(_T(""));
					BOOL bHasNotEmpty = FALSE;

					/*
					for (int i=0;i < iHCount;i++)
					{
						if(ph && ::IsWindow(ph->m_hWnd) && IsWindow(hwnd))
						{
							HDITEM hdi;
							TCHAR  lpBuffer[256];
							::ZeroMemory(lpBuffer, 255);
							hdi.mask		= HDI_TEXT;
							hdi.pszText		= lpBuffer;
							hdi.cchTextMax	= 256;

							if(ph->GetItem(i, &hdi) && IsWindow(hwnd))
							{
								sH+=_T((sH.IsEmpty() ? "\"" : "-\"") + CIPString(hdi.pszText)+"\"");

								CIPString sht(hdi.pszText);
								sht.AllTrim();
								if(!sht.IsEmpty())
									bHasNotEmpty = TRUE;
							}
						}
						else
							break;
					}
					*/
					sWndStyle.Format("itemcount:%d, selitems:%d%s",iCount,iSels, ((iHCount > 0) && bHasNotEmpty) ? ", headers:"+sH : "");
				}
			}
		}
		if(sCl.Find("richedit")>-1)
		{
			CRichEditCtrl* c = (CRichEditCtrl*)CWnd::FromHandle(hwnd);
			if(c && c->m_hWnd != NULL)
			{
				int iTxtLen = c->GetTextLength();
				int iLines  = c->GetLineCount();
				CIPString sTxt(_T(""));
				for(int i=0; i < iLines; i++)
				{
					c->GetLine(0, sTxt.GetBuffer(1024));
					sTxt.ReleaseBuffer(1024);
					sTxt.AllTrim();
					if(!sTxt.IsEmpty())
						break;
				}
				sWndStyle.Format("txtlen:%d, lines:%d",iTxtLen,iLines);
				if(!sTxt.IsEmpty())
					sWndStyle += _T("==>"+sTxt);
			}
		}
	}

	if(bWithhwnd)
		return shwnd+"(classname:"+CIPString(lpszClassName)+GetClassNameDesc(lpszClassName)+")" /*+ (CIPString(sWndStyle+s).IsEmpty() ? "" : "")*/ +sWndStyle+s;
	else
		return CIPString(lpszClassName)+GetClassNameDesc(lpszClassName) + sWndStyle + s;
}

void __FillSolidRect(HDC hDC, const RECT& rect, COLORREF clr)
{
	SetBkColor(hDC, clr);
	ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
}

void __FillSolidRect(HDC hDC, int x, int y, int cx, int cy, COLORREF clr)
{
	RECT rect={x, y, x + cx, y + cy };
	__FillSolidRect(hDC,rect,clr);
}

void __Draw3dRect(HDC hDC, int x, int y, int cx, int cy,COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	__FillSolidRect(hDC, x, y, cx - 1, 1, clrTopLeft);
	__FillSolidRect(hDC, x, y, 1, cy - 1, clrTopLeft);
	__FillSolidRect(hDC, x + cx, y, -1, cy, clrBottomRight);
	__FillSolidRect(hDC, x, y + cy, cx, -1, clrBottomRight);
}

void __Draw3dRect(HDC hDC, const RECT& rect,COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	__Draw3dRect(hDC, rect.left, rect.top,rect.right - rect.left,  rect.bottom - rect.top,clrTopLeft, clrBottomRight);
}

void __Draw3dBorder(HDC hDC, const RECT& rc, int nColor1, int nColor2,int nColor3, int nColor4)
{
	__Draw3dRect(hDC, rc, GetSysColor(nColor1), GetSysColor(nColor2));
	__Draw3dRect(hDC, rc.left + 1, rc.top + 1, rc.right - rc.left - 2, rc.bottom - rc.top - 2, GetSysColor(nColor3), GetSysColor(nColor4));
}

void __Draw3dBorder(HDC hDC, const RECT& rc, int nColor1, int nColor2,int nColor3, int nColor4,int nColor5, int nColor6)
{
	__Draw3dRect(hDC, rc, GetSysColor(nColor1), GetSysColor(nColor2));
	__Draw3dRect(hDC, rc.left + 1, rc.top + 1, rc.right - rc.left - 2, rc.bottom - rc.top - 2,GetSysColor(nColor3), GetSysColor(nColor4));
	__Draw3dRect(hDC, rc.left + 2, rc.top + 2, rc.right - rc.left - 4, rc.bottom - rc.top - 4,GetSysColor(nColor5), GetSysColor(nColor6));
}

void CDlgWindows::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 1;
	HTREEITEM h = m_oTree.GetSelectedItem();
	if(!h)
		return;

	HWND hw = (HWND)(m_oTree.GetItemData(h));
	if (!hw)
		return;
	CWnd* pw = CWnd::FromHandle(hw);
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
	::GetWindowRect(hw, &r);
	::SetCursorPos(r.left, r.top);

	if (fflashWindowEx)
	{
		//DWORD styleORG = GetWindowLong(hw,GWL_STYLE);
		CWnd* pwnd = CWnd::FromHandle(hw);

		{
			FLASHWINFO fi;
			fi.cbSize	= sizeof(fi);
			fi.hwnd		= hw;
			fi.dwFlags	= FLASHW_ALL;
			fi.uCount	= 2;
			fi.dwTimeout= 0;
			fflashWindowEx(&fi);
		}

		//HDC hDC = ::GetWindowDC(hw);
		RECT rect;
		::GetWindowRect(hw, &rect);
		//GetWindowRect(&rect);
		//this->ClientToScreen(&rect);
		//::ClientToScreen(hw, &rect);

		CDlgFlash _static;
		HRSRC _hrsrc	= ::FindResource(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDD_FLASHDLG), RT_DIALOG);
		HGLOBAL _hRes	= ::LoadResource(AfxGetApp()->m_hInstance, _hrsrc);
		_static.CreateIndirect(_hRes, AfxGetMainWnd());
		_static.MoveWindow(&rect, TRUE);
		_static.ShowWindow(SW_SHOW);

		//pwnd->SubclassWindow
		//COLORREF cf = GetBkColor(hDC);
		//COLORREF cf = GetTextColor(hDC);
		//DWORD dwbkORG = ::GetBkMode(hDC);

		for(int i=0; i < 9; i++)
		{
			//int nState = 2;
			//pwnd->ModifyStyleEx(1, WS_EX_TRANSPARENT|WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME|WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW);
			//::SetBkColor(hDC,GetSysColor(COLOR_3DHILIGHT));
			//__Draw3dBorder(hDC, rect, COLOR_3DDKSHADOW,COLOR_3DDKSHADOW,COLOR_3DHIGHLIGHT,COLOR_3DDKSHADOW,COLOR_3DLIGHT,COLOR_3DSHADOW);
			//__Draw3dBorder(hDC, rect, COLOR_3DHIGHLIGHT, COLOR_3DDKSHADOW,COLOR_3DLIGHT, COLOR_3DSHADOW,COLOR_3DFACE, COLOR_3DFACE);
			//__Draw3dBorder(hDC, rect, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,nState == 2 ? COLOR_3DHIGHLIGHT : COLOR_WINDOW, nState == 2 ? COLOR_3DHIGHLIGHT : COLOR_WINDOW);
			//::InflateRect(&rect, 4, 4);
			//::__IPVSleep(71);
			//::SetBkMode(hDC, OPAQUE);
			//SetBkColor(hDC,cf);
			//::SetTextColor(hDC, GetSysColor(COLOR_3DHILIGHT));
			//pwnd->Invalidate(TRUE);
			//pwnd->RedrawWindow();
			//::SendMessage(hw, WM_PAINT, 0, 0L);  // Repaint up-down too
			//nState = 1;
			//__Draw3dBorder(hDC, rect, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,nState == 2 ? COLOR_3DHIGHLIGHT : COLOR_WINDOW, nState == 2 ? COLOR_3DHIGHLIGHT : COLOR_WINDOW);
			//::InflateRect(&rect, -4, -4);
			//pwnd->ModifyStyleEx(1, WS_EX_TRANSPARENT|WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME|WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW);
			//::SendMessage(hw, WM_PAINT, 0, 0L);  // Repaint up-down too
			::__IPVSleep(71);
			_static.ShowWindow(SW_HIDE);
			::__IPVSleep(71);
			_static.ShowWindow(SW_SHOW);

			/*
			DWORD style = styleORG;
			style |= WS_BORDER;			//ADD FLAG
			style |= WS_DLGFRAME;
			style |= WS_THICKFRAME;
			::SetWindowLong(hw, GWL_STYLE, style);
			::__IPVSleep(71);
			style ^= WS_BORDER;			//REMOVE FLAG
			style ^= WS_DLGFRAME;
			style ^= WS_THICKFRAME;
			::SetWindowLong(hw, GWL_STYLE, style);
			::__IPVSleep(71);
			*/
		}
		//_static.CloseWindow();
		_static.DestroyWindow();
		//::SetBkColor(hDC,cf);
		//SetTextColor(hDC,cf);
		//::SetBkMode(hDC, dwbkORG);
		//::SetWindowLong(hw, GWL_STYLE, styleORG);
		//::ReleaseDC(WindowFromDC(hDC), hDC);

		{
			FLASHWINFO fi;
			fi.cbSize	= sizeof(fi);
			fi.hwnd		= hw;
			fi.dwFlags	= FLASHW_ALL;
			fi.uCount	= 2;
			fi.dwTimeout= 0;
			fflashWindowEx(&fi);
		}
	};

/*
	FLASHWINFO fwi; 
	fwi.cbSize = sizeof(FLASHWINFO); 
	fwi.hwnd = hw;
	fwi.dwFlags = FLASHW_ALL; 
	fwi.uCount = 25; 
	fwi.dwTimeout = 0; 
	FlashWindowEx(&fwi);

/*
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);

	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);
	::__IPVSleep(111);
	pw->FlashWindow(TRUE);

	CRect r;
	::GetWindowRect(hw, &r);
	::SetCursorPos(r.left, r.top);

	pw->FlashWindow(TRUE);
	::__IPVSleep(11);
	pw->FlashWindow(TRUE);
	::__IPVSleep(11);
	pw->FlashWindow(TRUE);
	::__IPVSleep(11);
	pw->FlashWindow(TRUE);
*/
}

void CDlgWindows::OnItemexpandingWinTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	if (pNMTreeView->action != TVE_EXPAND)
		return;

	HWND hwnd = (HWND)m_oTree.GetItemData(pNMTreeView->itemNew.hItem);
	HTREEITEM h = m_oTree.GetNextItem(pNMTreeView->itemNew.hItem, TVGN_CHILD);

	if(!h)
		return;

	CIPString sTxt(m_oTree.GetItemText(h));

	if(!sTxt.IsEmpty())
		return;

	m_oTree.DeleteItem(h);

	CWnd* pWnd		= CWnd::FromHandle(hwnd);
	CWnd* pwChild	= pWnd->GetWindow(GW_CHILD);
	long l			= m_oTree.m_ImageList.Add(__GetMyDir()+"\\w.bmp");

	CArray<HWND, HWND> ahs;
	ahs.Add(hwnd);

	while(pwChild)
	{
		if(!IsInArray(ahs, pwChild->m_hWnd, TRUE))
		{
			long l2	= m_oTree.m_ImageList.Add(__GetMyDir()+"\\"+GetWinIcon(pwChild->m_hWnd)+".bmp");
			if(l2 < 0)
				l2 = l;
			HTREEITEM hChild = m_oTree.InsertItem(GetWinTxt(pwChild->m_hWnd), l2, l2, pNMTreeView->itemNew.hItem, TVI_LAST);
			m_oTree.SetItemData(hChild, (DWORD)pwChild->m_hWnd);
			if(::GetWindow(pwChild->m_hWnd, GW_CHILD) != NULL)
				m_oTree.InsertItem("", l, l, hChild, TVI_LAST);
		}
		pwChild = pwChild->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CDlgWindows::IsInArray(CArray<HWND, HWND> &ahs, HWND h, BOOL bAdd)
{
	for(int i=0; i < ahs.GetSize(); i++)
	{
		if(ahs.GetAt(i) == h)
			return TRUE;
	}
	if(!bAdd)
		return FALSE;

	ahs.Add(h);
	return FALSE;
}

CIPString CDlgWindows::GetWinIcon(HWND h)
{
	TCHAR lpszClassName[255];
	GetClassName(h, lpszClassName, 255);
	if(_tcscmp(lpszClassName, _T("Button")) == 0)
	{
		CButton* b = (CButton*)CWnd::FromHandle(h);
		if(b && b->m_hWnd)
		{
			UINT uStyle = b->GetButtonStyle();
			if (uStyle & BS_PUSHBUTTON)
			   return "button";
			else
			{
				if (uStyle & BS_RADIOBUTTON)
				   return "radiobutton";
				else if (uStyle & BS_CHECKBOX)
				   return "checkbox";
				else if (uStyle & BS_3STATE)
				   return "radiobutton";
			}
		}

		return "button";
	}
	else if(_tcscmp(lpszClassName, _T("ScrollBar")) == 0)
	{
		return "scrollbar";
	}
	else if(_tcscmp(lpszClassName, _T("Static")) == 0)
	{
		return "static";
	}
	else if(_tcscmp(lpszClassName, _T("Edit")) == 0)
	{
		return "edit";
	}
	else if(_tcscmp(lpszClassName, _T("ComboBox")) == 0)
	{
		return "combobox";
	}
	CIPString sCl(lpszClassName);
	sCl.MakeLower();
	if(sCl.Find("tabcontrol")>-1)
		return "tabcontrol";
	if(sCl.Find("treeview")>-1)
		return "treeview";
	if(sCl.Find("internetexplorer")>-1)
		return "ie";
	if(sCl.Find("internet explorer")>-1)
		return "ie";
	if(sCl.Find("listview")>-1)
		return "listview";
	if(sCl.Find("richedit")>-1)
		return "richedit";

	return "w";
}

CIPString CDlgWindows::GetClassNameDesc(CIPString sClassName)
{
/*
ComboLBox -  Drop down listbox of a ComboBox
#32768    -  Menu Class
#32769    -  Desktop Window class
#32770    -  Dialog Class
#32771    -  Task Switch Window class (Windows 2000 or greater)
#32772    -  Class for Icon Titles
DDEMLEvent - Class for DDEML events
Message   -  class for message only window
*/
	sClassName.MakeLower();
	sClassName.AllTrim();
	if(sClassName.CompareNoCase("#32770")==0)		return " (Dialog)";
	if(sClassName.CompareNoCase("ComboLBox")==0)	return " (Drop down listbox of a ComboBox)";
	if(sClassName.CompareNoCase("#32768")==0)		return " (Menu)";
	if(sClassName.CompareNoCase("#32769")==0)		return " (Desktop Window)";
	if(sClassName.CompareNoCase("#32770")==0)		return " (Dialog)";
	if(sClassName.CompareNoCase("#32771")==0)		return " (Task Switch Window)";
	if(sClassName.CompareNoCase("#32772")==0)		return " (Icon Titles)";
	if(sClassName.CompareNoCase("DDEMLEvent")==0)	return " (DDEML events)";
	if(sClassName.CompareNoCase("Message")==0)		return " (message only window)";

	//::__Log("DlgWindows:GetClassNameDesc\tINF:unknown.class:"+sClassName);
	return _T("");
}
