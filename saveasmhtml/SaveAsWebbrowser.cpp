//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
// This is unsupported code and Microsoft makes no guarantee that the
// techniques used in this sample will function properly in future
// versions of the Internet Explorer product.  This sample takes advantage
// of the fact that the resource identifiers in the "Page Setup" and
// "Print" dialogs are consistent between IE4 and IE5.  Therefore, it is
// possible that this technique will not work properly in future versions
// of Internet Explorer due to changes in the user interface or other
// modifications made to the product at a later date.  The product is not
// designed or tested to accommodate this technique, and the fact that it
// works is fortuitous but not by design.  Please use caution when adding
// this functionality to an application, and bear in mind this warning
// when testing your application with future versions of Internet Explorer.
//
// Author: Dave Templin
//         Support Engineer - Internet Client SDK
//         Microsoft Developer Support
//--------------------------------------------------------------------------
// 
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SaveAsWebbrowser.h"
#include "SaveAsThread.h"

static HHOOK g_hHook = NULL;
static HWND g_hWnd = NULL;
static bool g_bSuccess = false;
static CSaveAsWebbrowser* g_pWebBrowserSaveAs = NULL;



CSaveAsWebbrowser::CSaveAsWebbrowser() : m_pWebBrowser(NULL)
{
	SaveAsDisable();
	m_bUpdateUI = TRUE;
}

CSaveAsWebbrowser::~CSaveAsWebbrowser()
{
	if (m_pWebBrowser)
		m_pWebBrowser->Release();
	m_pWebBrowser = NULL;
}

void CSaveAsWebbrowser::SetWebBrowser(IWebBrowser2* pWebBrowser)
{
	if (m_pWebBrowser)
	{
		m_pWebBrowser->Release();
		m_pWebBrowser = NULL;
	}

	if (pWebBrowser)
	{
		m_pWebBrowser = pWebBrowser;
		m_pWebBrowser->AddRef();
		m_bUpdateUI = TRUE;
	}
}

void CSaveAsWebbrowser::Config(CString &szFilename, SaveType type)
{
	m_szFilename = szFilename;
	m_nSaveType = type;
}

CString CSaveAsWebbrowser::GetFilename()
{ 
	return m_szFilename; 
}
SaveType CSaveAsWebbrowser::GetSaveAsType() 
{ 
	return m_nSaveType; 
}

BOOL CSaveAsWebbrowser::IsSaveAsEnabled()
{
	return m_bSaveAsEnabled;
}
void CSaveAsWebbrowser::SaveAsDisable()
{
	m_bSaveAsEnabled = FALSE;
}


BOOL CSaveAsWebbrowser::SaveAs()
{
	if (m_szFilename.IsEmpty())
		m_szFilename = "untitled";

	m_bSaveAsEnabled = TRUE;

	return InvokeDlg( OLECMDID_SAVEAS );
}


bool CSaveAsWebbrowser::InvokeDlg(OLECMDID cmdid)
{
	if (!m_pWebBrowser)
		return false;
	if (g_hHook)
		return false;


	// prepare SaveAs Dialog hook
	//
	g_hHook = SetWindowsHookEx(WH_CBT, CbtProc, NULL, GetCurrentThreadId());
	if (!g_hHook)
		return false;

	// make SaveAs Dialog appear
	//
	g_bSuccess = false;
	g_pWebBrowserSaveAs = this;
	HRESULT hr = m_pWebBrowser->ExecWB(cmdid, OLECMDEXECOPT_PROMPTUSER, NULL, NULL);


	// remove hook
	UnhookWindowsHookEx(g_hHook);
	g_pWebBrowserSaveAs = NULL;
	g_hHook = NULL;

	return g_bSuccess;
}


LRESULT CALLBACK CSaveAsWebbrowser::CbtProc(int nCode, WPARAM wParam, LPARAM lParam) 
{  
	switch (nCode)
	{
		case HCBT_CREATEWND:
		{
			HWND hWnd = (HWND)wParam;
			LPCBT_CREATEWND pcbt = (LPCBT_CREATEWND)lParam;
			LPCREATESTRUCT pcs = pcbt->lpcs;
			if ((DWORD)pcs->lpszClass == 0x00008002)
			{
				g_hWnd = hWnd;          // Get hwnd of SaveAs dialog
				pcs->x = -2 * pcs->cx;  // Move dialog off screen
			}
			break;
		}	
		case HCBT_ACTIVATE:
		{
			HWND hwnd = (HWND)wParam;
			if (hwnd == g_hWnd)
			{
				g_hWnd = NULL;
				g_bSuccess = true;

				if (g_pWebBrowserSaveAs->IsSaveAsEnabled())
				{
					g_pWebBrowserSaveAs->SaveAsDisable();

					CSaveAsThread *newthread = new CSaveAsThread();
					newthread->SetKeyWnd(hwnd);
					newthread->Config( g_pWebBrowserSaveAs->GetFilename(), g_pWebBrowserSaveAs->GetSaveAsType() );
					newthread->StartThread();
				}
			}
			break;
		}
	}
    return CallNextHookEx(g_hHook, nCode, wParam, lParam); 
} 


void CSaveAsWebbrowser::UpdateSaveAs(HWND hwnd)
{
	// editbox : filepath (control id = 0x047c)
	// dropdown combo : filetypes (options=complete page;archive;html only;txt) (control id = 0x0470)
	// save button : control id = 0x0001
	// cancel button : control id = 0x0002


	// select right item in the combobox
	SendMessage(GetDlgItem(hwnd, 0x0470), CB_SETCURSEL, (WPARAM) m_nSaveType, 0);
	SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(0x0470,CBN_CLOSEUP), (LPARAM) GetDlgItem(hwnd, 0x0470));

	// set output filename
	SendMessage(GetDlgItem(hwnd, 0x047c), WM_SETTEXT, (WPARAM) 0, (LPARAM)(LPCTSTR)m_szFilename);

	if (m_bUpdateUI)
		SendMessage(GetDlgItem(hwnd, 0x0001), BM_CLICK, 0, 0);  // Invoke Save button
	else
		SendMessage(GetDlgItem(hwnd, 0x0002), BM_CLICK, 0, 0);  // Invoke Cancel button
}





