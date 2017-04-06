#pragma once

#include "officeprocessor.h"

class CHTML2OfficeProcessor
{
private:
	CIPString			 m_sLastError;
	COfficeProcessor	*m_pProcessor;

private:
	BOOL IsFileExtension(CIPString &sFilePath, CIPString &sExtension);

public:
	CHTML2OfficeProcessor(void);
	~CHTML2OfficeProcessor(void);

	BOOL CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags);
	BOOL CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter);
	BOOL ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds);

	PROCESSOR_TYPE GetType();

	BOOL IsInitialized();

	void GetLastError(CIPString &sErrorMsg);
};
