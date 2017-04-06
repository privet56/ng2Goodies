#pragma once
#include "officeprocessor.h"
#include "ter_mfc.h"
#include "hts.h"

class CTERProcessor :
	protected  COfficeProcessor
{
private:
	BOOL						m_bIsInitialized;
	CTer						m_terWnd;

private:
	BOOL InitializeTer();

	void SetTempPath(CIPString &sFilePathFrom);
	void CreateTempFileName(CIPString &sFilePathFrom, CIPString &sTempFileName);
	void DeleteTempFile(CIPString &sTempFileName);
	void DeleteTempFiles(CArray<CIPString, CIPString> &listTempFileNames);
	void PrintSleep(int nMilliSeconds);

	BOOL OpenDocument(CIPString &sFileName);
	BOOL SaveDocumentAs(CIPString &sFileName);
	BOOL CloseDocument();
	BOOL FindUniqueTag(CIPString &sTag, long *lStartPosition);
	BOOL AddTOC();
	BOOL ReplaceTag(CIPString &sReplaceWhat, CIPString &sReplaceWith, int *pReplacedCount = NULL);
	BOOL ReplacePlaceholder(CMapStringToString &mapReplaceTags);
	BOOL AppendText(CIPString &sText, long *pStartCursorPosition = NULL, long *pEndCursorPosition = NULL);
	BOOL ChangeFontColorToWhite(long iStartCursorPosition, long iEndCursorPosition);
	BOOL AddDocument(CIPString &sFileName, BOOL bReplaceTag);
	BOOL AddDocumentIds(CIPString &sDocumentIds);
	BOOL ExtractDocumentIds(CIPString &sDocumentIds);
	BOOL Print(CIPString sPrinter);

public:
	CTERProcessor(void);
	~CTERProcessor(void);
	
	void DestroyProcessor();

	PROCESSOR_TYPE GetType();

	BOOL CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags);
	BOOL CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter);
	BOOL ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds);
};
