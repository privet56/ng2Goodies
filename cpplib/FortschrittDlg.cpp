// FortschrittDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "FortschrittDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFortschrittDlg 


CFortschrittDlg::CFortschrittDlg(CWnd* pParent)
	: CDialog(CFortschrittDlg::IDD/*, pParent*/) //it doesn't matter what parent is wanted, it must be allways
													//the main window
{
	CommonConstruct();
}

void CFortschrittDlg::CommonConstruct()
{
	m_hWndParent = NULL;
	m_bEnableParent = FALSE;
	m_hModalDialogTemplate = NULL;
}

void CFortschrittDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFortschrittDlg)
	DDX_Control(pDX, IDC_FORTSCHRITT_PB, m_ctlProgressCtrl);
	DDX_Control(pDX, IDC_FORTSCHRITT_ST, m_ctlStaticCtrl);
	DDX_Text(pDX, IDC_FORTSCHRITT_ST, m_strFortschritt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFortschrittDlg, CDialog)
	//{{AFX_MSG_MAP(CFortschrittDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFortschrittDlg 

int CFortschrittDlg::DoModal()
{
	// can be constructed with a resource template or InitModalIndirect
	ASSERT(m_lpszTemplateName != NULL || m_hDialogTemplate != NULL ||
		m_lpDialogTemplate != NULL);

	// load resource as necessary
	LPCDLGTEMPLATE lpDialogTemplate = m_lpDialogTemplate;
	m_hModalDialogTemplate = m_hDialogTemplate;
	HINSTANCE hInst = AfxGetResourceHandle();
	if (m_lpszTemplateName != NULL)
	{
		hInst = AfxFindResourceHandle(m_lpszTemplateName, RT_DIALOG);
		HRSRC hResource = ::FindResource(hInst, m_lpszTemplateName, RT_DIALOG);
		m_hModalDialogTemplate = LoadResource(hInst, hResource);
	}
	if (m_hModalDialogTemplate != NULL)
	{
		lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(m_hModalDialogTemplate);
	}

	if (lpDialogTemplate == NULL)
	{
		m_nModalResult = -1;
		return FALSE;
	}

	// disable parent (before creating dialog)
	m_hWndParent = PreModal();
	AfxUnhookWindowCreate();
	m_bEnableParent = FALSE;
	if (m_hWndParent != NULL && ::IsWindowEnabled(m_hWndParent))
	{
		::EnableWindow(m_hWndParent, FALSE);
		m_bEnableParent = TRUE;
	}

	TRY
	{
		// create modeless dialog
		AfxHookWindowCreate(this);
		if (CreateDlgIndirect(lpDialogTemplate, CWnd::FromHandle(m_hWndParent), hInst))
		{
			if (m_nFlags & WF_CONTINUEMODAL)
			{
				m_nFlags |= WF_MODALLOOP;
				ShowWindow(SW_SHOWNORMAL);
				UpdateWindow();
				Pulse();
			}
		}
	}
	CATCH_ALL(e)
	{
		CloseDialog();
		e->Delete();
		m_nModalResult = -1;
	}
	END_CATCH_ALL;

	SetTimer(10, 100, NULL);

	return ContinueModal();
}

BOOL CFortschrittDlg::Pulse()
{
	ASSERT(::IsWindow(m_hWnd));	
	
	DWORD dwFlags = 0;
	if (GetStyle() & DS_NOIDLEMSG)
		dwFlags |= MLF_NOIDLEMSG;

	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;
	MSG* pMsg = &AfxGetThread()->m_msgCur;
		
	// Check to see if we can do idle work
	while (bIdle && !::PeekMessage(pMsg, NULL, NULL, NULL, PM_NOREMOVE))
	{
		if (!(dwFlags & MLF_NOIDLEMSG) && m_hWndParent && lIdleCount == 0)
		{
			::SendMessage(m_hWndParent, WM_ENTERIDLE,
				MSGF_DIALOGBOX, (LPARAM)m_hWnd);
		}

		if ((dwFlags & MLF_NOKICKIDLE) ||
		!SendMessage(WM_KICKIDLE, MSGF_DIALOGBOX, lIdleCount++))
		{
			bIdle = FALSE;
		}
	}

	// Pump messages while available
	while (::PeekMessage(pMsg, NULL, NULL, NULL, PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage())
		{
			m_nFlags &= ~(WF_MODALLOOP|WF_CONTINUEMODAL);
			AfxPostQuitMessage(0);
			break; // No more messages
		}

		if (!ContinueModal())
		{
			m_nFlags &= ~(WF_MODALLOOP|WF_CONTINUEMODAL);
		}
	}

	return ContinueModal();
}

