// IPVOLEWordAutomation.h: Schnittstelle für die Klasse CIPVOLEWordAutomation.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPVOLEWORDAUTOMATION_H__B841DFB0_156C_44A0_8FF9_1358629ACC3E__INCLUDED_)
#define AFX_IPVOLEWORDAUTOMATION_H__B841DFB0_156C_44A0_8FF9_1358629ACC3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define	DOC		0
#define	DOT		1
#define	TXT		2
#define	RTF		6
#define	HTM		8
#define	HTML	8
#define	ASC		9
#define	WRI		13
#define	WPS		28
#define	DEFAULT	0

#include "Afxtempl.h"
#include "ipstring.h"
#include <atlbase.h>


class CIPVOLEWordAutomation  
{
public:
	BOOL EmbedPictures(CComPtr<IDispatch> &pDocument);
	BOOL DoEmbed(CComPtr<IDispatch> &listEmbedable);
	BOOL InvokeDispatchMethod(CComPtr<IDispatch> pDispatch, CIPString &sMethodName, WORD wMethodType, DISPPARAMS &dpParameter, VARIANT &vResult, EXCEPINFO &infoException);

	CIPVOLEWordAutomation();
	virtual ~CIPVOLEWordAutomation();

	void ErrHandler(HRESULT hr, EXCEPINFO excep, CIPString sAt=_T(""));

	void OpenDocument(CString _sPathName);
	void CloseDocument();
	void ShowDocument();
	void CloseWord();
	void Paste();
	BOOL Search(CString _sSearch);
	void SaveAs(CString _sPathName, long _lType);
	void Delete();
	void ActiveDocumentClose();


public:

    IUnknown* m_pUnk;

    // IDispatch pointers for Word's objects
    IDispatch* m_pDispApp;		//App
    IDispatch* m_pDispDocs;      //Documents collection
    IDispatch* m_pDispActiveDoc; //ActiveDocument object
    IDispatch* m_pDispSel;       //Selection object
    IDispatch* m_pDispFind;		//Find

    DISPID		m_dispid_App;		//App
    DISPID		m_dispid_Docs;      //Documents property of Application //object
	DISPID		m_dispid_ActiveDoc;	//active DOC
    DISPID		m_dispid_DocsOpen;  //AOpen Documents
	DISPID		m_dispid_Sel;		//Selection
	DISPID		m_dispid_Find;		//Find
	DISPID		m_dispid_SaveAs;	//SaveAs method of the Document object										
	DISPID		m_dispid_Quit;
	OLECHAR FAR* m_szFunction;
	HRESULT m_hr ;

	void OnInit();

};

#endif // !defined(AFX_IPVOLEWORDAUTOMATION_H__B841DFB0_156C_44A0_8FF9_1358629ACC3E__INCLUDED_)
