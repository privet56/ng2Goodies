// IPHTMLMetaCrawlerSammler.h: Schnittstelle für die Klasse CIPHTMLMetaCrawlerSammler.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPHTMLMETACRAWLERSAMMLER_H__DA3D3C1A_0E33_44FA_8053_73C4BCE242AC__INCLUDED_)
#define AFX_IPHTMLMETACRAWLERSAMMLER_H__DA3D3C1A_0E33_44FA_8053_73C4BCE242AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPHTMLMetaCrawler.h"

class CIPHTMLMetaCrawlerSammler : public CIPHTMLMetaCrawler  
{
public:
	CIPHTMLMetaCrawlerSammler();
	virtual ~CIPHTMLMetaCrawlerSammler();
	virtual BOOL OnMeta(const CIPString &strName, const CIPString &strContent, const CIPString &strFileName, const CIPString &strType);
	virtual BOOL OnHTML(DWORD dwPos);
	virtual BOOL OnTitle(const CIPString &strTitle);
	virtual BOOL OnBody(DWORD dwPos);
	virtual BOOL OnHead(DWORD dwPos);
	virtual BOOL OnBase(DWORD dwPos, DWORD dwLength);
	CMapStringToString smMETAs;
};

#endif // !defined(AFX_IPHTMLMETACRAWLERSAMMLER_H__DA3D3C1A_0E33_44FA_8053_73C4BCE242AC__INCLUDED_)
