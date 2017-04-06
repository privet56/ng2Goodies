// winsDlg.h : Header-Datei
//

#if !defined(AFX_WINSDLG_H__286BC5A4_1683_11D7_B598_0050DA3B1C7E__INCLUDED_)
#define AFX_WINSDLG_H__286BC5A4_1683_11D7_B598_0050DA3B1C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CWinsDlg Dialogfeld

#include "WinsListCtrl.h"
#include <afxtempl.h>
#include "HyperLink.h"
#include "AllProcCtrl.h"
#include "btnSHI.h"


#ifdef USING_NONMFC_TRAY  // This is set in project settings
#include "SystemTraySDK.h"
#else
#include "SystemTray.h"
#endif

#define WM_MESSAFTERONINIT 2002
#define WM_TRAY_ICON_NOTIFY_MESSAGE 2003

static UINT WM_TASKBARCREATED;

class CWinsDlg : public CDialog
{
// Konstruktion
	CButtonSHI m_cTreeChk;
public:
	void OnHideShow();
	void OnHideShowApp();
	void OnChangeWinColor();

	void OnExit();
	LRESULT OnTaskBarCreated(WPARAM wp, LPARAM lp);
	LRESULT OnTrayIconClick(WPARAM wp, LPARAM lp);
	CWinsDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	LRESULT OnRefreshMessage(WPARAM wp, LPARAM lp);

//lauftext
	void Lauf();
	int i;
	int ii;
	CString m_strbrLauf;
//lauftext end
// Dialogfelddaten
	//{{AFX_DATA(CWinsDlg)
	enum { IDD = IDD_WINS_DIALOG };
	CAllProcCtrl	m_cTree;
	CHyperLink	m_ctrlInfoSt;
	CWinsListCtrl	m_ctrlList;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CWinsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;
public:
	WINDATA* GetSelItem();
	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CWinsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowB();
	afx_msg void OnHideB();
	virtual void OnOK();
	afx_msg void OnInfoSt();
	afx_msg void OnRefreshB();
	afx_msg void OnShowProcessesB();
	afx_msg void OnWindows();
	afx_msg void OnEfficiency();
	afx_msg void OnTopMost();
	afx_msg void OnRenameB();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnCloseappB();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTreeChk();
	afx_msg void OnClickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_WINSDLG_H__286BC5A4_1683_11D7_B598_0050DA3B1C7E__INCLUDED_)
