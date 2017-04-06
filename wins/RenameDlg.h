#if !defined(AFX_RENAMEDLG_H__EDCFF361_1EF1_11D7_B59B_0050DA3B1C7E__INCLUDED_)
#define AFX_RENAMEDLG_H__EDCFF361_1EF1_11D7_B59B_0050DA3B1C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenameDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRenameDlg 

class CRenameDlg : public CDialog
{
// Konstruktion
public:
	CRenameDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CRenameDlg)
	enum { IDD = IDD_RENAME_DLG };
	CString	m_sTxt;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CRenameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CRenameDlg)
	afx_msg void OnChangeEdit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RENAMEDLG_H__EDCFF361_1EF1_11D7_B59B_0050DA3B1C7E__INCLUDED_
