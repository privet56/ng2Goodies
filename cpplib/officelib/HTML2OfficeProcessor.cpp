#include "StdAfx.h"
#include ".\html2officeprocessor.h"
#include "ipfile.h"

CHTML2OfficeProcessor::CHTML2OfficeProcessor(void)
{
	this->m_pProcessor = COfficeProcessor::CreateInstance(UNKNOWN, this->m_sLastError);
}

CHTML2OfficeProcessor::~CHTML2OfficeProcessor(void)
{
	if (this->m_pProcessor != NULL)
	{
		this->m_pProcessor->DestroyProcessor();
		delete this->m_pProcessor;
	}
}

BOOL CHTML2OfficeProcessor::IsInitialized()
{
	return (this->m_pProcessor != NULL) ? TRUE : FALSE;
}

void CHTML2OfficeProcessor::GetLastError(CIPString &sErrorMsg)
{
	sErrorMsg = this->m_sLastError;
}

BOOL CHTML2OfficeProcessor::CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (this->m_pProcessor == NULL)
	{
		this->m_sLastError = CIPString(_T("CHTML2OfficeProcessor::CreateDocument\tERR: no processor defined"));
		return FALSE;
	}

	BOOL _bResult = FALSE;

	if ( (this->IsFileExtension(sFilePathTo, CIPString(_T("pdf"))) == TRUE) && (this->m_pProcessor->GetType() != OPENOFFICE) )
	{
		COfficeProcessor *_pOOProcessor = COfficeProcessor::CreateInstance(OPENOFFICE, this->m_sLastError);

		if (_pOOProcessor != NULL)
		{
			_bResult = _pOOProcessor->CreateDocument(sFilePathFrom, sFilePathTo, mapReplaceTags);

			if (!_bResult)
				_pOOProcessor->GetLastError(this->m_sLastError);

			_pOOProcessor->DestroyProcessor();
			delete _pOOProcessor;

			return _bResult;
		}
	}
	
	_bResult = this->m_pProcessor->CreateDocument(sFilePathFrom, sFilePathTo, mapReplaceTags);

	if (!_bResult)
		this->m_pProcessor->GetLastError(this->m_sLastError);

	return _bResult;
}

BOOL CHTML2OfficeProcessor::CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (this->m_pProcessor == NULL)
	{
		this->m_sLastError = CIPString(_T("CHTML2OfficeProcessor::CreateDocument\tERR: no processor defined"));
		return FALSE;
	}

	BOOL _bResult = this->m_pProcessor->CreateNote(sFilePathtemplate, sFilePathTo, mapReplaceTags);

	if (!_bResult)
		this->m_pProcessor->GetLastError(this->m_sLastError);

	return _bResult;
}

BOOL CHTML2OfficeProcessor::CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (this->m_pProcessor == NULL)
	{
		this->m_sLastError = CIPString(_T("CHTML2OfficeProcessor::CreateDocument\tERR: no processor defined"));
		return FALSE;
	}

	BOOL _bResult = this->m_pProcessor->CreateDocumentCollection(sFilePathtemplate, listFilePathsFrom, sDocumentIds, sFilePathTo, mapReplaceTags);

	if (!_bResult)
		this->m_pProcessor->GetLastError(this->m_sLastError);

	return _bResult;
}

BOOL CHTML2OfficeProcessor::PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter)
{
	this->m_sLastError = "";

	if (this->m_pProcessor == NULL)
	{
		this->m_sLastError = CIPString(_T("CHTML2OfficeProcessor::CreateDocument\tERR: no processor defined"));
		return FALSE;
	}

	BOOL _bResult = this->m_pProcessor->PrintDocument(sFilePathFrom, mapReplaceTags, sPrinter);

	if (!_bResult)
		this->m_pProcessor->GetLastError(this->m_sLastError);

	return _bResult;
}

BOOL CHTML2OfficeProcessor::ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds)
{
	this->m_sLastError = "";

	if (this->m_pProcessor == NULL)
	{
		this->m_sLastError = CIPString(_T("CHTML2OfficeProcessor::CreateDocument\tERR: no processor defined"));
		return FALSE;
	}

	BOOL _bResult = this->m_pProcessor->ExtractDocumentCollectionData(sFilePathFrom, sDocumentIds);

	if (!_bResult)
		this->m_pProcessor->GetLastError(this->m_sLastError);

	return _bResult;
}

PROCESSOR_TYPE CHTML2OfficeProcessor::GetType()
{
	if (this->m_pProcessor == NULL)
		return UNKNOWN;

	return this->m_pProcessor->GetType();
}

BOOL CHTML2OfficeProcessor::IsFileExtension(CIPString &sFilePath, CIPString &sExtension)
{
	CIPString	_sFileExtensionToCheck = sExtension;
	CIPString	_sFileExtension;
	CIPFile		_fFile;	

	_fFile.SetFilePath(sFilePath);
	_fFile.GetExtension(_sFileExtension);
	_sFileExtension.MakeLower();
	_sFileExtensionToCheck.MakeLower();

	return (_sFileExtension == _sFileExtensionToCheck) ? TRUE : FALSE;
}