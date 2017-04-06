// sender.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "sender.h"
#include "senderDlg.h"

#include "msoutl9.h" // for Outlook 2000 use msoutl9.h
                     // for Outlook 2002 & Outlook 2003 use msoutl.h

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CsenderApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// Ole-initialization class.
class OleInitClass
{
public:
  OleInitClass()
  {
     OleInitialize(NULL);
  }
  ~OleInitClass()
  {
     OleUninitialize();
  }
};

// This global class calls OleInitialize() at
// application startup, and calls OleUninitialize()
// at application exit...
OleInitClass g_OleInitClass;

CsenderApp::CsenderApp()
{

}

CsenderApp theApp;

BOOL CsenderApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	_send();
	return FALSE;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CsenderDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL _send()
{
	// Start Outlook.
	// If it is already running, you'll use the same instance...
	_Application olApp;
	COleException e;
	if(!olApp.CreateDispatch("Outlook.Application", &e))
	{
		//0x80080005 = CO_E_SERVER_EXEC_FAILURE
		#ifdef _DEBUG
		CString str;
		str.Format("CreateDispatch() failed w/error 0x%08lx", e.m_sc);
		AfxMessageBox(str, MB_SETFOREGROUND);
		#endif
		return FALSE;
	}

#ifdef USE_NEW_OUTLOOK
	Namespace olNS(olApp.GetNames("MAPI"));
#else	
	_NameSpace olNs(olApp.GetNamespace("MAPI"));
#endif

	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	olNs.Logon(covOptional, covOptional, covOptional, covOptional);
   
	// Prepare a new mail message
	_MailItem olMail(olApp.CreateItem(0));
	olMail.SetTo("bla@blu.de");
	olMail.SetSubject("subject");
#ifdef SEND_TEXT_EMAIL
	olMail.SetBody("body");
#else
	olMail.SetHTMLBody("<p><b>html</b> body</p>");
#endif
	olMail.SetSubject("c++ example mail");

	{
		VARIANT _v;
		VariantInit(&_v);
		_v.vt = VT_BOOL;
		_v.boolVal = FALSE;
		olMail.Display(_v);
	}

	//olMail.Send();	// Send the message!

#ifdef _DEBUG
	AfxMessageBox("All done.", MB_SETFOREGROUND);
#endif

	olNs.Logoff();
	return TRUE;
}
