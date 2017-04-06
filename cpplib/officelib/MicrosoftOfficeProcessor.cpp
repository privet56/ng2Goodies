#include "StdAfx.h"
#include "microsoftofficeprocessor.h"
#include "SHIOfficeLib.h"
#include ".\microsoftofficeprocessor.h"


BOOL CMicrosoftOfficeProcessor::IsInitializable()
{
	CMicrosoftOfficeProcessor _msoTestProcessor;

	BOOL _bResult = _msoTestProcessor.InitializeApp();
	_msoTestProcessor.TerminateApp();

	return _bResult;
}

CMicrosoftOfficeProcessor::CMicrosoftOfficeProcessor(void) : m_pWordApplication(NULL)
{
	m_bIsInitialized = FALSE;
}

CMicrosoftOfficeProcessor::~CMicrosoftOfficeProcessor(void)
{
	DestroyProcessor();
}

void CMicrosoftOfficeProcessor::DestroyProcessor()
{
	TerminateApp();
}

BOOL CMicrosoftOfficeProcessor::IsInitialized()
{
	return m_bIsInitialized;
}

PROCESSOR_TYPE CMicrosoftOfficeProcessor::GetType()
{
	return MSOFFICE;
}

BOOL CMicrosoftOfficeProcessor::CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	m_sLastError = "";

	if (!InitializeApp())
		return FALSE;

	if (!IsFileExtension(sFilePathFrom, CIPString(_T("html"))) && !IsFileExtension(sFilePathFrom, CIPString(_T("htm"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CreateDocument\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CreateDocument\tERR: output file format is not supported"));
		return FALSE;
	}

	if (!CheckFile(sFilePathFrom))
		return FALSE;

	if (!CheckDirectory(sFilePathTo))
		return FALSE;
	
	CComPtr<IDispatch> _pDocument = NULL;
	_pDocument = OpenDocument(sFilePathFrom);

	if (_pDocument == NULL)
		return FALSE;
	
	if (!SaveDocumentAs(_pDocument, sFilePathTo))
	{
		CloseDocument(_pDocument);
		return FALSE;
	}
	
	CloseDocument(_pDocument);

	_pDocument = OpenDocument(sFilePathTo);

	if (_pDocument == NULL)
		return FALSE;

	EmbedPictures(_pDocument);

	ReplacePlaceholder(_pDocument, mapReplaceTags);
	AddTOC(_pDocument);

	if (!SaveDocumentAs(_pDocument, sFilePathTo))
	{
		CloseDocument(_pDocument);
		return FALSE;
	}
	
	CloseDocument(_pDocument);

	DestroyProcessor();
	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	m_sLastError = "";

	if (!InitializeApp())
	{
		return FALSE;
	}

	if (!IsFileExtension(sFilePathtemplate, CIPString(_T("rtf"))) || !IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CreateDocumentCollection\tERR: template or output file format is not supported"));
		return FALSE;
	}

	for (int _iElement = 0; _iElement < listFilePathsFrom.GetCount(); _iElement++)
	{
		if (!IsFileExtension((CIPString) listFilePathsFrom.GetAt(_iElement), CIPString(_T("html"))) && !IsFileExtension((CIPString) listFilePathsFrom.GetAt(_iElement), CIPString(_T("htm"))))
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CreateDocumentCollection\tERR: input file format is not supported"));
			return FALSE;
		}

		if (!CheckFile((CIPString) listFilePathsFrom.GetAt(_iElement)))
			return FALSE;
	}

	if (!CheckFile(sFilePathtemplate))
		return FALSE;

	if (!CheckDirectory(sFilePathTo))
		return FALSE;

	CComPtr<IDispatch> _pDocument = NULL;
	_pDocument = OpenDocument(sFilePathtemplate);

	if (_pDocument == NULL)
		return FALSE;

	for (int _iElement = 0; _iElement < listFilePathsFrom.GetCount(); _iElement++)
	{
		if (!AddDocument(_pDocument, (CIPString) listFilePathsFrom.GetAt(_iElement), (_iElement != listFilePathsFrom.GetCount() - 1) ? FALSE : TRUE))
		{
			//CloseDocument(_pDocument);
			return FALSE;
		}
		if (!SaveDocumentAs(_pDocument, sFilePathTo))
		{
			CloseDocument(_pDocument);
			return FALSE;
		}

		CloseDocument(_pDocument);

		_pDocument = OpenDocument(sFilePathTo);
		EmbedPictures(_pDocument);
	}

	ReplacePlaceholder(_pDocument, mapReplaceTags);
	AddTOC(_pDocument);

	if (!sDocumentIds.IsEmpty() && !AddDocumentIds(_pDocument, sDocumentIds))
	{
		CloseDocument(_pDocument);
		return FALSE;
	}

	if (!SaveDocumentAs(_pDocument, sFilePathTo))
	{
		CloseDocument(_pDocument);
		return FALSE;
	}

	CloseDocument(_pDocument);
	DestroyProcessor();

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	m_sLastError = "";

	if (!InitializeApp())
		return FALSE;

	if (!IsFileExtension(sFilePathtemplate, CIPString(_T("rtf"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CreateNote\tERR: template file format is not supported"));
		return FALSE;
	}

	if (!IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CreateNote\tERR: output file format is not supported"));
		return FALSE;
	}

	if (!CheckFile(sFilePathtemplate))
		return FALSE;

	if (!CheckDirectory(sFilePathTo))
		return FALSE;

	CComPtr<IDispatch> _pDocument = NULL;
	_pDocument = OpenDocument(sFilePathtemplate);

	if (_pDocument == NULL)
		return FALSE;

	ReplacePlaceholder(_pDocument, mapReplaceTags);

	if (!SaveDocumentAs(_pDocument, sFilePathTo))
	{
		CloseDocument(_pDocument);
		return FALSE;
	}
	
	CloseDocument(_pDocument);

	DestroyProcessor();
	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter)
{
	m_sLastError = "";

	if (!InitializeApp())
		return FALSE;

	if (!IsFileExtension(sFilePathFrom, CIPString(_T("html"))) 
		&& !IsFileExtension(sFilePathFrom, CIPString(_T("htm")))
		&& !IsFileExtension(sFilePathFrom, CIPString(_T("rtf"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::PrintDocument\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!CheckFile(sFilePathFrom))
		return FALSE;

	CComPtr<IDispatch> _pDocument = NULL;
	_pDocument = OpenDocument(sFilePathFrom);

	if (_pDocument == NULL)
		return FALSE;

	ReplacePlaceholder(_pDocument, mapReplaceTags);
	AddTOC(_pDocument);
	Print(sPrinter);
	
	CloseDocument(_pDocument);

	DestroyProcessor();
	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::Print(CIPString sPrinter)
{
	COleDispatchDriver oWordBasic;

	if(!sPrinter.IsEmpty())
	{
		// Get Wordbasic
		oWordBasic.CreateDispatch("Word.Basic");

		// Retrieve DISPIDs for the FilePrintSetup function and its parameters
		OLECHAR FAR* szMethod[3];
		DISPID dispid[3];
		szMethod[0]=OLESTR("FilePrintSetup");		// Method name
		szMethod[1]=OLESTR("Printer");				// Argument name
		szMethod[2]=OLESTR("DoNotSetAsSysDefault"); // Argument name

		if(!SUCCEEDED(oWordBasic.m_lpDispatch->GetIDsOfNames(IID_NULL, szMethod, 3, LOCALE_USER_DEFAULT, dispid)))
		{
			SysFreeString(szMethod[0]); SysFreeString(szMethod[1]);
			SysFreeString(szMethod[2]);
			return FALSE;
		}

		//Invoke the FilePrintSetup function using named arguments.
		VARIANT vArgs[2];

		DISPPARAMS dp;
		dp.cArgs = 2;
		dp.cNamedArgs = 2;
		dp.rgvarg = vArgs;
		dp.rgdispidNamedArgs=&(dispid[1]);  

		vArgs[1].vt = VT_I2;
		vArgs[1].iVal = 1;     //DoNotSetAsSysDefault = 1
		vArgs[0].vt = VT_BSTR;
		vArgs[0].bstrVal = sPrinter.AllocSysString();

		if(!SUCCEEDED(oWordBasic.m_lpDispatch->Invoke(dispid[0], IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, NULL, NULL, NULL)))
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::Print\tERR: can't print document: error invoking \"FilePrintSetup\" function"));
			SysFreeString(szMethod[0]); SysFreeString(szMethod[1]);
			SysFreeString(szMethod[2]);	SysFreeString(vArgs[0].bstrVal);
			return FALSE;
		}

		SysFreeString(szMethod[0]); SysFreeString(szMethod[1]);
		SysFreeString(szMethod[2]);	SysFreeString(vArgs[0].bstrVal);
		oWordBasic.ReleaseDispatch();
	}

	// Print
	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	VARIANT _vPrintArguments[1];

	_vPrintArguments[0].vt			= VT_BOOL;         
	_vPrintArguments[0].boolVal		= TRUE; //print in background

	DISPPARAMS _dpPrint;
	_dpPrint.cArgs = 1;
    _dpPrint.cNamedArgs = 0;
    _dpPrint.rgvarg = _vPrintArguments;

	if (!InvokeDispatchMethod(m_pWordApplication, CIPString(_T("PrintOut")), DISPATCH_METHOD, _dpPrint, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::Print\tERR: can't print document: error invoking \"PrintOut\" function"));
		return FALSE;
	}

	while (TRUE)
	{
		if (!InvokeDispatchMethod(m_pWordApplication, CIPString(_T("BackgroundPrintingStatus")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::Print\tERR: can't print document: error invoking \"BackgroundPrintingStatus\" function"));
			return FALSE;
		}

		if (_vFunctionResult.lVal <= 0)
			break;

		::__IPVSleep(10);
	}

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds)
{
	m_sLastError = "";

	if (!InitializeApp())
		return FALSE;

	if (!IsFileExtension(sFilePathFrom, CIPString(_T("rtf"))))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ExtractDocumentCollectionData\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!CheckFile(sFilePathFrom))
		return FALSE;

	CComPtr<IDispatch> _pDocument = NULL;
	_pDocument = OpenDocument(sFilePathFrom);

	if (_pDocument == NULL)
		return FALSE;

	ExtractDocumentIds(_pDocument, sDocumentIds);

	CloseDocument(_pDocument);
	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::ExtractDocumentIds(CComPtr<IDispatch> &pDocument, CIPString &sDocumentIds)
{
	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	CComPtr<IDispatch> _pFoundRange = NULL;
	FindeUniqueTag(pDocument, TAG_DOCIDS, _pFoundRange);

	if (_pFoundRange == NULL)
		return FALSE;

	// prepare parameter for collapsing found range //
	VARIANT _vCollapseArguments[1];

	_vCollapseArguments[0].vt		= VT_I4;         
	_vCollapseArguments[0].lVal		= 0;		//wdCollapseEnd = 0, wdCollapseStart = 1

	DISPPARAMS _dpCollapse;
	_dpCollapse.cArgs = 1;
    _dpCollapse.cNamedArgs = 0;
    _dpCollapse.rgvarg = _vCollapseArguments;
	//--------------------------------------------//

	// collapse found range //
	if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("Collapse")), DISPATCH_METHOD, _dpCollapse, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ExtractDocumentIds\tERR: can't collapse found range: error invoking \"Collapse\" function"));
		return FALSE;
	}
	//----------------------//

	// prepare parameter for moving range to end of document//
	VARIANT _vMoveArguments[1];

	_vMoveArguments[0].vt		= VT_I4;         
	_vMoveArguments[0].lVal		= 6;		//wdStory = 6

	DISPPARAMS _dpMove;
	_dpMove.cArgs = 1;
    _dpMove.cNamedArgs = 0;
    _dpMove.rgvarg = _vMoveArguments;
	//------------------------------------------------------//

	// move range //
	if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("MoveEnd")), DISPATCH_METHOD, _dpMove, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ExtractDocumentIds\tERR: can't move range to end of document: error invoking \"MoveEnd\" function"));
		return FALSE;
	}
	//------------//

	// retrieve text from range //
	if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("Text")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ExtractDocumentIds\tERR: can't get text from range: error invoking \"Text\" function"));
		return FALSE;
	}
	
	CIPString _sText;

	if (_vFunctionResult.vt != VT_EMPTY)
		_sText = CIPString(_vFunctionResult.bstrVal);
	//--------------------------//

	int _iSeparatorPosition = _sText.Find('|', 1);
	if (_iSeparatorPosition == -1)
		return FALSE;

	sDocumentIds = _sText.Mid(1, _iSeparatorPosition - 1);

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::AddDocumentIds(CComPtr<IDispatch> &pDocument, CIPString &sDocumentIds)
{
	CIPString _sDocumentIds(TAG_DOCIDS + _T("|"));
	_sDocumentIds = _sDocumentIds + sDocumentIds + _T("|");

	CComPtr<IDispatch> _pSelection = NULL;
	_pSelection = AppendText(pDocument, _sDocumentIds);

	if (_pSelection == NULL)
		return FALSE;

	return ChangeFontColorToWhite(_pSelection);
}

BOOL CMicrosoftOfficeProcessor::AddDocument(CComPtr<IDispatch> &pDocument, CIPString &sFileName, BOOL bReplaceTag)
{
	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;
	memset(&_infoException, 0, sizeof _infoException);

	BOOL _bAppendDocument = FALSE;
	CComPtr<IDispatch> _pFoundRange = NULL;
	FindeUniqueTag(pDocument, TAG_ADDCONTENTAT, _pFoundRange);
	BOOL bPlaceHolderFound = (_pFoundRange != NULL);

	if (_pFoundRange == NULL)
	{
		// Retrieve Range-Element for whole Content of the Document //
		if (!InvokeDispatchMethod(pDocument, CIPString(_T("Content")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddDocument\tERR: can't retrieve document content: error invoking \"Content\" function"));
			return FALSE;
		}

		_bAppendDocument = TRUE;
		_pFoundRange = _vFunctionResult.pdispVal;
		
		if (_pFoundRange == NULL)
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddDocument\tERR: error retrieving document content"));
			return FALSE;
		}
		//----------------------------------------------------------//
	}

	// prepare parameters for adding file //

	VARIANT _vCollapseArguments[1];

	_vCollapseArguments[0].vt		= VT_I4;         
	_vCollapseArguments[0].lVal		= (_bAppendDocument) ? 0 : 1;	//wdCollapseEnd = 0, wdCollapseStart = 1

	DISPPARAMS _dpCollapse;
	_dpCollapse.cArgs = 1;
    _dpCollapse.cNamedArgs = 0;
    _dpCollapse.rgvarg = _vCollapseArguments;

	BSTR _bstrFileName = sFileName.AllocSysString();;

	VARIANT _vAddArguments[1];

	_vAddArguments[0].vt		= VT_BSTR;         
	_vAddArguments[0].bstrVal	= _bstrFileName;	//FileName

	DISPPARAMS _dpAdd;
	_dpAdd.cArgs = 1;
    _dpAdd.cNamedArgs = 0;
    _dpAdd.rgvarg = _vAddArguments;
	//------------------------------------//

	// add file //
	//collapse to beginn of found range for not to replace TAG_ADDCONTENTAT
	if (_bAppendDocument == TRUE || bReplaceTag == FALSE)
	{
		if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("Collapse")), DISPATCH_METHOD, _dpCollapse, _vFunctionResult, _infoException))
		{
			SysFreeString(_bstrFileName);
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddDocument\tERR: can't process \"Collapse\" function"));
			return FALSE;
		}
	}
	else
	{
		//this->AddPageBreak(pDocument, FALSE);
	}

	if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("InsertFile")), DISPATCH_METHOD, _dpAdd, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrFileName);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddDocument\tERR: can't add new document: error invoking \"InsertFile\" function"));
		return FALSE;
	}

	if(!bReplaceTag)
	{
		this->AddPageBreak(pDocument, TRUE, (bPlaceHolderFound ? CIPString(TAG_ADDCONTENTAT).GetLength(): 0));
	}

	SysFreeString(_bstrFileName);
	//----------//

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::ChangeFontColorToWhite(CComPtr<IDispatch> &pSelection)
{
	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	// retrieve font element of selection //
	if (!InvokeDispatchMethod(pSelection, CIPString(_T("Font")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ChangeFontColorToWhite\tERR: can't retrieve selections font: error invoking \"Font\" function"));
		return FALSE;
	}

	CComPtr<IDispatch> _pFont = NULL;
	_pFont = _vFunctionResult.pdispVal;

	if (_pFont == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ChangeFontColorToWhite\tERR: error retrieving selections font"));
		return FALSE;
	}
	//------------------------------------// 

	// prepare parameter for font color changing //
	VARIANT _vColorChangeArguments[1];

	_vColorChangeArguments[0].vt		= VT_I4;         
	_vColorChangeArguments[0].lVal		= 16777215;		//wdColorWhite = FFFFFF = (16777215)

	DISPPARAMS _dpColorChange;
	_dpColorChange.cArgs = 1;
    _dpColorChange.cNamedArgs = 0;
    _dpColorChange.rgvarg = _vColorChangeArguments;
	//-------------------------------------------//

	// put color property //
	if (!InvokeDispatchMethod(_pFont, CIPString(_T("Color")), DISPATCH_PROPERTYPUT, _dpColorChange, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ChangeFontColorToWhite\tERR: can't change font color: error invoking \"Color\" function"));
		return FALSE;
	}
	//--------------------//

	return TRUE;
}

CComPtr<IDispatch> CMicrosoftOfficeProcessor::AppendText(CComPtr<IDispatch> &pDocument, CIPString &sText)
{
	//if (sText.IsEmpty())
	//	return NULL;

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	// Retrieve Range-Element for whole Content of the Document and select it //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("Content")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't retrieve document content: error invoking \"Content\" function"));
		return NULL;
	}

	CComPtr<IDispatch> _pDocumentContentRange = NULL;
	_pDocumentContentRange = _vFunctionResult.pdispVal;

	if (_pDocumentContentRange == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: error retrieving document content"));
		return NULL;
	}

	if (!InvokeDispatchMethod(_pDocumentContentRange, CIPString(_T("Select")), DISPATCH_METHOD, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't retrieve document content: error invoking \"Select\" function"));
		return NULL;
	}
	//----------------------------------------------------------//

	// retrieve selection object (whole document is now selected) //
	if (!InvokeDispatchMethod(m_pWordApplication, CIPString(_T("Selection")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't retrieve selection: error invoking \"Selection\" function"));
		return NULL;
	}

	CComPtr<IDispatch> _pSelection = NULL;
	_pSelection = _vFunctionResult.pdispVal;

	if (_pSelection == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: error retrieving selection"));
		return NULL;
	}
	//---------------------------//
	
	// prepare parameter for adding text //
	VARIANT _vCollapseArguments[1];

	_vCollapseArguments[0].vt		= VT_I4;         
	_vCollapseArguments[0].lVal		= 0;	//wdCollapseEnd

	DISPPARAMS _dpCollapse;
	_dpCollapse.cArgs = 1;
    _dpCollapse.cNamedArgs = 0;
    _dpCollapse.rgvarg = _vCollapseArguments;

	BSTR _bstrText = sText.AllocSysString();

	VARIANT _vTextArguments[1];

	_vTextArguments[0].vt		= VT_BSTR;         
	_vTextArguments[0].bstrVal	= _bstrText;	//Text

	DISPPARAMS _dpText;
	_dpText.cArgs = 1;
    _dpText.cNamedArgs = 0;
    _dpText.rgvarg = _vTextArguments;
	//-----------------------------------//

	// insert paragraph and text //
	//collapse to end of document (selection)
	if (!InvokeDispatchMethod(_pSelection, CIPString(_T("Collapse")), DISPATCH_METHOD, _dpCollapse, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrText);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't process \"Collapse\" function"));
		return NULL;
	}

	if (!InvokeDispatchMethod(_pSelection, CIPString(_T("InsertParagraphAfter")), DISPATCH_METHOD, _dpNoArgs, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrText);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't process \"InsertParagraphAfter\" function"));
		return NULL;
	}

	//collapse to end of document (selection)
	if (!InvokeDispatchMethod(_pSelection, CIPString(_T("Collapse")), DISPATCH_METHOD, _dpCollapse, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrText);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't process \"Collapse\" function"));
		return NULL;
	}

	if (!InvokeDispatchMethod(_pSelection, CIPString(_T("InsertAfter")), DISPATCH_METHOD, _dpText, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrText);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AppendText\tERR: can't process \"TypeText\" function"));
		return NULL;
	}

	SysFreeString(_bstrText);
	//-------------//

	//selection is now appended text
	return _pSelection;
}

BOOL CMicrosoftOfficeProcessor::ReplacePlaceholder(CComPtr<IDispatch> &pDocument, CMapStringToString &mapReplaceTags)
{
	mapReplaceTags.SetAt("PAGEBREAK","^p^m");	//replacement '^p^m' means line-break+page-break

	if (mapReplaceTags.GetCount() == 0)
		return TRUE;

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	// Retrieve Range-Element for whole Content of the Document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("Content")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ReplacePlaceholder\tERR: can't retrieve document content: error invoking \"Content\" function"));
		return FALSE;
	}

	CComPtr<IDispatch> _pDocumentContentRange = NULL;
	_pDocumentContentRange = _vFunctionResult.pdispVal;

	if (_pDocumentContentRange == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ReplacePlaceholder\tERR: error retrieving document content"));
		return FALSE;
	}
	//----------------------------------------------------------//

	// Retrieve Find-Element for Document Range //
	if (!InvokeDispatchMethod(_pDocumentContentRange, CIPString(_T("Find")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ReplacePlaceholder\tERR: can't retrieve find element: error invoking \"Find\" function"));
		return FALSE;
	}

	CComPtr<IDispatch> _pRangeFind = NULL;
	_pRangeFind = _vFunctionResult.pdispVal;

	if (_pRangeFind == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ReplacePlaceholder\tERR: error retrieving find element"));
		return FALSE;
	}
	//------------------------------------------//

	// prepare parameters for executing Find //
	VARIANT _vNoParam;
	_vNoParam.vt = VT_ERROR;
	_vNoParam.scode = DISP_E_PARAMNOTFOUND;

	BSTR _bstrTagFind;
	BSTR _bstrTagReplaceWith;

	VARIANT _vFindArguments[11];

	_vFindArguments[10].vt		= VT_BSTR;         
	//_vFindArguments[10].bstrVal	= to be filled in loop;	//Find Text

    _vFindArguments[9].vt		= VT_BOOL;            
    _vFindArguments[9].boolVal	= FALSE;		//Match Case

	_vFindArguments[8].vt		= VT_BOOL;            
    _vFindArguments[8].boolVal	= TRUE;			//Match Whole Word

	_vFindArguments[7].vt		= VT_BOOL;            
    _vFindArguments[7].boolVal	= FALSE;		//Match Wildcards

	_vFindArguments[6].vt		= VT_BOOL;            
    _vFindArguments[6].boolVal	= FALSE;		//Match SoundsLike

    _vFindArguments[5].vt		= VT_BOOL;            
    _vFindArguments[5].boolVal	= FALSE;		//Match All Word Forms

	_vFindArguments[4].vt		= VT_BOOL;            
    _vFindArguments[4].boolVal	= TRUE;			//Forward

	_vFindArguments[3]			= _vNoParam;	//Wrap
	_vFindArguments[2]			= _vNoParam;	//Format

	_vFindArguments[1].vt		= VT_BSTR;         
	//_vFindArguments[1].bstrVal	= to be filled in loop;	//ReplaceWith

	_vFindArguments[0].vt		= VT_I4;         
	_vFindArguments[0].lVal		= 2;			//Replace (wdReplaceNone = 0, wdReplaceOne = 1, wdReplaceAll = 2)


	DISPPARAMS _dpFind;
	_dpFind.cArgs = 11;
    _dpFind.cNamedArgs = 0;
    _dpFind.rgvarg = _vFindArguments;
	//---------------------------------------//

	// execute Find-Replace //
	POSITION _elementPosition = mapReplaceTags.GetStartPosition();
	CIPString _sReplaceWhat;
	CIPString _sReplaceThrough;
	BOOL _bGetNextReplacement = TRUE;
	while (_elementPosition != NULL)
	{
		if (_bGetNextReplacement)
			mapReplaceTags.GetNextAssoc(_elementPosition, _sReplaceWhat, _sReplaceThrough);

		CComPtr<IDispatch> _pFoundTOCRange = NULL;
		FindeUniqueTag(pDocument, TAG_ADDCONTENTAT, _pFoundTOCRange);

		if (_sReplaceWhat == TAG_ADDCONTENTAT && _pFoundTOCRange == NULL)
		{
			AppendText(pDocument, _sReplaceThrough);
			_bGetNextReplacement = TRUE;
			continue;
		}

		CIPString _sReplaceThroughTemp;
		if (_sReplaceThrough.GetLength() > 50)
		{
			_sReplaceThroughTemp = _sReplaceThrough.Left(50 - _sReplaceWhat.GetLength());
			_sReplaceThrough = _sReplaceThrough.Right(_sReplaceThrough.GetLength() - _sReplaceThroughTemp.GetLength());
			_sReplaceThroughTemp = _sReplaceThroughTemp + _sReplaceWhat;

			_bGetNextReplacement = FALSE;
		}
		else
		{
			_bGetNextReplacement = TRUE;
			_sReplaceThroughTemp = _sReplaceThrough;
		}

		_bstrTagFind = _sReplaceWhat.AllocSysString();
		_bstrTagReplaceWith = _sReplaceThroughTemp.AllocSysString();
  
		_vFindArguments[10].bstrVal	= _bstrTagFind;			//Find Text
		_vFindArguments[1].bstrVal	= _bstrTagReplaceWith;	//ReplaceWith

		
		if (!InvokeDispatchMethod(_pRangeFind, CIPString(_T("ClearFormatting")), DISPATCH_METHOD, _dpNoArgs, _vFunctionResult, _infoException))
		{
			SysFreeString(_bstrTagFind);
			SysFreeString(_bstrTagReplaceWith);
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ReplacePlaceholder\tERR: can't execute find-replace: error invoking \"ClearFormatting\" function"));
			return FALSE;
		}

		if (!InvokeDispatchMethod(_pRangeFind, CIPString(_T("Execute")), DISPATCH_METHOD, _dpFind, _vFunctionResult, _infoException))
		{
			SysFreeString(_bstrTagFind);
			SysFreeString(_bstrTagReplaceWith);
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::ReplacePlaceholder\tERR: can't execute find-replace: error invoking \"Execute\" function"));
			return FALSE;
		}

		SysFreeString(_bstrTagFind);
		SysFreeString(_bstrTagReplaceWith);
	}
	//--------------//

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::AddTOC(CComPtr<IDispatch> &pDocument)
{
	CComPtr<IDispatch> _pFoundTOCRange = NULL;
	FindeUniqueTag(pDocument, TAG_TOC, _pFoundTOCRange);

	if (_pFoundTOCRange == NULL)
		return TRUE;

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	// retrive TOCs from document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("TablesOfContents")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddTOC\tERR: can't retrieve document TOCs: error invoking \"TablesOfContents\" function"));
		return FALSE;
	}

	CComPtr<IDispatch> _pTablesOfContents = NULL;
	_pTablesOfContents = _vFunctionResult.pdispVal;

	if (_pTablesOfContents == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddTOC\tERR: can't retrieve document TOCs: found TOCs is NULL"));
		return FALSE;
	}
	//----------------------------//

	// prepare parameters for adding TOC //
	VARIANT _vNoParam;
	_vNoParam.vt = VT_ERROR;
	_vNoParam.scode = DISP_E_PARAMNOTFOUND;

	VARIANT _vAddArguments[11];

	_vAddArguments[10].vt		= VT_DISPATCH;         
	_vAddArguments[10].pdispVal	= _pFoundTOCRange;	//Range

    _vAddArguments[9].vt		= VT_BOOL;            
    _vAddArguments[9].boolVal	= TRUE;				//UseHeadingStyles

	_vAddArguments[8]			= _vNoParam;		//UpperHeadingLevel
	_vAddArguments[7]			= _vNoParam;		//LowerHeadingLevel
	_vAddArguments[6]			= _vNoParam;		//UseFields
	_vAddArguments[5]			= _vNoParam;		//TableID
	_vAddArguments[4]			= _vNoParam;		//RightAlignPageNumbers

	_vAddArguments[3].vt		= VT_BOOL;            
    _vAddArguments[3].boolVal	= FALSE;			//IncludePageNumbers
	
	_vAddArguments[2]			= _vNoParam;		//AddedStyles
	_vAddArguments[1]			= _vNoParam;		//UseHyperlinks
	_vAddArguments[0]			= _vNoParam;		//HidePageNumbersInWeb


	DISPPARAMS _dpAdd;
	_dpAdd.cArgs = 11;
    _dpAdd.cNamedArgs = 0;
    _dpAdd.rgvarg = _vAddArguments;
	//-----------------------------------//

	// add TOC //
	if (!InvokeDispatchMethod(_pTablesOfContents, CIPString(_T("Add")), DISPATCH_METHOD, _dpAdd, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddTOC\tERR: can't add TOC: error invoking \"Add\" function"));
		return FALSE;
	}
	//---------//

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::FindeUniqueTag(CComPtr<IDispatch> &pDocument, CIPString &sTag, CComPtr<IDispatch> &pFoundRange)
{
	pFoundRange = NULL;

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	// Retrieve Range-Element for whole Content of the Document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("Content")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: can't retrieve document content: error invoking \"Content\" function"));
		return FALSE;
	}

	CComPtr<IDispatch> _pDocumentContentRange = NULL;
	_pDocumentContentRange = _vFunctionResult.pdispVal;

	if (_pDocumentContentRange == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: error retrieving document content"));
		return FALSE;
	}
	//----------------------------------------------------------//

	// Retrieve Find-Element for Document Range //
	if (!InvokeDispatchMethod(_pDocumentContentRange, CIPString(_T("Find")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: can't retrieve find element: error invoking \"Find\" function"));
		return FALSE;
	}

	CComPtr<IDispatch> _pRangeFind = NULL;
	_pRangeFind = _vFunctionResult.pdispVal;

	if (_pRangeFind == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: error retrieving find element"));
		return FALSE;
	}
	//------------------------------------------//

	// prepare parameters for executing Find //
	BSTR _bstrTag = sTag.AllocSysString();

	VARIANT _vFindArguments[7];

	_vFindArguments[6].vt		= VT_BSTR;         
    _vFindArguments[6].bstrVal	= _bstrTag;		//Find Text

    _vFindArguments[5].vt		= VT_BOOL;            
    _vFindArguments[5].boolVal	= FALSE;		//Match Case

	_vFindArguments[4].vt		= VT_BOOL;            
    _vFindArguments[4].boolVal	= TRUE;			//Match Whole Word

	_vFindArguments[3].vt		= VT_BOOL;            
    _vFindArguments[3].boolVal	= FALSE;		//Match Wildcards

	_vFindArguments[2].vt		= VT_BOOL;            
    _vFindArguments[2].boolVal	= FALSE;		//Match SoundsLike

    _vFindArguments[1].vt		= VT_BOOL;            
    _vFindArguments[1].boolVal	= FALSE;		//Match All Word Forms

	_vFindArguments[0].vt		= VT_BOOL;            
    _vFindArguments[0].boolVal	= TRUE;			//Forward


	DISPPARAMS _dpFind;
	_dpFind.cArgs = 7;
    _dpFind.cNamedArgs = 0;
    _dpFind.rgvarg = _vFindArguments;
	//---------------------------------------//

	// execute Find //
	if (!InvokeDispatchMethod(_pRangeFind, CIPString(_T("Execute")), DISPATCH_METHOD, _dpFind, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrTag);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: can't execute find: error invoking \"Execute\" function"));
		return FALSE;
	}
	
	SysFreeString(_bstrTag);

	if (_vFunctionResult.vt != VT_BOOL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::FindeUniqueTag\tERR: find execution failed (received incorrect result)"));
		return FALSE;
	}

	if (_vFunctionResult.boolVal == FALSE)
	{
		return TRUE;
	}
	//--------------//

	pFoundRange = _pDocumentContentRange;
	return TRUE;
}

CComPtr<IDispatch> CMicrosoftOfficeProcessor::OpenDocument(CIPString &sFilePath)
{
	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	// Retrieve Documents //
	if(!InvokeDispatchMethod(m_pWordApplication, CIPString(_T("Documents")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::OpenDocument\tERR: can't retrieve document collection: error invoking \"Documents\" function"));
		return NULL;
	}

	CComPtr<IDispatch> _pDocuments = NULL;
	_pDocuments = _vFunctionResult.pdispVal;
	//---------------------//

	// Open Documents //
	BSTR _bstrFilePath = sFilePath.AllocSysString();
	VARIANT _vOpenArguments[2];
	_vOpenArguments[1].vt = VT_BSTR;         
	_vOpenArguments[1].bstrVal = _bstrFilePath;

	_vOpenArguments[0].vt = VT_BOOL;         
	_vOpenArguments[0].bstrVal = FALSE;

	DISPPARAMS _dpOpen;
	_dpOpen.cArgs = 2;
	_dpOpen.cNamedArgs = 0;
	_dpOpen.rgvarg = _vOpenArguments;
	

	if(!InvokeDispatchMethod(_pDocuments, CIPString(_T("Open")), DISPATCH_METHOD, _dpOpen, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrFilePath);
		CIPString _err(_infoException.bstrDescription);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::OpenDocument\tERR: can't open document: error invoking \"Open\" function " + _err));
		return NULL;
	}

	SysFreeString(_bstrFilePath);
	//----------------//

	CComPtr<IDispatch> _pDocument = _vFunctionResult.pdispVal;
	
	return _pDocument;
}


BOOL CMicrosoftOfficeProcessor::DoEmbed(CComPtr<IDispatch> &listEmbedable)
{
	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	long _lElementCount = 0;

	if (!InvokeDispatchMethod(listEmbedable, CIPString(_T("Count")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::DoEmbed\tERR: can't retrieve count of embedable elements: error invoking \"Count\" function"));
		return FALSE;
	}

	_lElementCount = _vFunctionResult.lVal;

	if (_lElementCount == 0)
		return TRUE;

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

		//------------//
	}

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::EmbedPictures(CComPtr<IDispatch> &pDocument)
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
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::EmbedPictures\tERR: can't retrieve document fields: error invoking \"Fields\" function"));
		return FALSE;
	}

	_pEmbedable = _vFunctionResult.pdispVal;

	if (_pEmbedable == NULL)
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::EmbedPictures\tERR: can't retrieve document fields: found fields is NULL"));
		return FALSE;
	}

	_bResult = DoEmbed(_pEmbedable);
	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);
	GetLastError(_sErrMsg);
	m_sLastError = _sErrMsg;
	//----------------------------//
	
	// embed all Shapes from document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("Shapes")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError += CIPString(_T("CMicrosoftOfficeProcessor::EmbedPictures\tERR: can't retrieve document shapes: error invoking \"Shapes\" function"));
		return FALSE;
	}

	_pEmbedable = NULL;
	_pEmbedable = _vFunctionResult.pdispVal;

	if (_pEmbedable == NULL)
	{
		m_sLastError += CIPString(_T("CMicrosoftOfficeProcessor::EmbedPictures\tERR: can't retrieve document shapes: found shapes is NULL"));
		return FALSE;
	}

	_bResult = DoEmbed(_pEmbedable);
	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);
	GetLastError(_sErrMsg);
	m_sLastError += _sErrMsg;
	//----------------------------//

	// embed all Inline Shapes from document //
	if (!InvokeDispatchMethod(pDocument, CIPString(_T("InlineShapes")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError += CIPString(_T("CMicrosoftOfficeProcessor::EmbedPictures\tERR: can't retrieve document inline shapes: error invoking \"InlineShapes\" function"));
		return FALSE;
	}

	_pEmbedable = NULL;
	_pEmbedable = _vFunctionResult.pdispVal;

	if (_pEmbedable == NULL)
	{
		m_sLastError += CIPString(_T("CMicrosoftOfficeProcessor::EmbedPictures\tERR: can't retrieve document inline shapes: found shapes is NULL"));
		return FALSE;
	}

	_bResult = DoEmbed(_pEmbedable);
	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);
	GetLastError(_sErrMsg);
	m_sLastError += _sErrMsg;
	//----------------------------//

	return _bResult;
}

BOOL CMicrosoftOfficeProcessor::SaveDocumentAs(CComPtr<IDispatch> &pDocument, CIPString &sFilePathTo)
{
	SetFileAttributes((LPCTSTR) (sFilePathTo), FILE_ATTRIBUTE_NORMAL);

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	InvokeDispatchMethod(pDocument, CIPString(_T("UndoClear")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException);

	BSTR _bstrFilePathTo = sFilePathTo.AllocSysString();
	BSTR _bstrEmptyString = SysAllocString(OLESTR(""));

	VARIANT _vFalse;
    _vFalse.vt = VT_BOOL;
    _vFalse.boolVal = FALSE;

    VARIANT _vSaveAsArguments[11];

	_vSaveAsArguments[10].vt		= VT_BSTR;         
    _vSaveAsArguments[10].bstrVal	= _bstrFilePathTo;	//Filename

    _vSaveAsArguments[9].vt			= VT_I4;            
    _vSaveAsArguments[9].lVal		= 6;				//FileFormat (6 = rtf)

    _vSaveAsArguments[8]			= _vFalse;			//LockComments

    _vSaveAsArguments[7].vt			= VT_BSTR;
    _vSaveAsArguments[7].bstrVal	= _bstrEmptyString;	//Password

    _vSaveAsArguments[6].vt			= VT_BOOL;      
    _vSaveAsArguments[6].boolVal	= TRUE;             //AddToRecentFiles

    _vSaveAsArguments[5].vt			= VT_BSTR;
    _vSaveAsArguments[5].bstrVal	= _bstrEmptyString;	//WritePassword

    _vSaveAsArguments[4]			= _vFalse;			//ReadOnlyRecommended

    _vSaveAsArguments[3]			= _vFalse;          //EmbedTrueTypeFonts

    _vSaveAsArguments[2].vt			= VT_BOOL;          
	_vSaveAsArguments[2].boolVal	= FALSE;			//SaveNativePictureFormat

    _vSaveAsArguments[1]			= _vFalse;          //SaveFormsData

    _vSaveAsArguments[0]			= _vFalse;          //SaveAsOCELetter

	DISPPARAMS _dpSaveAs;
	_dpSaveAs.cArgs = 11;
    _dpSaveAs.cNamedArgs = 0;
    _dpSaveAs.rgvarg = _vSaveAsArguments;
	

	if(!InvokeDispatchMethod(pDocument, CIPString(_T("SaveAs")), DISPATCH_METHOD, _dpSaveAs, _vFunctionResult, _infoException))
	{
		SysFreeString(_bstrFilePathTo);
		SysFreeString(_bstrEmptyString);
		CIPString _sErr(_infoException.bstrDescription);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::SaveDocumentAs\tERR: can't save document: error invoking \"SaveAs\" function " + _sErr));
		return FALSE;
	}

    SysFreeString(_bstrFilePathTo);
	SysFreeString(_bstrEmptyString);

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::CloseDocument(CComPtr<IDispatch> &pDocument)
{
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	VARIANT _vCloseArguments[1];
	_vCloseArguments[0].vt		= VT_BOOL;
	_vCloseArguments[0].lVal	= 0;	

	DISPPARAMS _dpClose;
	_dpClose.cArgs = 1;
    _dpClose.cNamedArgs = 0;
    _dpClose.rgvarg = _vCloseArguments;

	if(!InvokeDispatchMethod(pDocument, CIPString(_T("Close")), DISPATCH_METHOD, _dpClose, _vFunctionResult, _infoException))
	{
		CIPString _sErr(_infoException.bstrDescription);
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::CloseDocument\tERR: can't close document: error invoking \"Close\" function " + _sErr));
		return FALSE;
	}

	return TRUE;
}

BOOL CMicrosoftOfficeProcessor::InitializeApp()
{
	if (m_bIsInitialized == TRUE)
		return TRUE;

	m_bIsInitialized = FALSE;
	m_pWordApplication = NULL;

	CoInitialize(NULL);

	CLSID _clsidWordApp;

	if (!SUCCEEDED(CLSIDFromProgID(L"Word.Application", &_clsidWordApp)))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::InitializeApp\tERR: can't retrieve class id for Word.Application"));
		return FALSE;
	}

	if (!SUCCEEDED(CoCreateInstance(_clsidWordApp, NULL, CLSCTX_SERVER, IID_IDispatch, (void**) &m_pWordApplication)))
	{
		m_pWordApplication = NULL;
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::InitializeApp\tERR: can't instantiate Word.Application"));
		return FALSE;
	}

	m_bIsInitialized = TRUE;

	return TRUE;
}

void CMicrosoftOfficeProcessor::TerminateApp()
{
	if (m_bIsInitialized == FALSE || m_pWordApplication == NULL)
		return;

	m_bIsInitialized = FALSE;

	DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};
	VARIANT _vFunctionResult;
	EXCEPINFO _infoException;

	if(!InvokeDispatchMethod(m_pWordApplication, CIPString(_T("Quit")), DISPATCH_METHOD, _dpNoArgs, _vFunctionResult, _infoException))
	{
		m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::TerminateApp\tERR: can't terminate Application: error invoking \"Quit\" function"));
	}

	m_pWordApplication = NULL;

    CoUninitialize();
}

BOOL CMicrosoftOfficeProcessor::InvokeDispatchMethod(CComPtr<IDispatch> pDispatch, CIPString &sMethodName, WORD wMethodType, DISPPARAMS &dpParameter, VARIANT &vResult, EXCEPINFO &infoException)
{
	OLECHAR FAR* _sOleFunction = sMethodName.AllocSysString();
	DISPID _dispidFunction;

	if (!SUCCEEDED(pDispatch->GetIDsOfNames(IID_NULL, &_sOleFunction, 1, LOCALE_USER_DEFAULT, &_dispidFunction)))
	{
		SysFreeString(_sOleFunction);
		return FALSE;
	}

	HRESULT hRes = pDispatch->Invoke(_dispidFunction, IID_NULL, LOCALE_USER_DEFAULT, wMethodType, &dpParameter, &vResult, &infoException, NULL);
	if (!SUCCEEDED(hRes))
	{
		//ReportHRESULT(hRes);
		//ReportEXCEPINFO(infoException);
		SysFreeString(_sOleFunction);
		return FALSE;
	}

	SysFreeString(_sOleFunction);

	return TRUE;
}

void CMicrosoftOfficeProcessor::ReportHRESULT(HRESULT hRes)
{
	switch(hRes)
	{
		case S_OK: AfxMessageBox(_T("Success.")); break;
		case DISP_E_BADPARAMCOUNT: AfxMessageBox(_T("The number of elements provided to DISPPARAMS is different from the number of arguments accepted by the method or property.")); break;
		case DISP_E_BADVARTYPE: AfxMessageBox(_T("One of the arguments in rgvarg is not a valid variant type.")); break;
		case DISP_E_EXCEPTION: AfxMessageBox(_T("The application needs to raise an exception. In this case, the structure passed in pExcepInfo should be filled in.")); break;
		case DISP_E_MEMBERNOTFOUND: AfxMessageBox(_T("The requested member does not exist, or the call to Invoke tried to set the value of a read-only property.")); break;
		case DISP_E_NONAMEDARGS: AfxMessageBox(_T("This implementation of IDispatch does not support named arguments.")); break;
		case DISP_E_OVERFLOW: AfxMessageBox(_T("One of the arguments in rgvarg could not be coerced to the specified type.")); break;
		case DISP_E_PARAMNOTFOUND: AfxMessageBox(_T("One of the parameter DISPIDs does not correspond to a parameter on the method. In this case, puArgErr should be set to the first argument that contains the error.")); break;
		case DISP_E_TYPEMISMATCH: AfxMessageBox(_T("One or more of the arguments could not be coerced. The index within rgvarg of the first parameter with the incorrect type is returned in the puArgErr parameter.")); break;
		case DISP_E_UNKNOWNINTERFACE: AfxMessageBox(_T("The interface identifier passed in riid is not IID_NULL.")); break;
		case DISP_E_UNKNOWNLCID: AfxMessageBox(_T("The member being invoked interprets string arguments according to the LCID, and the LCID is not recognized. If the LCID is not needed to interpret arguments, this error should not be returned.")); break;
		case DISP_E_PARAMNOTOPTIONAL: AfxMessageBox(_T("A required parameter was omitted.")); break;
		default: 
		{
			CIPString shRes;
			shRes.Format(_T("Unknown HRESULT:%d"), hRes);
			AfxMessageBox(shRes);
		}
	}
}

void CMicrosoftOfficeProcessor::ReportEXCEPINFO(EXCEPINFO& info)
{
	CIPString sDesc(info.bstrDescription);
	CIPString sHelp(info.bstrHelpFile);
	CIPString sSrc(info.bstrSource);
	CIPString sInf;
	sInf.Format(_T("Description:%s\nHelp:%s\nSource:%s\nException Code:%d"), sDesc, sHelp, sSrc, info.wCode);
	AfxMessageBox(sInf);
}
BOOL CMicrosoftOfficeProcessor::AddPageBreak(CComPtr<IDispatch> &pDocument, BOOL bSetPosition2End, int iMoveBackward)
{
	return TRUE;
	//as word-makro:
    //Selection.EndKey Unit:=wdStory
    //Selection.InsertBreak Type:=wdPageBreak

	CComPtr<IDispatch> _pFoundRange = NULL;
	{	//find beginning of the document
		VARIANT _vFunctionResult;
		EXCEPINFO _infoException;
		DISPPARAMS _dpNoArgs = {NULL, NULL, 0, 0};

		if (!InvokeDispatchMethod(pDocument, CIPString(_T("Content")), DISPATCH_PROPERTYGET, _dpNoArgs, _vFunctionResult, _infoException))
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddPageBreak\tERR: can't retrieve document content: error invoking \"Content\" function"));
			return FALSE;
		}
		_pFoundRange = _vFunctionResult.pdispVal;
	}
	if(bSetPosition2End)		//set position to start of the document
	{
		VARIANT _vFunctionResult;
		EXCEPINFO _infoException;
		VARIANT _vCollapseArguments[1];
		DISPPARAMS _dpCollapse;
		_vCollapseArguments[0].vt		= VT_I4;
		_vCollapseArguments[0].lVal		= 0;	//wdCollapseEnd = 0, wdCollapseStart = 1
		_dpCollapse.cArgs				= 1;
		_dpCollapse.cNamedArgs			= 0;
		_dpCollapse.rgvarg				= _vCollapseArguments;

		if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("Collapse")), DISPATCH_METHOD, _dpCollapse, _vFunctionResult, _infoException))
		{
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddPageBreak\tERR: can't process \"Collapse\" function"));
			return FALSE;
		}
	}
	if(iMoveBackward > 0)
	{
		//Selection.MoveLeft Unit:=wdCharacter, Count:=4
		long wdCharacter = 1;
		VARIANT _vArguments[2];
		DISPPARAMS _dp;

		_vArguments[0].vt		= VT_I4;
		_vArguments[0].lVal		= wdCharacter;
		_vArguments[1].vt		= VT_I4;
		_vArguments[1].lVal		= iMoveBackward;
		_dp.cArgs				= 2;
		_dp.cNamedArgs			= 0;
		_dp.rgvarg				= _vArguments;

		VARIANT _vFunctionResult;
		EXCEPINFO _infoException;

		if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("MoveLeft")), DISPATCH_METHOD, _dp, _vFunctionResult, _infoException))
		{
			CIPString _sErr(_infoException.bstrDescription);
			m_sLastError += "MicrosoftOfficeProcessor:AddPageBreak\tERR:!'MoveLeft' err:"+_sErr;
			//return FALSE;
		}
	}

	/*
	{	//insert text
		CIPString sText("HEREPAGEBREAK");
		BSTR _bstrText = sText.AllocSysString();
		VARIANT _vTextArguments[1];
		_vTextArguments[0].vt		= VT_BSTR;         
		_vTextArguments[0].bstrVal	= _bstrText;	//Text
		DISPPARAMS _dpText;
		_dpText.cArgs = 1;
		_dpText.cNamedArgs = 0;
		_dpText.rgvarg = _vTextArguments;
		if (!InvokeDispatchMethod(_pSelection, CIPString(_T("InsertAfter")), DISPATCH_METHOD, _dpText, _vFunctionResult, _infoException))
		{
			SysFreeString(_bstrText);
			m_sLastError = CIPString(_T("CMicrosoftOfficeProcessor::AddPageBreak\tERR: can't process \"TypeText\" function"));
			return NULL;
		}

		SysFreeString(_bstrText);
	}
	*/
	/*
	CComPtr<IDispatch> pSelection = AppendText(pDocument,CIPString("HEREPAGEBREAK"));
	if(!pSelection)
	{
		m_sLastError += "MicrosoftOfficeProcessor:AddPageBreak\tERR:!AppendText + !pSelection";
		return FALSE;
	}
	return TRUE;
	*/
	{	//insert page break
		long wdPageBreak = 7;
		VARIANT _vArguments[1];
		DISPPARAMS _dp;

		_vArguments[0].vt		= VT_I4;         
		_vArguments[0].lVal		= wdPageBreak;
		_dp.cArgs				= 1;
		_dp.cNamedArgs			= 0;
		_dp.rgvarg				= _vArguments;

		VARIANT _vFunctionResult;
		EXCEPINFO _infoException;

		if (!InvokeDispatchMethod(_pFoundRange, CIPString(_T("InsertBreak")), DISPATCH_METHOD, _dp, _vFunctionResult, _infoException))
		{
			CIPString _sErr(_infoException.bstrDescription);
			m_sLastError += "MicrosoftOfficeProcessor:AddPageBreak\tERR:!'InsertBreak' err:"+_sErr;
			return FALSE;
		}
	}
	return TRUE;
}
