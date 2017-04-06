#if !defined(AFX_PlainHTMLView_H__0112103B_4369_48EF_BD73_95B3B2C4BCC2__INCLUDED_)
#define AFX_PlainHTMLView_H__0112103B_4369_48EF_BD73_95B3B2C4BCC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlainHTMLView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// CPlainHTMLView HTML-Ansicht

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <afxhtml.h>
#include <mshtmhst.h>
#include <IPString.h>



class CPlainHTMLView : public CHtmlView
{
public:
	CPlainHTMLView();           // gesch�tzter Konstruktor wird von dynamischer Erstellung verwendet
	virtual ~CPlainHTMLView();
	DECLARE_DYNCREATE(CPlainHTMLView)

// HTML-Daten
public:
	//{{AFX_DATA(CPlainHTMLView)
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente hinzu
	//}}AFX_DATA

// Attribute
public:

// Operationen
public:

// �berladungen
	// �berladungen f�r virtuelle Funktionen, die vom Klassen-Assistenten erstellt wurden
	//{{AFX_VIRTUAL(CPlainHTMLView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Erstellte Funktionen f�r die Nachrichtenumsetzung
	//{{AFX_MSG(CPlainHTMLView)
		// HINWEIS - Hier werden Member-Funktionen vom Klassen-Assistenten hinzugef�gt und entfernt.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_PlainHTMLView_H__0112103B_4369_48EF_BD73_95B3B2C4BCC2__INCLUDED_
