// IPProcTree.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "IPProcTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPProcTree

CIPProcTree::CIPProcTree()
{
}

CIPProcTree::~CIPProcTree()
{
}


BEGIN_MESSAGE_MAP(CIPProcTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CIPProcTree)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CIPProcTree 

BOOL CIPProcTree::Setup()
{
	//create default image list
	if (m_ImageList.m_hImageList == NULL)
	{
		m_ImageList.Create(16, 16, ILC_COLOR24 |ILC_MASK /*ILC_COLOR4*/, 0, 50);
		SetImageList(&m_ImageList, TVSIL_NORMAL);
		SetItemHeight(22);
	}

	//delete prev. items
	DeleteAllItems();

	return TRUE;
}
