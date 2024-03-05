// BrowserView.h : interface of the CBrowserView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROWSERVIEW_H__41B33A5F_710C_11D3_BB8B_00C04FA3471C__INCLUDED_)
#define AFX_BROWSERVIEW_H__41B33A5F_710C_11D3_BB8B_00C04FA3471C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SaveAsWebbrowser.h"

class CBrowserView : public CHtmlView
{
protected: // create from serialization only
	CBrowserView();
	DECLARE_DYNCREATE(CBrowserView)

// Attributes
public:
	CBrowserDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CSaveAsWebbrowser m_wbSaveAs;

// Generated message map functions
protected:
	//{{AFX_MSG(CBrowserView)
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BrowserView.cpp
inline CBrowserDoc* CBrowserView::GetDocument()
   { return (CBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERVIEW_H__41B33A5F_710C_11D3_BB8B_00C04FA3471C__INCLUDED_)
