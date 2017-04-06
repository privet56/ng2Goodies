#if !defined(AFX_IPPROCTREE_H__5CC87A3B_E885_4507_A383_A5AC82FA45A4__INCLUDED_)
#define AFX_IPPROCTREE_H__5CC87A3B_E885_4507_A383_A5AC82FA45A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPProcTree.h : Header-Datei
//
#include "IPImageList.h"
/////////////////////////////////////////////////////////////////////////////
// Fenster CIPProcTree 

class CIPProcTree : public CTreeCtrl
{
// Konstruktion
public:
	CIPProcTree();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CIPProcTree)
	//}}AFX_VIRTUAL

// Implementierung
public:
	BOOL Setup();
	virtual ~CIPProcTree();
	CIPImageList m_ImageList;
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CIPProcTree)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_IPPROCTREE_H__5CC87A3B_E885_4507_A383_A5AC82FA45A4__INCLUDED_
