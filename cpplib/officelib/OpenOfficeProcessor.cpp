#include "StdAfx.h"

#include ".\openofficeprocessor.h"
#include "SHIOfficeLib.h"
#include "ipfile.h"

COpenOfficeProcessor::COpenOfficeProcessor(CIPString &sOOPath, CIPString &sOOAccessorExecutable)
{
	this->m_bIsInitialized = FALSE;
	this->m_sOOPath = sOOPath;
	this->m_sOOAccessorExecutable = sOOAccessorExecutable;

	CIPString _sChannelName;
	_sChannelName.FromGUID();
	_sChannelName.Remove(_T(":"));
	_sChannelName.Remove(_T("."));
	_sChannelName.Remove(_T(" "));
	_sChannelName.Remove(_T("-"));
	_sChannelName.Remove(_T("_"));
	_sChannelName.Remove(_T(";"));
	_sChannelName.Remove(_T("{"));
	_sChannelName.Remove(_T("}"));

	this->m_pIpcCommunicator = new CIPCCommunicator(_sChannelName, OO_IPC_BUFFERSIZE);
}

COpenOfficeProcessor::~COpenOfficeProcessor()
{
	this->DestroyProcessor();
}

void COpenOfficeProcessor::DestroyProcessor()
{
	this->TerminateIPC();
	delete this->m_pIpcCommunicator;
}

PROCESSOR_TYPE COpenOfficeProcessor::GetType()
{
	return OPENOFFICE;
}

BOOL COpenOfficeProcessor::CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (!this->InitializeIPC())
		return FALSE;
	
	CIPString _sIPCCommand;

	if (!this->IsFileExtension(sFilePathFrom, CIPString(_T("html"))) && !this->IsFileExtension(sFilePathFrom, CIPString(_T("htm"))))
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::CreateDocument\tERR: input file format is not supported"));
		return FALSE;
	}

	if (this->IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
		_sIPCCommand = _T("ipc_create_rtf");
	else if (this->IsFileExtension(sFilePathTo, CIPString(_T("pdf"))))
		_sIPCCommand = _T("ipc_create_pdf");
	else
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::CreateDocument\tERR: output file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathFrom))
		return FALSE;

	if (!this->CheckDirectory(sFilePathTo))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(_sIPCCommand))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathFrom))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathTo))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendStringMap(mapReplaceTags))
		return FALSE;

	BOOL _bResult = FALSE;

	if (!this->m_pIpcCommunicator->ReceiveBOOL(&_bResult))
		return FALSE;

	return _bResult;
}

BOOL COpenOfficeProcessor::CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (!this->InitializeIPC())
		return FALSE;
	
	CIPString _sIPCCommand;

	if (!this->IsFileExtension(sFilePathtemplate, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::CreateNote\tERR: template file format is not supported"));
		return FALSE;
	}

	if (this->IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
		_sIPCCommand = _T("ipc_create_notes_rtf");
	else if (this->IsFileExtension(sFilePathTo, CIPString(_T("pdf"))))
		_sIPCCommand = _T("ipc_create_notes_pdf");
	else
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::CreateNote\tERR: output file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathtemplate))
		return FALSE;

	if (!this->CheckDirectory(sFilePathTo))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(_sIPCCommand))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathtemplate))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathTo))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendStringMap(mapReplaceTags))
		return FALSE;

	BOOL _bResult = FALSE;

	if (!this->m_pIpcCommunicator->ReceiveBOOL(&_bResult))
		return FALSE;

	return _bResult;
}

