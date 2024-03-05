// BrowserDoc.cpp : implementation of the CBrowserDoc class
//

#include "stdafx.h"
#include "Browser.h"

#include "BrowserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc

IMPLEMENT_DYNCREATE(CBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CBrowserDoc, CDocument)
	//{{AFX_MSG_MAP(CBrowserDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBrowserDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CBrowserDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IBrowser to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {41B33A53-710C-11D3-BB8B-00C04FA3471C}
static const IID IID_IBrowser =
{ 0x41b33a53, 0x710c, 0x11d3, { 0xbb, 0x8b, 0x0, 0xc0, 0x4f, 0xa3, 0x47, 0x1c } };

BEGIN_INTERFACE_MAP(CBrowserDoc, CDocument)
	INTERFACE_PART(CBrowserDoc, IID_IBrowser, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc construction/destruction

CBrowserDoc::CBrowserDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CBrowserDoc::~CBrowserDoc()
{
	AfxOleUnlockApp();
}

BOOL CBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc serialization

void CBrowserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc diagnostics

#ifdef _DEBUG
void CBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserDoc commands
