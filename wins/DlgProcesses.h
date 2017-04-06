#if !defined(AFX_DLGPROCESSES_H__92E55BFC_BC8D_4CDF_8A0C_9B4DD7726F6C__INCLUDED_)
#define AFX_DLGPROCESSES_H__92E55BFC_BC8D_4CDF_8A0C_9B4DD7726F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProcesses.h : Header-Datei
//
#include "ipproctree.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgProcesses 

#define  MEGABYTE   1048576 
#define  GIGABYTE   1073741824 
#define  DB_DEF_IOSIZE   (8 * 1024) 

#include <direct.h>
#include <shlwapi.h>
#include "ModulVer.h"


class CDlgProcesses : public CDialog
{
// Konstruktion
public:
	BOOL SetItemData(HTREEITEM hti, UINT uType, DWORD dwProcessID, CIPString sModFN, CIPString sTitle, MODULEENTRY32* pme);
	BOOL IsInArray(CIPString sName, CIPStringArray *pArray);
	BOOL IsValidFunctionName(CIPString sFuName);
	BOOL FillImpsFromHModule(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis);
	BOOL FillExpsFromHModule(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis);
	BOOL FillImpsExpsFromHModule(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis);
	BOOL FillImpsExpsFromHModule2(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis);
	HTREEITEM GetItemFromName(CIPString sTitle, CArray<HTREEITEM, HTREEITEM> *paHtis);
	TREEITEMDATA* GetItemDataFromProcID(DWORD dwProcID, DWORD dwModuleID);
	DWORD m_dwProcID;
	CDlgProcesses(DWORD dwProcID, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgProcesses)
	enum { IDD = IDD_PROCESSES_DLG };
	CIPProcTree	m_oProcTree;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgProcesses)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	LRESULT OnFillTree(WPARAM wp, LPARAM lp);
// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgProcesses)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkProcTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGPROCESSES_H__92E55BFC_BC8D_4CDF_8A0C_9B4DD7726F6C__INCLUDED_
