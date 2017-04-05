
// sender.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include <windows.h>
#include "resource.h"		// main symbols


// CsenderApp:
// See sender.cpp for the implementation of this class
//

class CsenderApp : public CWinAppEx
{
public:
	CsenderApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CsenderApp theApp;

BOOL _send();
