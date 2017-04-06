// IPVOLEWordAutomation.cpp: Implementierung der Klasse CIPVOLEWordAutomation.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IPVOLEWordAutomation.h"
#include "IPString.h"
#include <io.h>				//declaration _access
#include "IPFile.h"
#include "ipglobal.h"
#include "IPHelpers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


BOOL __bDebug = FALSE;


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIPVOLEWordAutomation::CIPVOLEWordAutomation()
{
    m_dispid_App		= 0;	//App
    m_dispid_Docs		= 0;    //Documents property of Application //object
	m_dispid_ActiveDoc	= 0;	//active DOC
    m_dispid_DocsOpen	= 0;	//AOpen Documents
	m_dispid_Sel		= 0;	//Selection
	m_dispid_Find		= 0;	//Find
	m_dispid_SaveAs		= 0;	//SaveAs method of the Document object										

    m_pDispApp			= NULL;	//App
    m_pDispDocs			= NULL; //Documents collection
    m_pDispActiveDoc	= NULL; //ActiveDocument object
    m_pDispSel			= NULL; //Selection object
    m_pDispFind			= NULL;	//Find
	m_pUnk				= NULL;

	m_szFunction			= NULL;

	OnInit();
}


CIPVOLEWordAutomation::~CIPVOLEWordAutomation()
{
    //Clean-up
/*	if(m_pDispActiveDoc)	m_pDispActiveDoc->Release();
	if(m_pDispSel)			m_pDispSel->Release();
	if(m_pDispDocs)			m_pDispDocs->Release();
	if(m_pDispFind)			m_pDispFind->Release();
	if(m_pDispApp)			m_pDispApp->Release();
    if(m_pUnk)				m_pUnk->Release();
*/
}


void CIPVOLEWordAutomation::OnInit()
{
    //Initialize the COM libraries
    ::CoInitialize(NULL);

    // Create an instance of the Word application and obtain the 
    // pointer to the application's IDispatch interface.
    CLSID clsid;
    CLSIDFromProgID(L"Word.Application", &clsid);  

    m_hr = ::CoCreateInstance(clsid, NULL, CLSCTX_SERVER, IID_IUnknown, (void**) &m_pUnk);
    if(SUCCEEDED(m_hr))
		m_hr = m_pUnk->QueryInterface(IID_IDispatch, (void**)&m_pDispApp);
}


void CIPVOLEWordAutomation::ErrHandler(HRESULT _hr, EXCEPINFO _excep, CIPString sAt/*=_T("")*/)
{
	if(!__bDebug)return;
    if(_hr==DISP_E_EXCEPTION)
    {
        char errDesc[512];
        char errMsg[512];
        wcstombs(errDesc, _excep.bstrDescription, 512);
        sprintf(errMsg, "Run-time error %d:\n\n %s", 
                _excep.scode & 0x0000FFFF,  //Lower 16-bits of SCODE
                errDesc);                  //Text error description
        ::MessageBox(NULL, CIPString(sAt.IsEmpty() ? "" : sAt+"\n\n") + errMsg, "Server Error", MB_SETFOREGROUND | MB_OK);
    }
    else
    {
        LPVOID lpMsgBuf;
        ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, _hr,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0, NULL);
        ::MessageBox(NULL, (LPCTSTR)lpMsgBuf, "COM Error", MB_OK | MB_SETFOREGROUND);
        ::LocalFree( lpMsgBuf );
    }

}

void CIPVOLEWordAutomation::CloseDocument()
{
	if(m_pDispActiveDoc == NULL)return;

	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	VARIANT _vCloseArguments[1];
	_vCloseArguments[0].vt		= VT_BOOL;
	_vCloseArguments[0].lVal	= 0;	

	DISPPARAMS _dpClose;
	_dpClose.cArgs = 1;
    _dpClose.cNamedArgs = 0;
    _dpClose.rgvarg = _vCloseArguments;

	CComPtr<IDispatch> pDocument;
	pDocument.Attach(this->m_pDispActiveDoc);

	if(!InvokeDispatchMethod(pDocument, CIPString(_T("Close")), DISPATCH_METHOD, _dpClose, _vFunctionResult, _infoException))
	{
		pDocument.Detach();
		m_pDispActiveDoc = NULL;
		return;
	}
	pDocument.Detach();
	m_pDispActiveDoc = NULL;

	return;
}

