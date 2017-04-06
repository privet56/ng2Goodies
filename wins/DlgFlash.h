#if !defined(AFX_DLGFLASH_H__ECFE3848_4F75_4B9D_9EA3_B9D15CEB7906__INCLUDED_)
#define AFX_DLGFLASH_H__ECFE3848_4F75_4B9D_9EA3_B9D15CEB7906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFlash.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFlash 

class CDlgFlash : public CDialog
{
// Konstruktion
public:
	void DoShow(BOOL bShow, CWnd* p);
	CDlgFlash(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgFlash)
	enum { IDD = IDD_FLASHDLG };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFlash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFlash)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGFLASH_H__ECFE3848_4F75_4B9D_9EA3_B9D15CEB7906__INCLUDED_
