// wins.h : Haupt-Header-Datei für die Anwendung WINS
//

#if !defined(AFX_WINS_H__286BC5A2_1683_11D7_B598_0050DA3B1C7E__INCLUDED_)
#define AFX_WINS_H__286BC5A2_1683_11D7_B598_0050DA3B1C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole
#include "ipstring.h"
#include "ipstringarray.h"

#include <windows.h>
#include <tlhelp32.h>


#define MEMALLOC(x) GlobalAlloc(GPTR, x)
#define MEMFREE(x)  GlobalFree(x)


/////////////////////////////////////////////////////////////////////////////
// CWinsApp:
// Siehe wins.cpp für die Implementierung dieser Klasse
//

#define TYPE_NONE		0
#define TYPE_EXE		1
#define TYPE_DLL		2
#define TYPE_FUNCTION	3

typedef struct tagWINDATA
{
	tagWINDATA();

	HWND m_HWND;
	long m_lCount;
	CString m_sTitle;
	BOOL m_bEnabled;
	CString m_sModFN;
	BOOL m_bDlgBased;
	DWORD m_dwProcessID;
	int iItem;
} 
WINDATA, far*LPWINDATA;

typedef struct tagPROCWINS
{
	CArray<HWND, HWND> m_ahWnds;
	DWORD m_dwProcessID;
} 
PROCWINS, far*LPPROCWINS;


typedef struct tagTREEITEMDATA
{
	tagTREEITEMDATA();
	tagTREEITEMDATA(tagTREEITEMDATA &tid);
	tagTREEITEMDATA& operator =(tagTREEITEMDATA &tid);

	DWORD m_dwProcessID;
	CString m_sTitle;
	CString m_sModFN;
	CArray<MODULEENTRY32, MODULEENTRY32> m_aChildren;
	UINT uType;
	MODULEENTRY32 me;

	HTREEITEM m_hti;
} 
TREEITEMDATA, far*LPTREEITEMDATA;


class CWinsApp : public CWinApp
{
public:
	LRESULT OnMsgSingleInstance(WPARAM wp, LPARAM lp);
	CWinsApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CWinsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CWinsApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
void GetIndex( char *, char * );
CString DisplayFilename( DWORD );
BOOL __Log(CIPString _strToWrite);
BOOL GetProcessModule (DWORD dwPID, DWORD dwModuleID, LPMODULEENTRY32 lpMe32, DWORD cbMe32, CArray<MODULEENTRY32, MODULEENTRY32> *paChildren);
CIPString __GetMyDir();
CIPString __GetCFG(CIPString sEntry);
void __IPVSleep(int nMilliSeconds);
IMAGE_NT_HEADERS ReadPEHeader(HANDLE FHandle, int VirusSections);

PROC WINAPI HookImportedFunction(HMODULE hModule, PSTR FunctionModule, PSTR FunctionName, PROC pfnNewProc, CIPStringArray *paImpFuncs);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_WINS_H__286BC5A2_1683_11D7_B598_0050DA3B1C7E__INCLUDED_)