void CIPVOLEWordAutomation::CloseWord()
{
	//Letzte Änderung oder Erstellung  14:16:32  ;  12.11.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//schliesst Word (nicht getestet)

	//Invoke the method
    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};

    m_szFunction = OLESTR("Quit");
    m_hr = m_pDispApp->GetIDsOfNames(IID_NULL, &m_szFunction, 1, 
                                 LOCALE_USER_DEFAULT, &m_dispid_Quit);
    m_hr = m_pDispApp->Invoke (m_dispid_Quit, IID_NULL, 
                           LOCALE_USER_DEFAULT, DISPATCH_METHOD,
                           &dpNoArgs, NULL, NULL, NULL);


    //Clean-up
	if(m_pDispActiveDoc)	m_pDispActiveDoc->Release();
	if(m_pDispSel)			m_pDispSel->Release();
	if(m_pDispDocs)			m_pDispDocs->Release();
	if(m_pDispFind)			m_pDispFind->Release();
	if(m_pDispApp)			m_pDispApp->Release();
    if(m_pUnk)				m_pUnk->Release();

    ::CoUninitialize();
}

void CIPVOLEWordAutomation::ShowDocument()
{
	//Letzte Änderung oder Erstellung  14:13:28  ;  12.11.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//Make Word Visible
//    OLECHAR FAR* szFunction;
	DISPID dispid_Visible;
//	HRESULT m_hr ;

	m_szFunction = OLESTR("Visible");
	m_hr = m_pDispApp->GetIDsOfNames(IID_NULL, &m_szFunction, 1, 
								 LOCALE_USER_DEFAULT, &dispid_Visible);
	VARIANT pArgs2[1];
	DISPPARAMS dpVisible;
	pArgs2[0].vt= VT_BOOL;
	pArgs2[0].boolVal = TRUE;
	dpVisible.cArgs = 1;
	dpVisible.cNamedArgs = 1;
	dpVisible.rgvarg = pArgs2;
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	dpVisible.rgdispidNamedArgs = &dispidNamed;

	m_hr = m_pDispApp->Invoke (dispid_Visible, IID_NULL, LOCALE_USER_DEFAULT,
						   DISPATCH_PROPERTYPUT, &dpVisible, NULL, NULL, 
						   NULL);

}


void CIPVOLEWordAutomation::OpenDocument(CString _sPathName)
{
	//Letzte Änderung oder Erstellung  09:25:39  ;  11.11.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//Öffnet ein Word-Dokument

	if(_sPathName.IsEmpty()) return;

    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};
//    OLECHAR FAR* szFunction;
//	HRESULT m_hr ;

	VARIANT vResult;
    BSTR _bstrTemp;
	EXCEPINFO excep;

	//------------- Get Document -----------------
    // Get IDispatch* for the Documents collection object
    m_szFunction = OLESTR("Documents");
    m_hr = m_pDispApp->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &m_dispid_Docs);
    m_hr = m_pDispApp->Invoke (m_dispid_Docs, IID_NULL, 
                           LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, 
                           &dpNoArgs, &vResult, &excep, NULL);
    m_pDispDocs = vResult.pdispVal;

    if (FAILED(m_hr))  ErrHandler(m_hr, excep);


	//-----------Open Document-------------------
	VARIANT vArgsOpen[1];
    DISPPARAMS dpOpen;
    dpOpen.cArgs = 1;
    dpOpen.cNamedArgs = 0;
	dpOpen.rgvarg = vArgsOpen;

