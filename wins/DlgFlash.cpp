// DlgFlash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "DlgFlash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFlash 


CDlgFlash::CDlgFlash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFlash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFlash)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgFlash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFlash)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFlash, CDialog)
	//{{AFX_MSG_MAP(CDlgFlash)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFlash 

BOOL CDlgFlash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return FALSE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgFlash::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	return;

	if(!bShow)
	{
		return;
	}
	this->ShowWindow(SW_HIDE);

	CRect rct;
	this->GetWindowRect(&rct);
	this->ScreenToClient(&rct);

	if (rct.top < 0)
		rct.top = 0;
	if (rct.left < 0)
		rct.left = 0;

	int iWdth = rct.right - rct.left;
	int iHght = rct.bottom - rct.top;

	CWnd* pbTop = GetDlgItem(IDC_TOP_B);
	CWnd* pbBtt = GetDlgItem(IDC_BOTTOM_B);
	CWnd* pbLft = GetDlgItem(IDC_LEFT_B);
	CWnd* pbRgt = GetDlgItem(IDC_RIGHT_B);

	pbTop->MoveWindow(0,0,iWdth,5, TRUE);
	pbLft->MoveWindow(0,0,5,iHght,TRUE);

	pbBtt->MoveWindow(0,rct.bottom-rct.top-7,rct.right-rct.left,5,TRUE);


	pbRgt->MoveWindow(rct.right-7,0,5,rct.bottom,TRUE);


	/*
	HDC hdc = ::GetDC(this->m_hWnd);
	MoveToEx(hdc, 0, 0, NULL); 
	LineTo(hdc, rct.right,0); 
	ReleaseDC(this->m_hWnd, hdc); 
	*/
}

void CDlgFlash::DoShow(BOOL bShow, CWnd* p)
{
	this->ShowWindow(SW_HIDE);

	CRect rct;
	this->GetWindowRect(&rct);
	this->ScreenToClient(&rct);

	if (rct.top < 0)
		rct.top = 0;
	if (rct.left < 0)
		rct.left = 0;

	int iWdth = rct.right - rct.left;
	int iHght = rct.bottom - rct.top;

	CWnd* pbTop = GetDlgItem(IDC_TOP_B);
	CWnd* pbBtt = GetDlgItem(IDC_BOTTOM_B);
	CWnd* pbLft = GetDlgItem(IDC_LEFT_B);
	CWnd* pbRgt = GetDlgItem(IDC_RIGHT_B);

	pbTop->MoveWindow(0,0,iWdth,5, TRUE);
	pbLft->MoveWindow(0,0,5,iHght,TRUE);
	pbBtt->MoveWindow(0,rct.bottom-rct.top-7,rct.right-rct.left,5,TRUE);
	pbRgt->MoveWindow(rct.right-7,0,5,rct.bottom,TRUE);

	pbTop->SetParent(p);
	pbBtt->SetParent(p);
	pbLft->SetParent(p);
	pbRgt->SetParent(p);

	pbTop->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	pbBtt->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	pbLft->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	pbRgt->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}
