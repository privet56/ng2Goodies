// Browser.h : main header file for the BROWSER application
//

#if !defined(AFX_BROWSER_H__41B33A56_710C_11D3_BB8B_00C04FA3471C__INCLUDED_)
#define AFX_BROWSER_H__41B33A56_710C_11D3_BB8B_00C04FA3471C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBrowserApp:
// See Browser.cpp for the implementation of this class
//

class CBrowserApp : public CWinApp
{
public:
	CBrowserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CBrowserApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSER_H__41B33A56_710C_11D3_BB8B_00C04FA3471C__INCLUDED_)
