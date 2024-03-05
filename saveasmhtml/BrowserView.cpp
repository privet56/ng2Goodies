// BrowserView.cpp : implementation of the CBrowserView class
//

#include "stdafx.h"
#include "Browser.h"

#include "BrowserDoc.h"
#include "BrowserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserView

IMPLEMENT_DYNCREATE(CBrowserView, CHtmlView)

BEGIN_MESSAGE_MAP(CBrowserView, CHtmlView)
	//{{AFX_MSG_MAP(CBrowserView)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSave)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserView construction/destruction

CBrowserView::CBrowserView()
{
	// TODO: add construction code here

}

CBrowserView::~CBrowserView()
{
}

BOOL CBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView drawing

void CBrowserView::OnDraw(CDC* pDC)
{
	CBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CBrowserView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	
	
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("http://www.yahoo.com"),NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView printing


/////////////////////////////////////////////////////////////////////////////
// CBrowserView diagnostics

#ifdef _DEBUG
void CBrowserView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBrowserView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CBrowserDoc* CBrowserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrowserDoc)));
	return (CBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserView message handlers


void CBrowserView::OnFileSave() 
{
	m_wbSaveAs.SetWebBrowser(m_pBrowserApp);
	m_wbSaveAs.Config( CString("c:\\htmlpage"), SAVETYPE_ARCHIVE );
	m_wbSaveAs.SaveAs();
}