void CFortschrittDlg::CloseDialog()
{
	// hide the window before enabling the parent, etc.
	if (m_hWnd != NULL)
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW|
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);

	if (m_bEnableParent)
		::EnableWindow(m_hWndParent, TRUE);
	if (m_hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(m_hWndParent);

	// destroy modal window
	DestroyWindow();
	PostModal();

	// unlock/free resources as necessary
	if (m_lpszTemplateName != NULL || m_hDialogTemplate != NULL)
		UnlockResource(m_hModalDialogTemplate);
	if (m_lpszTemplateName != NULL)
		FreeResource(m_hModalDialogTemplate);

	m_hWndParent = NULL;
	m_bEnableParent = FALSE;
	m_hModalDialogTemplate = NULL;

	KillTimer(10);
}

int CFortschrittDlg::GetModalResult() const
{
	return m_nModalResult;
}


CWnd* CFortschrittDlg::GetProgressControl()
{
	if (m_ctlProgressCtrl.m_hWnd)
		return &m_ctlProgressCtrl;
	return NULL;
}

void CFortschrittDlg::SetRange(short nLower, short nUpper)
{
	if (m_ctlProgressCtrl.m_hWnd)
		m_ctlProgressCtrl.SendMessage(PBM_SETRANGE, 0,
			MAKELPARAM(nLower, nUpper));
}

int CFortschrittDlg::SetPos(int nPos)
{
	if (m_ctlProgressCtrl.m_hWnd)
		return (int) LOWORD(m_ctlProgressCtrl.SendMessage(PBM_SETPOS, nPos, 0L));
	return 0;
}

int CFortschrittDlg::OffsetPos(int nPos)
{
	if (m_ctlProgressCtrl.m_hWnd)
		return (int) LOWORD(m_ctlProgressCtrl.SendMessage(PBM_DELTAPOS, nPos, 0L));
	return 0;
}

int CFortschrittDlg::SetStep(int nStep)
{
	if (m_ctlProgressCtrl.m_hWnd)
		return (int) LOWORD(m_ctlProgressCtrl.SendMessage(PBM_SETSTEP, nStep, 0L));
//	else
//		AfxMessageBox("error");
	return 0;
}

int CFortschrittDlg::StepIt()
{
	Pulse();
	if (m_ctlProgressCtrl.m_hWnd)
		return (int) LOWORD(m_ctlProgressCtrl.SendMessage(PBM_STEPIT, 0, 0L));
	return 0;
}

BOOL CFortschrittDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//build the dialog caption
	//data
	CString _str(_T(""));
	//code
	SetWindowText(m_strWhatToDo);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CFortschrittDlg::SetStrFortschritt(CString string)
{
	m_strFortschritt = string;
	//data
	int _iRet;
	//code
	if (m_ctlStaticCtrl.m_hWnd)
	{
		_iRet = (int)LOWORD(m_ctlStaticCtrl.SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)string));
		UpdateWindow();
		return _iRet;
	}
	return 0;
}

int CFortschrittDlg::SetCaption(CString string)
{
	return (int) LOWORD(SendMessage(WM_SETTEXT, 0, (LPARAM)(LPCTSTR)string));

}

void CFortschrittDlg::OnOK()
{
	//no action!!!
}

void CFortschrittDlg::OnCancel()
{
	//no action!!!
}
/*
LRESULT CFortschrittDlg::OnHelp(WPARAM, LPARAM)
{
	//no action!!!
	return TRUE;
}
*/
void CFortschrittDlg::OnTimer(UINT nIDEvent) 
{	
	if(nIDEvent == 10)
	{
		StepIt();
	}

	CDialog::OnTimer(nIDEvent);
}
