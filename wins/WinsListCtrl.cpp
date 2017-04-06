// WinsListCtrl.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "WinsListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinsListCtrl

CWinsListCtrl::CWinsListCtrl()
{
	m_ImageList.Create(IDB_IMGLIST, 16, 2, RGB(200, 201, 202));
}

CWinsListCtrl::~CWinsListCtrl()
{
}


BEGIN_MESSAGE_MAP(CWinsListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CWinsListCtrl)
		ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CWinsListCtrl 

void CWinsListCtrl::Setup()
{
	ListView_SetExtendedListViewStyle(m_hWnd, LVS_EX_FULLROWSELECT);

	//calc. the column widths
	RECT _rct;

	GetClientRect(&_rct);
	_rct.right -= ::GetSystemMetrics(SM_CXVSCROLL);
	InsertColumn(0, _T("Title"),			LVCFMT_LEFT,(int)((_rct.right / 5)*1.7) , -1);
	InsertColumn(1, _T("hwnd/pid"),			LVCFMT_LEFT,(int)((_rct.right / 5)*1.8) ,  1);
	InsertColumn(2, _T("Module Filename"),	LVCFMT_LEFT,	 ((_rct.right / 5)*3)	,  2);
	InsertColumn(3, _T("Enabled"),			LVCFMT_CENTER,	 ((_rct.right / 5)/2)	,  2);
	InsertColumn(4, _T("DlgBased"),			LVCFMT_CENTER,	 ((_rct.right / 5)/2)	,  2);
	/*
	InsertColumn(0, _T("Title"),			LVCFMT_LEFT,	(_rct.right / 5)*2	, -1);
	InsertColumn(1, _T("#"),				LVCFMT_CENTER,	(_rct.right / 5)/2	,  1);
	InsertColumn(2, _T("Module Filename"),	LVCFMT_LEFT,	(_rct.right / 5)*2	,  2);
	InsertColumn(3, _T("Enabled"),			LVCFMT_CENTER,	(_rct.right / 5)	,  2);
	InsertColumn(4, _T("dlg based app"),	LVCFMT_CENTER,	(_rct.right / 5)	,  2);
	*/
}

void CWinsListCtrl::AddItem(WINDATA *_pWindata)
{	
	SetImageList(&m_ImageList, LVSIL_SMALL);

	LVITEM _i;

	_i.mask = LVIF_TEXT | LVIF_IMAGE;
	_i.pszText = (LPTSTR)(LPCTSTR)_pWindata->m_sTitle;
	_i.iItem = GetItemCount();
	_i.iSubItem = 0;
	if((_pWindata->m_HWND != NULL) && ::IsWindowVisible(_pWindata->m_HWND))
		_i.iImage = 0;
	else
		_i.iImage = 1;

	int _iInsterted = InsertItem(&_i);

	CString _sCount = _T("");
	_sCount.Format(_T("hwnd:%.d procid:%d"), _pWindata->m_HWND, _pWindata->m_dwProcessID);
	SetItemText(_iInsterted, 1, (LPTSTR)(LPCTSTR)_sCount);
	SetItemText(_iInsterted, 2, (LPTSTR)(LPCTSTR)_pWindata->m_sModFN);

	SetItemText(_iInsterted, 3, _pWindata->m_bEnabled  ? (LPTSTR)(LPCTSTR)_T("yes") : (LPTSTR)(LPCTSTR)_T("no"));
	SetItemText(_iInsterted, 4, _pWindata->m_bDlgBased ? (LPTSTR)(LPCTSTR)_T("yes") : (LPTSTR)(LPCTSTR)_T("no"));

	WINDATA* _pwind = new WINDATA;
	*(_pwind) = *(_pWindata);
	_pwind->iItem = _i.iItem;

	SetItemData(_iInsterted, (DWORD)_pwind);
}

