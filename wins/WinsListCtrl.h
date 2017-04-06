#if !defined(AFX_WINSLISTCTRL_H__2D0B0280_1713_11D7_B598_0050DA3B1C7E__INCLUDED_)
#define AFX_WINSLISTCTRL_H__2D0B0280_1713_11D7_B598_0050DA3B1C7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WinsListCtrl.h : Header-Datei
//
#include "wins.h"
/////////////////////////////////////////////////////////////////////////////
// Fenster CWinsListCtrl 

class CWinsListCtrl : public CListCtrl
{
// Konstruktion
public:
	typedef struct tagLISTSORT
	{
		CListCtrl* list;
		int iSubItem;
		BOOL bUp;
		tagLISTSORT()
		{
			list = NULL;
			iSubItem = -1;
			bUp = FALSE;
		};

	} LISTSORT;

	tagLISTSORT m_ListSort;
	static int CALLBACK OnCompareTwoItems(LPARAM lItem1, LPARAM lItem2, LPARAM lParam);

	CWinsListCtrl();
	CImageList m_ImageList;
	void SetSelectedItem(long i);
// Attribute
public:
	void AddItem(WINDATA *_pWindata);
	void SetItem(long _lItem);
	long GetSelectedItem();

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CWinsListCtrl)
	//}}AFX_VIRTUAL

// Implementierung
public:
	void Setup();
	virtual ~CWinsListCtrl();

	// Generierte Nachrichtenzuordnungsfunktionen
public:
	//{{AFX_MSG(CWinsListCtrl)
		afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_WINSLISTCTRL_H__2D0B0280_1713_11D7_B598_0050DA3B1C7E__INCLUDED_