//    _bstrTemp = ::SysAllocString(OLESTR("c:\\doc1.doc"));
    _bstrTemp = _sPathName.AllocSysString();

    vArgsOpen[0].vt = VT_BSTR;         
	vArgsOpen[0].bstrVal = _bstrTemp;

	m_szFunction = OLESTR("Open");
    m_hr = m_pDispDocs->GetIDsOfNames(IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, 
                                  &m_dispid_DocsOpen);
    m_hr = m_pDispDocs->Invoke (m_dispid_DocsOpen, IID_NULL, 
						       LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
							   &dpOpen, &vResult, &excep, NULL);
    m_pDispActiveDoc = vResult.pdispVal;
    if (FAILED(m_hr))  ErrHandler(m_hr, excep);

    ::SysFreeString(_bstrTemp);

	if(__bDebug)ShowDocument();
}



void CIPVOLEWordAutomation::Delete()
{
	//Letzte Änderung oder Erstellung  21:31:15  ;  02.12.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//löscht die aktuelle Marktierung

    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};

	VARIANT vResult;
	EXCEPINFO excep;
	DISPID		m_dispid_Delete;	
    IDispatch*  m_pDispDelete;		

	m_dispid_Delete = 0;
	m_pDispDelete = NULL;

	if(m_pDispSel == NULL)	return;

	m_szFunction = OLESTR("Delete");
    m_hr = m_pDispSel->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &m_dispid_Delete);
    m_hr = m_pDispSel->Invoke (m_dispid_Delete, IID_NULL, 
							LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
							&dpNoArgs, &vResult, &excep, NULL);
//	vResult.boolVal;
/*
	if(vResult.boolVal)
		AfxMessageBox("1");
	else
		AfxMessageBox("0");

*/
	if (FAILED(m_hr))  ErrHandler(m_hr, excep);
}

BOOL CIPVOLEWordAutomation::Search(CString _sSearch)
{
	//Letzte Änderung oder Erstellung  14:33:07  ;  12.11.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//Search a String in an Document

    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};

	VARIANT vResult;
    BSTR _bstrTemp;
	EXCEPINFO excep;


    //----------------ActiveDocument object -----------------
    // Get IDispatch* for the Selection object
    m_szFunction = OLESTR("Selection");
    m_hr = m_pDispApp->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &m_dispid_Sel);
    m_hr = m_pDispApp->Invoke (m_dispid_Sel, IID_NULL, 
								LOCALE_USER_DEFAULT,DISPATCH_PROPERTYGET, 
								&dpNoArgs, &vResult, &excep, NULL);
    m_pDispSel= vResult.pdispVal;

    if (FAILED(m_hr))  ErrHandler(m_hr, excep);


	//-------------- Find-----------------
	m_szFunction = OLESTR("Find");
    m_hr = m_pDispSel->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &m_dispid_Find);
    m_hr = m_pDispSel->Invoke (m_dispid_Find, IID_NULL, 
							LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, 
							&dpNoArgs, &vResult, &excep, NULL);
	m_pDispFind = vResult.pdispVal;
	if (FAILED(m_hr))  ErrHandler(m_hr, excep);


	//------------- clear -----------------
    DISPID		_dispid_Clear; 
	m_szFunction = OLESTR("ClearFormatting");
    m_hr = m_pDispFind->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
	                                LOCALE_USER_DEFAULT, &_dispid_Clear);
    m_hr = m_pDispFind->Invoke (_dispid_Clear, IID_NULL, 
								LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
								&dpNoArgs, &vResult, &excep, NULL);
	if (FAILED(m_hr))  ErrHandler(m_hr, excep);

	//---------------- Search -------------
	//------------- Execute Find -----------------
	VARIANT vArgsSearch[1];
    DISPPARAMS dpSearch;
    dpSearch.cArgs = 1;
    dpSearch.cNamedArgs = 0;
	dpSearch.rgvarg = vArgsSearch;

//    _bstrTemp = ::SysAllocString(OLESTR(_sSearch);
    _bstrTemp = _sSearch.AllocSysString();

    vArgsSearch[0].vt = VT_BSTR;         
	vArgsSearch[0].bstrVal = _bstrTemp;


    DISPID		_dispid_Execute; 
	m_szFunction = OLESTR("Execute");
    m_hr = m_pDispFind->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &_dispid_Execute);
    m_hr = m_pDispFind->Invoke (_dispid_Execute, IID_NULL, 
							LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
							&dpSearch, &vResult, &excep, NULL);
	if (FAILED(m_hr))  ErrHandler(m_hr, excep);

    ::SysFreeString(_bstrTemp);


	//i have not fond entry
	if(vResult.boolVal == FALSE)
		return FALSE;

	return TRUE;
}