void CWinsListCtrl::SetItem(long _lItem)
{
//1.: select
	LVITEM _i;
	CSize _sz;
	RECT _rct;

	_i.mask = LVIF_STATE;
	_i.iItem = _lItem;
	_i.iSubItem = 0;
	_i.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
	_i.state = LVIS_SELECTED | LVIS_FOCUSED;
	SetItemState(_lItem, &_i);

	//scroll to the selected item when needed
	if (!EnsureVisible(_lItem, FALSE))
	{
		GetItemRect(0, &_rct, LVIR_BOUNDS);
		_sz.cx = 0;
		_sz.cy = (_rct.top - _rct.bottom) * (_lItem - GetTopIndex() - GetCountPerPage());
		Scroll(_sz);
	}
//2.: set
	WINDATA* _pwindata = (WINDATA*)GetItemData(_lItem);
	//code

	CWnd* _pwnd = NULL;
	_pwnd = CWnd::FromHandle(_pwindata->m_HWND);
	_pwnd->GetWindowText(_pwindata->m_sTitle);

	_i.mask = LVIF_TEXT | LVIF_IMAGE;
	_i.pszText = (LPTSTR)(LPCTSTR)_pwindata->m_sTitle;
	_i.iItem = GetSelectedItem();
	_i.iSubItem = 0;

	if(::IsWindowVisible(_pwindata->m_HWND))
		_i.iImage = 0;
	else
		_i.iImage = 1;

	CString _sCount = _T("");
	_sCount.Format(_T("hwnd:%.d procid:%d"), _pwindata->m_HWND, _pwindata->m_dwProcessID);
	SetItemText(_i.iItem, 1, (LPTSTR)(LPCTSTR)_sCount);
	SetItemText(_i.iItem, 2, (LPTSTR)(LPCTSTR)_pwindata->m_sModFN);

	SetItemText(_i.iItem, 3, _pwindata->m_bEnabled  ? (LPTSTR)(LPCTSTR)_T("yes") : (LPTSTR)(LPCTSTR)_T("no"));
	SetItemText(_i.iItem, 4, _pwindata->m_bDlgBased ? (LPTSTR)(LPCTSTR)_T("yes") : (LPTSTR)(LPCTSTR)_T("no"));

	_pwindata->iItem = _i.iItem;

	CListCtrl::SetItem(&_i);
}

long CWinsListCtrl::GetSelectedItem()
{
	//data
	POSITION pos = GetFirstSelectedItemPosition();
	//code
	if (pos == NULL)
		return -1;
	else
		return GetNextSelectedItem(pos);

	return -1;
}

void CWinsListCtrl::SetSelectedItem(long i)
{
	//data
	LVITEM _i;
	CSize _sz;
	RECT _rct;
	//code
	_i.mask = LVIF_STATE;
	_i.iItem = i;
	_i.iSubItem = 0;
	_i.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
	_i.state = LVIS_SELECTED | LVIS_FOCUSED;
	SetItemState(i, &_i);

	//scroll to the selected item when needed
	if (!EnsureVisible(i, FALSE))
	{
		GetItemRect(0, &_rct, LVIR_BOUNDS);
		_sz.cx = 0;
		_sz.cy = (_rct.top - _rct.bottom) * (i - GetTopIndex() - GetCountPerPage());
		Scroll(_sz);
	}

	GetParent()->PostMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), LBN_SELCHANGE), (LPARAM)m_hWnd);
}

void CWinsListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if((pNMHDR == NULL) && (pResult == NULL))
	{
		m_ListSort.list				= this;
		m_ListSort.bUp				= FALSE;
		this->m_ListSort.iSubItem	= 0;
		this->SortItems(this->OnCompareTwoItems, (LPARAM)(&(this->m_ListSort)));
		return;
	}
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	m_ListSort.list = this;
	if(pNMListView->iSubItem == this->m_ListSort.iSubItem)
		m_ListSort.bUp = !m_ListSort.bUp;
	else
		m_ListSort.bUp = FALSE;

	this->m_ListSort.iSubItem = pNMListView->iSubItem;
	this->SortItems(this->OnCompareTwoItems, (LPARAM)(&(this->m_ListSort)));
	
	*pResult = 0;
}

