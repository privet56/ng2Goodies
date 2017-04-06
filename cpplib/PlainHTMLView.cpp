// PlainHTMLView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "PlainHTMLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlainHTMLView

IMPLEMENT_DYNCREATE(CPlainHTMLView, CHtmlView)

CPlainHTMLView::CPlainHTMLView()
{
	//{{AFX_DATA_INIT(CPlainHTMLView)
		// HINWEIS: Der Klassen-Assistent fügt hier die Elementinitialisierung hinzu
	//}}AFX_DATA_INIT
}

CPlainHTMLView::~CPlainHTMLView()
{
}

void CPlainHTMLView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlainHTMLView)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe hinzu
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlainHTMLView, CHtmlView)
	//{{AFX_MSG_MAP(CPlainHTMLView)
		// HINWEIS - Hier werden Umsetzungsmakros vom Klassen-Assistenten hinzugefügt und entfernt.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlainHTMLView Diagnose

#ifdef _DEBUG
void CPlainHTMLView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CPlainHTMLView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlainHTMLView Nachrichten-Behandlungsroutinen

void CPlainHTMLView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

