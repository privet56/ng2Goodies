// IPHTMLMetaCrawlerSammler.cpp: Implementierung der Klasse CIPHTMLMetaCrawlerSammler.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "IPHTMLMetaCrawlerSammler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIPHTMLMetaCrawlerSammler::CIPHTMLMetaCrawlerSammler()
{

}

CIPHTMLMetaCrawlerSammler::~CIPHTMLMetaCrawlerSammler()
{

}

BOOL CIPHTMLMetaCrawlerSammler::OnHTML(DWORD dwPos)
{
	//override to act on html
	return TRUE;
}

BOOL CIPHTMLMetaCrawlerSammler::OnBody(DWORD dwPos)
{
	//override to act on html
	return TRUE;
}

BOOL CIPHTMLMetaCrawlerSammler::OnBase(DWORD dwPos, DWORD dwLength)
{
	//override to act on html
	return TRUE;
}

BOOL CIPHTMLMetaCrawlerSammler::OnHead(DWORD dwPos)
{
	//override to act on html
	return TRUE;
}

BOOL CIPHTMLMetaCrawlerSammler::OnTitle(const CIPString &strTitle)
{
	if(strTitle.IsEmpty())
		return TRUE;
	CIPString sMapContent(_T(""));
	smMETAs.Lookup(_T("title"), sMapContent);
	if( sMapContent.GetLength() > 0)
		sMapContent += _T(" "+strTitle);
	else
		sMapContent = strTitle;
	smMETAs.SetAt(_T("title"), sMapContent);
	return TRUE;
}

BOOL CIPHTMLMetaCrawlerSammler::OnMeta(const CIPString &strName, const CIPString &strContent, const CIPString &strFileName, const CIPString &strType)
{
	CIPString sName(strName);
	CIPString sCont(strContent);
	if(strContent.IsEmpty())
	{
		sName	=_T("aname");
		sCont	=strName;
	}

	CIPString sMETAName(sName);
	sMETAName.MakeLower();
	CIPString sMapContent(_T(""));
	smMETAs.Lookup(sMETAName, sMapContent);
	if( sMapContent.GetLength() > 0)
		sMapContent += _T(" "+sCont);
	else
		sMapContent = sCont;
	smMETAs.SetAt(sMETAName, sMapContent);
	return TRUE;
}