BOOL COpenOfficeProcessor::CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (!this->InitializeIPC())
		return FALSE;
	
	if (!this->IsFileExtension(sFilePathtemplate, CIPString(_T("rtf"))) || !this->IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::CreateDocumentCollection\tERR: template or output file format is not supported"));
		return FALSE;
	}

	for (int _iElement = 0; _iElement < listFilePathsFrom.GetCount(); _iElement++)
	{
		if (!this->IsFileExtension((CIPString) listFilePathsFrom.GetAt(_iElement), CIPString(_T("html"))) && !this->IsFileExtension((CIPString) listFilePathsFrom.GetAt(_iElement), CIPString(_T("htm"))))
		{
			this->m_sLastError = CIPString(_T("COpenOfficeProcessor::CreateDocumentCollection\tERR: input file format is not supported"));
			return FALSE;
		}

		if (!this->CheckFile((CIPString) listFilePathsFrom.GetAt(_iElement)))
			return FALSE;
	}

	if (!this->CheckFile(sFilePathtemplate))
		return FALSE;

	if (!this->CheckDirectory(sFilePathTo))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(CIPString(_T("ipc_create_collection"))))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathtemplate))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendStringArray(listFilePathsFrom))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sDocumentIds))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathTo))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendStringMap(mapReplaceTags))
		return FALSE;

	BOOL _bResult = FALSE;

	if (!this->m_pIpcCommunicator->ReceiveBOOL(&_bResult))
		return FALSE;

	return _bResult;
}


BOOL COpenOfficeProcessor::PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter)
{
	this->m_sLastError = "";

	if (!this->InitializeIPC())
		return FALSE;
	
	CIPString _sIPCCommand;

	if (this->IsFileExtension(sFilePathFrom, CIPString(_T("html"))) && !this->IsFileExtension(sFilePathFrom, CIPString(_T("htm"))))
		_sIPCCommand = _T("ipc_print_html");
	else if (this->IsFileExtension(sFilePathFrom, CIPString(_T("rtf"))))
		_sIPCCommand = _T("ipc_print_rtf");
	else
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::PrintDocument\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathFrom))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(_sIPCCommand))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathFrom))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sPrinter))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendStringMap(mapReplaceTags))
		return FALSE;

	BOOL _bResult = FALSE;

	if (!this->m_pIpcCommunicator->ReceiveBOOL(&_bResult))
		return FALSE;

	return _bResult;
}


BOOL COpenOfficeProcessor::ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds)
{
	this->m_sLastError = "";

	if (!this->InitializeIPC())
		return FALSE;
	
	if (!this->IsFileExtension(sFilePathFrom, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("COpenOfficeProcessor::ExtractDocumentCollectionData\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathFrom))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(CIPString(_T("ipc_get_collection"))))
		return FALSE;

	if (!this->m_pIpcCommunicator->SendString(sFilePathFrom))
		return FALSE;

	BOOL _bResult = FALSE;

	if (!this->m_pIpcCommunicator->ReceiveBOOL(&_bResult))
		return FALSE;

	if (_bResult)
	{
		if (!this->m_pIpcCommunicator->ReceiveString(sDocumentIds))
			return FALSE;
	}

	return _bResult;
}

BOOL COpenOfficeProcessor::InitializeIPC()
{
	if (this->m_bIsInitialized == TRUE)
		return TRUE;

	this->m_bIsInitialized = FALSE;

	CIPString _sChannelName;
	this->m_pIpcCommunicator->GetChannelName(_sChannelName);
	CIPString _sCmdLineParameters = CIPString(_T("-IPCCHANNEL=")) + _sChannelName;
	int _iResult = (int) ShellExecute(NULL, NULL, this->m_sOOAccessorExecutable, _sCmdLineParameters, this->m_sOOPath, SW_HIDE);

	if (_iResult <= 32)
		return FALSE;

	::__IPVSleep(100);

	this->m_bIsInitialized = this->m_pIpcCommunicator->InitiateCommunication();

	return this->m_bIsInitialized;
}

void COpenOfficeProcessor::TerminateIPC()
{
	if (this->m_bIsInitialized == TRUE)
	{
		this->m_pIpcCommunicator->SendString(CIPString(_T("ipc_end")));
	}

	this->m_bIsInitialized = FALSE;
}