void CIPVOLEWordAutomation::ActiveDocumentClose()
{
	//Letzte Änderung oder Erstellung  14:47:56  ;  03.12.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//Schliesst da aktive Dokument

    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};

	VARIANT vResult;
	EXCEPINFO excep;
	DISPID		m_dispid_ActiveDocument;	
    

    m_szFunction = OLESTR("ActiveDocument");
    m_hr = m_pDispApp->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &m_dispid_ActiveDocument);
    m_hr = m_pDispApp->Invoke (m_dispid_ActiveDocument, IID_NULL, 
								LOCALE_USER_DEFAULT,DISPATCH_PROPERTYGET, 
								&dpNoArgs, &vResult, &excep, NULL);
    m_pDispActiveDoc= vResult.pdispVal;



    m_szFunction = OLESTR("Close");
    m_hr = m_pDispActiveDoc->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
									       LOCALE_USER_DEFAULT, &m_dispid_ActiveDocument);
    m_hr = m_pDispActiveDoc->Invoke (m_dispid_ActiveDocument, IID_NULL, 
									LOCALE_USER_DEFAULT,DISPATCH_METHOD, 
									&dpNoArgs, &vResult, &excep, NULL);




//    if(vResult.boolVal)

//    if (FAILED(m_hr))  ErrHandler(m_hr, excep);







/*
    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};

	VARIANT vResult;
	EXCEPINFO excep;
	DISPID		m_dispid_Delete;	
    IDispatch*  m_pDispDelete;		

	m_dispid_Delete = 0;
	m_pDispDelete = NULL;

	if(m_pDispSel == NULL)	return;

	m_szFunction = OLESTR("Delete");
    m_hr = m_pDispSel->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, &m_dispid_Delete);
    m_hr = m_pDispSel->Invoke (m_dispid_Delete, IID_NULL, 
							LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
							&dpNoArgs, &vResult, &excep, NULL);

  */


}