int CALLBACK CWinsListCtrl::OnCompareTwoItems(LPARAM lItem1, LPARAM lItem2, LPARAM lParam)
{
/*
	{
		tagLISTSORT* pListSort = (tagLISTSORT*)lParam;
		CString    strItem1 = pListSort->list->GetItemText(((WINDATA*) lItem1)->iItem, pListSort->iSubItem);
		CString    strItem2 = pListSort->list->GetItemText(((WINDATA*) lItem2)->iItem, pListSort->iSubItem);
		{
			//CIPString s;
			//s.Format("s1:%s\ts2:%s\niItem1:%d\tiItem2:%d\npListSort->iSubItem:%d",strItem1, strItem2,((WINDATA*) lItem1)->iItem,((WINDATA*) lItem2)->iItem, pListSort->iSubItem);
			//AfxMessageBox(s);
		}
		if(!pListSort->bUp)
			return strcmp(strItem1, strItem2) > 0;
		else
			return strcmp(strItem2, strItem1) > 0;
	}
*/

	tagLISTSORT* pListSort = (tagLISTSORT*)lParam;
	int nSpalte = (int) pListSort->iSubItem;

	WINDATA* pItem1 = (WINDATA*) lItem1;
	WINDATA* pItem2 = (WINDATA*) lItem2;

	if((pItem1 == NULL) || (pItem2 == NULL))	return 0;

	//CIPString strItem1;
	//CIPString strItem2;

	/*
	InsertColumn(0, _T("Title"),			LVCFMT_LEFT,(int)((_rct.right / 5)*1.7) , -1);
	InsertColumn(1, _T("hwnd/pid"),			LVCFMT_LEFT,(int)((_rct.right / 5)*1.8) ,  1);
	InsertColumn(2, _T("Module Filename"),	LVCFMT_LEFT,	 ((_rct.right / 5)*3)	,  2);
	InsertColumn(3, _T("Enabled"),			LVCFMT_CENTER,	 ((_rct.right / 5)/2)	,  2);
	InsertColumn(4, _T("DlgBased"),			LVCFMT_CENTER,	 ((_rct.right / 5)/2)	,  2);

	//0 		_i.pszText = (LPTSTR)(LPCTSTR)_pWindata->m_sTitle;
	//1 		CString _sCount = _T("");
				_sCount.Format(_T("hwnd:%.d procid:%d"), _pWindata->m_HWND, _pWindata->m_dwProcessID);
				SetItemText(_iInsterted, 1, (LPTSTR)(LPCTSTR)_sCount);
	//2 		SetItemText(_iInsterted, 2, (LPTSTR)(LPCTSTR)_pWindata->m_sModFN);
	//3 		SetItemText(_iInsterted, 3, _pWindata->m_bEnabled  ? (LPTSTR)(LPCTSTR)_T("yes") : (LPTSTR)(LPCTSTR)_T("no"));
	//4 		SetItemText(_iInsterted, 4, _pWindata->m_bDlgBased ? (LPTSTR)(LPCTSTR)_T("yes") : (LPTSTR)(LPCTSTR)_T("no"));
	*/

	switch(nSpalte)
	{
		case(0):
		{
			if(!pListSort->bUp)
			{
				if(pItem1->m_sTitle.IsEmpty())
					return 1;
				if(pItem2->m_sTitle.IsEmpty())
					return -1;
				return (pItem1->m_sTitle.CompareNoCase(pItem2->m_sTitle)>0);
			}
			else
				return (pItem1->m_sTitle.CompareNoCase(pItem2->m_sTitle)<0);
		}
		case(1):
		{
			CString _sCount1(_T(""));
			_sCount1.Format(_T("hwnd:%.d procid:%d"), pItem1->m_HWND, pItem1->m_dwProcessID);
	 		CString _sCount2(_T(""));
			_sCount2.Format(_T("hwnd:%.d procid:%d"), pItem2->m_HWND, pItem2->m_dwProcessID);
			if(!pListSort->bUp)
				return (_sCount1.CompareNoCase(_sCount2)>0);
			else
				return (_sCount1.CompareNoCase(_sCount2)<0);
		}
		case(2):
		{
			if(!pListSort->bUp)
				return (pItem1->m_sModFN.CompareNoCase(pItem2->m_sModFN)>0);
			else
				return (pItem1->m_sModFN.CompareNoCase(pItem2->m_sModFN)<0);
		}
		case(3):
		{
			if(!pListSort->bUp)
				return (pItem1->m_bEnabled > pItem2->m_bEnabled);
			else
				return (pItem1->m_bEnabled < pItem2->m_bEnabled);
		}
		case(4):
		{
			if(!pListSort->bUp)
				return (pItem1->m_bDlgBased > pItem2->m_bDlgBased);
			else
				return (pItem1->m_bDlgBased < pItem2->m_bDlgBased);
		}
		default:
		{
			if(!pListSort->bUp)
				return (pItem1->m_sTitle.CompareNoCase(pItem2->m_sTitle)>0);
			else
				return (pItem1->m_sTitle.CompareNoCase(pItem2->m_sTitle)<0);
		}
	}
}
