#if !defined(AFX_DLGEFFICIENCY_H__F2785B8B_6D46_4774_90BB_A4AB3D23A557__INCLUDED_)
#define AFX_DLGEFFICIENCY_H__F2785B8B_6D46_4774_90BB_A4AB3D23A557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEfficiency.h : Header-Datei
//

#include "OScopeCtrl.h"
#include "cpuusage.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEfficiency 

class CDlgEfficiency : public CDialog
{
// Konstruktion
public:
	COScopeCtrl m_meter;
	double m_iMax;
	int m_iTimerCalls;
	double m_LASTdcputime_curpr;
	double m_LASTdrealime_curpr;
	double m_LASTdcputime_pr;

	CCpuUsage m_usage;
	WINDATA* m_pwind;
	CDlgEfficiency(WINDATA* _pwind, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgEfficiency)
	enum { IDD = IDD_EFFICIENCY_DLG };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgEfficiency)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgEfficiency)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGEFFICIENCY_H__F2785B8B_6D46_4774_90BB_A4AB3D23A557__INCLUDED_
