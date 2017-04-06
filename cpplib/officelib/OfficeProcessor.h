#pragma once

#include "ipstring.h"
#include "Afxtempl.h"

#define TAG_ADDCONTENTAT CIPString(_T("%TEXT%"))
#define TAG_TOC CIPString(_T("%TOC%"))
#define TAG_DOCIDS CIPString(_T("%DOCIDS%"))

enum PROCESSOR_TYPE
{
	OPENOFFICE,
	MSOFFICE,
	TER,
	UNKNOWN
};

class COfficeProcessor
{
private:
	static CArray<PROCESSOR_TYPE, PROCESSOR_TYPE>	_AVAILABLE_TYPES;
	static CIPString								_OO_PATH;
	static CIPString								_EXE_PATH;
	static BOOL										_TYPES_DETERMINED;

protected:
	CIPString	m_sLastError;

protected:
	BOOL IsFileExtension(CIPString &sFilePath, CIPString &sExtension);
	BOOL CheckDirectory(CIPString &sFileName);
	BOOL CheckFile(CIPString &sFileName);

private:
	static void DetermineAvailableTypes(CIPString &sErrorMsg = CIPString(""));
	static BOOL CheckOOAvailable(CIPString &sOOPath, CIPString &sEXEPath, CIPString &sErrorMsg = CIPString(""));
	static BOOL CheckMSOAvailable(CIPString &sErrorMsg = CIPString(""));
	static BOOL IsTypeAvailable(PROCESSOR_TYPE typeOfProcessor);

public:
	COfficeProcessor(void);
	~COfficeProcessor(void);

	virtual void DestroyProcessor() = 0;

	void GetLastError(CIPString &sError);

	virtual PROCESSOR_TYPE GetType() = 0;
	virtual BOOL CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString()) = 0;
	virtual BOOL CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags) = 0;
	virtual BOOL CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString()) = 0;
	virtual BOOL PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter) = 0;
	virtual BOOL ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds) = 0;

	static COfficeProcessor* CreateInstance(PROCESSOR_TYPE typeOfProcessor, CIPString &sErrorMsg = CIPString(""));
};
