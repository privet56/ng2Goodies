#pragma once


#include ".\officeprocessor.h"
#include "IPCCommunicator.h"


#define OO_IPC_BUFFERSIZE 2048

class COpenOfficeProcessor : protected COfficeProcessor
{
private:
	BOOL						m_bIsInitialized;
	CIPCCommunicator			*m_pIpcCommunicator;
	CIPString					m_sOOPath;
	CIPString					m_sOOAccessorExecutable;

private:
	BOOL InitializeIPC();
	void TerminateIPC();

public:
	COpenOfficeProcessor(CIPString &sOOPath, CIPString &sOOAccessorExecutable);
	~COpenOfficeProcessor(void);

	void DestroyProcessor();

	PROCESSOR_TYPE GetType();

	BOOL CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags);
	BOOL CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags =CMapStringToString());
	BOOL PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter);
	BOOL ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds);
};
