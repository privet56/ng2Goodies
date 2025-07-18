// BrowserDoc.h : interface of the CBrowserDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROWSERDOC_H__41B33A5D_710C_11D3_BB8B_00C04FA3471C__INCLUDED_)
#define AFX_BROWSERDOC_H__41B33A5D_710C_11D3_BB8B_00C04FA3471C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBrowserDoc : public CDocument
{
protected: // create from serialization only
	CBrowserDoc();
	DECLARE_DYNCREATE(CBrowserDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBrowserDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBrowserDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERDOC_H__41B33A5D_710C_11D3_BB8B_00C04FA3471C__INCLUDED_)
