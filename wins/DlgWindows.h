#if !defined(AFX_DLGWINDOWS_H__29874C81_2240_4CC6_AB86_538F4DC30290__INCLUDED_)
#define AFX_DLGWINDOWS_H__29874C81_2240_4CC6_AB86_538F4DC30290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWindows.h : Header-Datei
//
#include "ipproctree.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgWindows 

typedef struct {
  UINT  cbSize;
  HWND  hwnd;
  DWORD dwFlags;
  UINT  uCount;
  DWORD dwTimeout;
} FLASHWINFO, *PFLASHWINFO;

#define FLASHW_STOP         0 
#define FLASHW_CAPTION      0x00000001 
#define FLASHW_TRAY         0x00000002 
#define FLASHW_ALL          (FLASHW_CAPTION | FLASHW_TRAY) 
#define FLASHW_TIMER        0x00000004 
#define FLASHW_TIMERNOFG    0x0000000C 


class CDlgWindows : public CDialog
{
// Konstruktion
public:
	static CIPString GetClassNameDesc(CIPString sClassName);
	static CIPString GetWinIcon(HWND h);
	BOOL IsInArray(CArray<HWND, HWND> &ahs, HWND h, BOOL bAdd);
	LRESULT OnFillTree(WPARAM wp, LPARAM lp);
	static CIPString GetWinTxt(HWND hwnd, BOOL bWithhwnd=TRUE);
	DWORD m_dwProcID;
	HWND m_HWND;
	CDlgWindows(DWORD dwProcID,	HWND h, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgWindows)
	enum { IDD = IDD_WINDOWS_DLG };
	CIPProcTree	m_oTree;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgWindows)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgWindows)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingWinTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

int CALLBACK wndEnumProc(HWND hwnd, LPARAM lParam);

#endif // AFX_DLGWINDOWS_H__29874C81_2240_4CC6_AB86_538F4DC30290__INCLUDED_