void CIPVOLEWordAutomation::SaveAs(CString _sPathName, long _lType)
{
	//Letzte Änderung oder Erstellung  17:05:53  ;  25.11.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//Speichert Dokument

/*
case "doc":
$convert_to=0;
Break;
case "dot":
$convert_to=1;
Break;
case "txt":
$convert_to=2;
Break;
case "rtf":
$convert_to=6;
Break;
case "htm":
$convert_to=8;
Break;
case "html":
$convert_to=8;
Break;
case "asc":
$convert_to=9;
Break;
case "wri":
$convert_to=13;
Break;
case "wps":
$convert_to=28;
Break;
default:
$convert_to=0;
*/
	//save first
	if(_sPathName.IsEmpty())	return;
	if(_lType < 0)				return;

	//only this Typs are allowd
	if( (_lType != DOC)		&&
		(_lType != DOT)		&&
		(_lType != TXT)		&&
		(_lType != RTF)		&&
		(_lType != HTM)		&&
		(_lType != HTML)	&&
		(_lType != ASC)		&&
		(_lType != WRI)		&&
		(_lType != WPS))		return;

    //Set up the DISPPARAMS for the SaveAs method (11 arguments)

    BSTR _bstrTemp;
	HRESULT m_hr ;
	EXCEPINFO excep;


    VARIANT vArgsSaveAs[11];
    DISPPARAMS dpSaveAs;
    dpSaveAs.cArgs = 11;
    dpSaveAs.cNamedArgs = 0;
    dpSaveAs.rgvarg = vArgsSaveAs;

	BSTR bstrEmptyString;
    bstrEmptyString = ::SysAllocString(OLESTR(""));

    VARIANT vFalse;
    vFalse.vt = VT_BOOL;
    vFalse.boolVal = FALSE;

//    bstrTemp = ::SysAllocString(OLESTR("c:\\doc1.doc"));
	_bstrTemp = _sPathName.AllocSysString();

    vArgsSaveAs[10].vt = VT_BSTR;         
    vArgsSaveAs[10].bstrVal = _bstrTemp;        //Filename
    vArgsSaveAs[9].vt = VT_I4;            
//    vArgsSaveAs[9].lVal = 0;                   //FileFormat
    vArgsSaveAs[9].lVal = _lType;   
    vArgsSaveAs[8] = vFalse;                   //LockComments
    vArgsSaveAs[7].vt = VT_BSTR;
    vArgsSaveAs[7].bstrVal = bstrEmptyString;  //Password
    vArgsSaveAs[6].vt = VT_BOOL;      
    vArgsSaveAs[6].boolVal = TRUE;             //AddToRecentFiles
    vArgsSaveAs[5].vt = VT_BSTR;
    vArgsSaveAs[5].bstrVal = bstrEmptyString;  //WritePassword
    vArgsSaveAs[4] = vFalse;                   //ReadOnlyRecommended
    vArgsSaveAs[3] = vFalse;                   //EmbedTrueTypeFonts
    vArgsSaveAs[2] = vFalse;                   //SaveNativePictureFormat
    vArgsSaveAs[1] = vFalse;                   //SaveFormsData
    vArgsSaveAs[0] = vFalse;                   //SaveAsOCELetter


    //Invoke the SaveAs method
    m_szFunction = OLESTR("SaveAs");
    m_hr = m_pDispActiveDoc->GetIDsOfNames(IID_NULL, &m_szFunction, 1, 
                                  LOCALE_USER_DEFAULT, 
                                  &m_dispid_SaveAs);
    m_hr = m_pDispActiveDoc->Invoke(m_dispid_SaveAs, IID_NULL, 
                                LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
                                &dpSaveAs, NULL, &excep, NULL);

    if (FAILED(m_hr))  ErrHandler(m_hr, excep);
	

	
	::SysFreeString(_bstrTemp);


}

void CIPVOLEWordAutomation::Paste()
{
	//Letzte Änderung oder Erstellung  14:33:35  ;  12.11.2003
	//von D.Bröcker Copyright by SHI Elektronische Medien GmbH
	//
	//Paste from Clipborad

    DISPPARAMS dpNoArgs = {NULL, NULL, 0, 0};
	HRESULT m_hr ;
	VARIANT vResult;
	EXCEPINFO excep;
	
	m_szFunction = OLESTR("Paste");
    m_hr = m_pDispSel->GetIDsOfNames (IID_NULL, &m_szFunction, 1, 
									  LOCALE_USER_DEFAULT, &m_dispid_App);
    m_hr = m_pDispSel->Invoke (m_dispid_App, IID_NULL, 
						      LOCALE_USER_DEFAULT, DISPATCH_METHOD, 
							   &dpNoArgs, &vResult, &excep, NULL);
    if (FAILED(m_hr))  ErrHandler(m_hr, excep);
}

BOOL CIPVOLEWordAutomation::EmbedPictures(CComPtr<IDispatch> &pDocument)
{
	//images are saved sometimes as fields and sometimes as shapes or inline shapes: so to embed all images both shapes/inline shapes and fields have to be "breaklinked"

	BOOL		_bResult = NULL;
	CIPString	_sErrMsg = "";

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	CComPtr<IDispatch> _pEmbedable = NULL;

	// embed all Fields from document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("Fields")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		return FALSE;
	}

	_pEmbedable = _vFunctionResult.pdispVal;

	if (_pEmbedable == NULL)
	{
		return FALSE;
	}

	_bResult = DoEmbed(_pEmbedable);
	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);
	//----------------------------//
	
	// embed all Shapes from document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("Shapes")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		return FALSE;
	}

	_pEmbedable = NULL;
	_pEmbedable = _vFunctionResult.pdispVal;

	if (_pEmbedable == NULL)
	{
		return FALSE;
	}

	_bResult = DoEmbed(_pEmbedable);
	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);
	//----------------------------//

	// embed all Inline Shapes from document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("InlineShapes")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		return FALSE;
	}

	_pEmbedable = NULL;
	_pEmbedable = _vFunctionResult.pdispVal;

	if (_pEmbedable == NULL)
	{
		return FALSE;
	}

	_bResult = DoEmbed(_pEmbedable);
	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);
	//----------------------------//

	return _bResult;
}

