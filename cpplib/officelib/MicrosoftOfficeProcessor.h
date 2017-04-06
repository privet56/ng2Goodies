#pragma once

//#include "ipstring.h"
//#include "Afxtempl.h"

#include ".\officeprocessor.h"

class CMicrosoftOfficeProcessor : protected COfficeProcessor
{
private:
	BOOL						m_bIsInitialized;
	CComPtr<IDispatch>			m_pWordApplication;

private:
	BOOL InitializeApp();
	void TerminateApp();

	BOOL InvokeDispatchMethod(CComPtr<IDispatch> pDispatch, CIPString &sMethodName, WORD wMethodType, DISPPARAMS &dpParameter, VARIANT &vResult, EXCEPINFO &infoException);

	CComPtr<IDispatch> OpenDocument(CIPString &sFilePath);
	BOOL SaveDocumentAs(CComPtr<IDispatch> &pDocument, CIPString &sFilePathTo);
	BOOL EmbedPictures(CComPtr<IDispatch> &pDocument);
	BOOL DoEmbed(CComPtr<IDispatch> &listEmbedable);
	BOOL CloseDocument(CComPtr<IDispatch> &pDocument);
	BOOL FindeUniqueTag(CComPtr<IDispatch> &pDocument, CIPString &sTag, CComPtr<IDispatch> &_rFoundRange);
	BOOL AddTOC(CComPtr<IDispatch> &pDocument);
	BOOL ReplacePlaceholder(CComPtr<IDispatch> &pDocument, CMapStringToString &mapReplaceTags);
	CComPtr<IDispatch> AppendText(CComPtr<IDispatch> &pDocument, CIPString &sText);
	BOOL ChangeFontColorToWhite(CComPtr<IDispatch> &pSelection);
	BOOL AddDocument(CComPtr<IDispatch> &pDocument, CIPString &sFileName, BOOL bReplaceTag);
	BOOL AddDocumentIds(CComPtr<IDispatch> &pDocument, CIPString &sDocumentIds);
	BOOL ExtractDocumentIds(CComPtr<IDispatch> &pDocument, CIPString &sDocumentIds);
	BOOL Print(CIPString sPrinter);
	void ReportHRESULT(HRESULT hRes);
	void ReportEXCEPINFO(EXCEPINFO& info);

public:
	static BOOL IsInitializable();

public:
	CMicrosoftOfficeProcessor(void);
	~CMicrosoftOfficeProcessor(void);

	void DestroyProcessor();

	BOOL IsInitialized();

	PROCESSOR_TYPE GetType();

	BOOL CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags);
	BOOL CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter);
	BOOL ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds);
	BOOL AddPageBreak(CComPtr<IDispatch> &pDocument, BOOL bSetPosition2End, int iMoveBackward);
};
