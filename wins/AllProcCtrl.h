#if !defined(AFX_ALLPROCCTRL_H__13F062B4_8EDA_4314_98F6_08BC952B2184__INCLUDED_)
#define AFX_ALLPROCCTRL_H__13F062B4_8EDA_4314_98F6_08BC952B2184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AllProcCtrl.h : Header-Datei
//

#include "IPProcTree.h"

/////////////////////////////////////////////////////////////////////////////
// Fenster CAllProcCtrl 

typedef BOOL (WINAPI * PFNENUMPROCESSES)(DWORD * lpidProcess,DWORD cb,DWORD * cbNeeded);
typedef BOOL (WINAPI * PFNENUMPROCESSMODULES)(HANDLE hProcess,HMODULE *lphModule,DWORD cb,LPDWORD lpcbNeeded);
typedef DWORD (WINAPI * PFNGETMODULEFILENAMEEXA)(HANDLE hProcess,HMODULE hModule,LPSTR lpFilename,DWORD nSize);


class CAllProcCtrl : public CIPProcTree
{
// Konstruktion
public:
	CAllProcCtrl();

// Attribute
public:
	CImageList m_ImageListStatus;
// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAllProcCtrl)
	//}}AFX_VIRTUAL

// Implementierung
public:
	void SetSelectedItemStateIconAndText();
	void Setup();
	void OnRBClick();
	void OnLBDblClick();
	void OnLBClick();
	void Empty();
	void Fill();
	virtual ~CAllProcCtrl();
	void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CAllProcCtrl)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ALLPROCCTRL_H__13F062B4_8EDA_4314_98F6_08BC952B2184__INCLUDED_