BOOL CIPVOLEWordAutomation::InvokeDispatchMethod(CComPtr<IDispatch> pDispatch, CIPString &sMethodName, WORD wMethodType, DISPPARAMS &dpParameter, VARIANT &vResult, EXCEPINFO &infoException)
{
	OLECHAR FAR* _sOleFunction = sMethodName.AllocSysString();
	DISPID _dispidFunction;

	if (!SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, &_sOleFunction, 1, LOCALE_USER_DEFAULT, &_dispidFunction)))
	{
		if(__bDebug)AfxMessageBox("InvokeDispatchMethod\tERR:!getidsofnames:'"+sMethodName+"'");
		SysFreeString(_sOleFunction);
		return FALSE;
	}

	HRESULT hRes = pDispatch->Invoke(_dispidFunction, IID_NULL, LOCALE_USER_DEFAULT, wMethodType, &dpParameter, &vResult, &infoException, NULL);
	if (!SUCCEEDED(hRes))
	{
		this->ErrHandler(hRes, infoException, "method:'"+sMethodName+"'");
		//ReportHRESULT(hRes);
		//ReportEXCEPINFO(infoException);
		SysFreeString(_sOleFunction);
		return FALSE;
	}

	SysFreeString(_sOleFunction);

	return TRUE;
}

