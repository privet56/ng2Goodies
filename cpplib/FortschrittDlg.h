#if !defined(AFX_FORTSCHRITT_H__71460DF7_87B2_11D3_B027_0000E86B7B3E__INCLUDED_)
#define AFX_FORTSCHRITT_H__71460DF7_87B2_11D3_B027_0000E86B7B3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FortschrittDlg.h : Header-Datei
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFortschrittDlg

class CFortschrittDlg : public CDialog
{
// Konstruktion
public:
	int SetCaption(CString string);
	int SetStrFortschritt(CString string);
	CString m_strWhatToDo;
	UINT m_iAvi;
	int OffsetPos(int nPos);
	int SetPos(int nPos);
	void SetRange(short nLower, short nUpper);
	CWnd* GetProgressControl();
	int StepIt();
	int SetStep(int nStep);
	void CommonConstruct();
	int GetModalResult() const;
	void CloseDialog();
	BOOL Pulse();
	int DoModal();
	CFortschrittDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CFortschrittDlg)
	enum { IDD = IDD_PRGRSS_DLG };
	CProgressCtrl	m_ctlProgressCtrl;
	CStatic			m_ctlStaticCtrl;
	CString			m_strFortschritt;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CFortschrittDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
	virtual void OnOK();
	virtual void OnCancel();

// Implementierung
protected:
	HGLOBAL m_hModalDialogTemplate;
	BOOL m_bEnableParent;
	HWND m_hWndParent;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CFortschrittDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_FORTSCHRITT_H__71460DF7_87B2_11D3_B027_0000E86B7B3E__INCLUDED_

/* usage:
	m_FortschrDlg.SetStrFortschritt(_T("Bitte warten Sie, während die Collection erstellt wird..."));
	m_FortschrDlg.m_strWhatToDo =   _T("Bitte warten Sie, während die Collection erstellt wird...");
	m_FortschrDlg.DoModal();
	m_FortschrDlg.SetRange(0, 20);
	m_FortschrDlg.Pulse();

	...
	
	m_FortschrDlg.CloseDialog();
*/