BOOL CIPVOLEWordAutomation::DoEmbed(CComPtr<IDispatch> &listEmbedable)
{
	CIPString sCFG_debug="0";

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	long _lElementCount = 0;

	if (!InvokeDispatchMethod(listEmbedable, CIPString(_T("Count")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
        __WriteLogFile(_T("ooa:DoEmbed\tERR:1"),0,0,sCFG_debug);
		return FALSE;
	}

	_lElementCount = _vFunctionResult.lVal;

	if (_lElementCount == 0)
	{
		__WriteLogFile(_T("ooa:DoEmbed\tINF:nopics"),0,0,sCFG_debug);
		return TRUE;
	}

	int iEmbeddeds=0;

	for (long _iElementIndex = 0; _iElementIndex <= _lElementCount; _iElementIndex++)
	{
		// retrive embedable at specified Index //
		VARIANT _vGetAtArguments[1];

		_vGetAtArguments[0].vt		= VT_I4;         
		_vGetAtArguments[0].lVal	= _iElementIndex;	//Item Index

		DISPPARAMS _dpGetAt;
		_dpGetAt.cArgs = 1;
		_dpGetAt.cNamedArgs = 0;
		_dpGetAt.rgvarg = _vGetAtArguments;

		if(!InvokeDispatchMethod(listEmbedable, CIPString(_T("Item")), DISPATCH_METHOD, _dpGetAt, _vFunctionResult, _infoException))
			continue;

		CComPtr<IDispatch> _pEmbedable = NULL;
		_pEmbedable = _vFunctionResult.pdispVal;

		if (_pEmbedable == NULL)
			continue;
		//----------------------------------//

		// retrieve link format for embedable //
		if (!InvokeDispatchMethod(_pEmbedable, CIPString(_T("LinkFormat")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
			continue;

		CComPtr<IDispatch> _pLinkFormat = NULL;
		_pLinkFormat = _vFunctionResult.pdispVal;

		if (_pLinkFormat == NULL)
			continue;
		//----------------------------------------//

		// break link //
		if (!InvokeDispatchMethod(_pLinkFormat, CIPString(_T("BreakLink")), DISPATCH_METHOD, _dpNoArgs, _vFunctionResult, _infoException))
			continue;

		iEmbeddeds++;
	}

	{
		CIPString s;
		s.FromInt(iEmbeddeds);
		__WriteLogFile(_T("ooa:DoEmbed\tINF:embeddeds:"+s),0,0,sCFG_debug);
	}
	return TRUE;
}



/*

HRESULT CIPVOLEWordAutomation::OleCallFunction(CString _sFunctionName, VARIANT *_pvArg, UINT cArg, VARIANT *_pvResult, USHORT _lArt, LPDISPATCH pDisp)
{
	//General
//	if(!m_pSelection) return E_FAIL;
	if(pDisp == NULL) return E_FAIL;


//1.: params
	//param 1
	BSTR bstr;
    bstr = _sFunctionName.AllocSysString();
	//param 2
	DISPPARAMS dispparamsArgs;
	if(_pvArg != NULL)
		dispparamsArgs.cArgs = cArg;
	else
		dispparamsArgs.cArgs = 0;
	dispparamsArgs.cNamedArgs = 0;
	dispparamsArgs.rgvarg = _pvArg;
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	// Handle special-case for property-puts!
    if(_lArt == DISPATCH_PROPERTYPUT) 
	{
        dispparamsArgs.cNamedArgs = 1;
        dispparamsArgs.rgdispidNamedArgs = &dispidNamed;
    }

//2.: get function
	DISPID dispid;
	HRESULT m_hr = pDisp->GetIDsOfNames (IID_NULL, &bstr, 1, 
                              LOCALE_USER_DEFAULT, &dispid);

	if(!SUCCEEDED(m_hr))
	{
		//if(GetCFG(_T("debug")) == _T("1"))
			AfxMessageBox("OleCallFunction error: function not found! "+CString(bstr));
		return m_hr;
	}
//3.: call function
	EXCEPINFO _ei;
	UINT	  _epar = 0;
	m_hr = pDisp->Invoke (dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT,
                       _lArt, &dispparamsArgs, _pvResult, &_ei, 
                       &_epar);
	if(!SUCCEEDED(m_hr))
	{
		CIPString _sErr;
		if(m_hr == DISP_E_BADPARAMCOUNT)
			_sErr = _T("DISP_E_BADPARAMCOUNT");
		else if(m_hr == DISP_E_BADVARTYPE)
			_sErr = _T("DISP_E_BADVARTYPE");
		else if(m_hr == DISP_E_EXCEPTION)
			_sErr = _T("DISP_E_EXCEPTION");
		else if(m_hr == DISP_E_MEMBERNOTFOUND)
			_sErr = _T("DISP_E_MEMBERNOTFOUND");
		else if(m_hr == DISP_E_NONAMEDARGS)
			_sErr = _T("DISP_E_NONAMEDARGS");
		else if(m_hr == DISP_E_OVERFLOW)
			_sErr = _T("DISP_E_OVERFLOW");
		else if(m_hr == DISP_E_PARAMNOTFOUND)
			_sErr = _T("DISP_E_PARAMNOTFOUND");
		else if(m_hr == DISP_E_TYPEMISMATCH)
			_sErr = _T("DISP_E_TYPEMISMATCH");
		else if(m_hr == DISP_E_UNKNOWNINTERFACE)
			_sErr = _T("DISP_E_UNKNOWNINTERFACE");
		else if(m_hr == DISP_E_UNKNOWNLCID)
			_sErr = _T("DISP_E_UNKNOWNLCID");
		else if(m_hr == DISP_E_PARAMNOTOPTIONAL)
			_sErr = _T("DISP_E_PARAMNOTOPTIONAL");
		else
			_sErr.FromLong((LONG)m_hr);

		CIPString _sei1; _sei1.FromBSTR(_ei.bstrSource);
		CIPString _sei2; _sei2.FromBSTR(_ei.bstrDescription);
		if(!_sei1.IsEmpty()) _sei1 += _T("\n");
		if(!_sei2.IsEmpty()) _sei2 += _T("\n");

		CIPString _separ(_T(""));
		if(_epar != 0)
		{
			_separ.FromLong((LONG)_epar);
			_separ = _T("\nFehlerhafter Parameter ") + _separ;
		}

		AfxMessageBox(_sei1 + _sei2 + "OleCallFunction error " + _sErr + ": couldn´t call function "+CString(bstr) + _separ);
		return m_hr;
	}

	return m_hr;
}

 */