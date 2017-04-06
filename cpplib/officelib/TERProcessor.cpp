#include "StdAfx.h"
#include ".\terprocessor.h"
#include "ipfile.h"
#include "ximage.h"
#include <io.h>
#include <direct.h>
#include "ipcommon.h"
#include <winspool.h>

CIPString						__global_PathFrom(_T(""));
CArray<CIPString, CIPString>	__global_PNGTempFileNames;

CTERProcessor::CTERProcessor(void)
{
	this->m_bIsInitialized = FALSE;
}

CTERProcessor::~CTERProcessor(void)
{
	this->DestroyProcessor();
}

void CTERProcessor::DestroyProcessor()
{
	this->m_terWnd.DestroyWindow();
	this->m_bIsInitialized = FALSE;
}

PROCESSOR_TYPE CTERProcessor::GetType()
{
	return TER;
}

BOOL CTERProcessor::CreateDocument(CIPString &sFilePathFrom, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (!this->InitializeTer())
		return FALSE;

	if (!this->IsFileExtension(sFilePathFrom, CIPString(_T("html"))) && !this->IsFileExtension(sFilePathFrom, CIPString(_T("htm"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::CreateDocument\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!this->IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::CreateDocument\tERR: output file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathFrom))
		return FALSE;

	if (!this->CheckDirectory(sFilePathTo))
		return FALSE;

	this->SetTempPath(sFilePathFrom);

	CIPString _sTempFileName;
	this->CreateTempFileName(sFilePathTo, _sTempFileName);

	if (!this->OpenDocument(sFilePathFrom))
	{
		this->DeleteTempFile(_sTempFileName);
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	if (!this->SaveDocumentAs(_sTempFileName))
	{
		this->CloseDocument();
		this->DeleteTempFile(_sTempFileName);
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	this->CloseDocument();

	if (!this->OpenDocument(_sTempFileName))
	{
		this->DeleteTempFile(_sTempFileName);
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	this->ReplacePlaceholder(mapReplaceTags);
	this->AddTOC();

	if (!this->SaveDocumentAs(sFilePathTo))
	{
		this->CloseDocument();
		this->DeleteTempFile(_sTempFileName);
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	this->CloseDocument();
	this->DeleteTempFile(_sTempFileName);
	this->DeleteTempFiles(::__global_PNGTempFileNames);

	return TRUE;
}

BOOL CTERProcessor::CreateNote(CIPString &sFilePathtemplate, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (!this->InitializeTer())
		return FALSE;

	if (!this->IsFileExtension(sFilePathtemplate, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::CreateNote\tERR: template file format is not supported"));
		return FALSE;
	}

	if (!this->IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::CreateNote\tERR: output file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathtemplate))
		return FALSE;

	if (!this->CheckDirectory(sFilePathTo))
		return FALSE;

	if (!this->OpenDocument(sFilePathtemplate))
	{
		return FALSE;
	}

	this->ReplacePlaceholder(mapReplaceTags);

	if (!this->SaveDocumentAs(sFilePathTo))
	{
		this->CloseDocument();
		return FALSE;
	}

	this->CloseDocument();
	return TRUE;
}

BOOL CTERProcessor::CreateDocumentCollection(CIPString &sFilePathtemplate, CArray<CIPString, CIPString> &listFilePathsFrom, CIPString &sDocumentIds, CIPString &sFilePathTo, CMapStringToString &mapReplaceTags)
{
	this->m_sLastError = "";

	if (!this->InitializeTer())
		return FALSE;

	if (!this->IsFileExtension(sFilePathtemplate, CIPString(_T("rtf"))) || !this->IsFileExtension(sFilePathTo, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::CreateDocumentCollection\tERR: template or output file format is not supported"));
		return FALSE;
	}

	for (int _iElement = 0; _iElement < listFilePathsFrom.GetCount(); _iElement++)
	{
		if (!this->IsFileExtension((CIPString) listFilePathsFrom.GetAt(_iElement), CIPString(_T("html"))) && !this->IsFileExtension((CIPString) listFilePathsFrom.GetAt(_iElement), CIPString(_T("htm"))))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::CreateDocumentCollection\tERR: input file format is not supported"));
			return FALSE;
		}

		if (!this->CheckFile((CIPString) listFilePathsFrom.GetAt(_iElement)))
			return FALSE;
	}

	if (!this->CheckFile(sFilePathtemplate))
		return FALSE;

	if (!this->CheckDirectory(sFilePathTo))
		return FALSE;

	CArray<CIPString, CIPString> _listTempFileNames;
	for (int _iElement = 0; _iElement < listFilePathsFrom.GetCount(); _iElement++)
	{
		CIPString _sTempFileName;
		this->CreateTempFileName(sFilePathTo, _sTempFileName);

		this->SetTempPath((CIPString) listFilePathsFrom.GetAt(_iElement));

		if (!this->OpenDocument((CIPString) listFilePathsFrom.GetAt(_iElement)))
		{
			this->DeleteTempFiles(_listTempFileNames);
			this->DeleteTempFiles(::__global_PNGTempFileNames);
			return FALSE;
		}

		if (!this->SaveDocumentAs(_sTempFileName))
		{
			this->CloseDocument();
			this->DeleteTempFiles(_listTempFileNames);
			this->DeleteTempFiles(::__global_PNGTempFileNames);
			return FALSE;
		}
		
		this->CloseDocument();
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		_listTempFileNames.Add(_sTempFileName);
	}

	if (!this->OpenDocument(sFilePathtemplate))
	{
		this->DeleteTempFiles(_listTempFileNames);
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	for (int _iElement = 0; _iElement < _listTempFileNames.GetCount(); _iElement++)
	{
		if (!this->AddDocument((CIPString) _listTempFileNames.GetAt(_iElement), (_iElement != _listTempFileNames.GetCount() - 1) ? FALSE : TRUE))
		{
			this->CloseDocument();
			this->DeleteTempFiles(_listTempFileNames);
			this->DeleteTempFiles(::__global_PNGTempFileNames);
			return FALSE;
		}
	}

	this->ReplacePlaceholder(mapReplaceTags);
	this->AddTOC();
	if(!sDocumentIds.IsEmpty())
		this->AddDocumentIds(sDocumentIds);

	if (!this->SaveDocumentAs(sFilePathTo))
	{
		this->CloseDocument();
		this->DeleteTempFiles(_listTempFileNames);
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	this->CloseDocument();
	this->DeleteTempFiles(_listTempFileNames);
	this->DeleteTempFiles(::__global_PNGTempFileNames);
	return TRUE;
}

BOOL CTERProcessor::PrintDocument(CIPString &sFilePathFrom, CMapStringToString &mapReplaceTags, CIPString sPrinter)
{
	this->m_sLastError = "";

	if (!this->InitializeTer())
		return FALSE;

	if (!this->IsFileExtension(sFilePathFrom, CIPString(_T("html"))) 
		&& !this->IsFileExtension(sFilePathFrom, CIPString(_T("htm")))
		&& !this->IsFileExtension(sFilePathFrom, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::PrintDocument\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathFrom))
		return FALSE;

	this->SetTempPath(sFilePathFrom);

	if (!this->OpenDocument(sFilePathFrom))
	{
		this->DeleteTempFiles(::__global_PNGTempFileNames);
		return FALSE;
	}

	this->ReplacePlaceholder(mapReplaceTags);
	this->AddTOC();

	BOOL _bResult = this->Print(sPrinter);

	this->CloseDocument();
	this->DeleteTempFiles(::__global_PNGTempFileNames);
	
	return _bResult;
}

BOOL CTERProcessor::Print(CIPString sPrinter)
{
	if(!sPrinter.IsEmpty())
	{
		// Open printer
		HANDLE hPrinter;
		if (OpenPrinter((LPTSTR)(LPCTSTR)sPrinter, &hPrinter, NULL) == FALSE)
			return FALSE;

		// Obtain PRINTER_INFO_2 structure and close printer
		DWORD dwBytesReturned, dwBytesNeeded;
		GetPrinter(hPrinter, 2, NULL, 0, &dwBytesNeeded);
		PRINTER_INFO_2* p2 = (PRINTER_INFO_2*)GlobalAlloc(GPTR, dwBytesNeeded);
		if(GetPrinter(hPrinter, 2, (LPBYTE)p2, dwBytesNeeded, &dwBytesReturned) == 0)
		{
			GlobalFree(p2);
			ClosePrinter(hPrinter);
			return FALSE;
		}
		ClosePrinter(hPrinter);

		// Allocate a global handle for DEVMODE
		HGLOBAL  hDevMode = GlobalAlloc(GHND, sizeof(*p2->pDevMode) + p2->pDevMode->dmDriverExtra);
		ASSERT(hDevMode);
		DEVMODE* pDevMode = (DEVMODE*)GlobalLock(hDevMode);
		ASSERT(pDevMode);

		// copy DEVMODE data from PRINTER_INFO_2::pDevMode
		memcpy(pDevMode, p2->pDevMode, sizeof(*p2->pDevMode) + p2->pDevMode->dmDriverExtra);
		GlobalUnlock(hDevMode);

		BYTE device[60],driver[30],port[30];
		lstrcpy((LPSTR)device,(LPCTSTR)p2->pPrinterName);
		lstrcpy((LPSTR)driver,(LPCTSTR)p2->pDriverName);
		lstrcpy((LPSTR)port,(LPCTSTR)CIPString(p2->pPortName));

		GlobalFree(p2);

		if(!TerSetPrinter(m_terWnd.m_hWnd,device,driver,port, hDevMode))
			TerSetPrinter(m_terWnd.m_hWnd,NULL,NULL,NULL,NULL);
	}

	if (!TerPrint(this->m_terWnd.m_hWnd, FALSE))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::Print\ttERR: can't print current document"));
		return FALSE;
	}

	while (TerIsPrinting(this->m_terWnd.m_hWnd))
	{
		this->PrintSleep(100);
	}

	return TRUE;
}

BOOL CTERProcessor::ExtractDocumentCollectionData(CIPString &sFilePathFrom, CIPString &sDocumentIds)
{
	this->m_sLastError = "";

	if (!this->InitializeTer())
		return FALSE;

	if (!this->IsFileExtension(sFilePathFrom, CIPString(_T("rtf"))))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::ExtractDocumentCollectionData\tERR: input file format is not supported"));
		return FALSE;
	}

	if (!this->CheckFile(sFilePathFrom))
		return FALSE;

	if (!this->OpenDocument(sFilePathFrom))
		return FALSE;

	BOOL _bExtracted = this->ExtractDocumentIds(sDocumentIds);

	this->CloseDocument();
	return _bExtracted;
}

BOOL CTERProcessor::ExtractDocumentIds(CIPString &sDocumentIds)
{
	long _lFoundPosition = -1;
	BOOL _bTagFound = this->FindUniqueTag(TAG_DOCIDS, &_lFoundPosition);
	
	if (_bTagFound == FALSE || _lFoundPosition == -1)
		return FALSE;

	_lFoundPosition = _lFoundPosition + TAG_DOCIDS.GetLength();

	if (!SetTerCursorPos(this->m_terWnd.m_hWnd, this->m_terWnd.GetLineCount() - 1, this->m_terWnd.LineLength(this->m_terWnd.GetLineCount() - 1) - 1, FALSE))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::ExtractDocumentIds\ttERR: can't set new cursor position"));
		return FALSE;
	}

	long _lEndCursorPosition = 0;
	int _iCurrentColumn = -1; //to get absolute cursor position
	if (!GetTerCursorPos(this->m_terWnd.m_hWnd, &_lEndCursorPosition, &_iCurrentColumn))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::ExtractDocumentIds\ttERR: can't get end cursor position"));
		return FALSE;
	}

	CIPString _sFoundIds;
	long _lFoundIdsSize = 0;
	if(!TerSearchReplace(this->m_terWnd.m_hWnd, (LPBYTE) _sFoundIds.GetBuffer(1024), 0, SRCH_RETRIEVE, _lFoundPosition, &_lEndCursorPosition, &_lFoundIdsSize))
	{
		_sFoundIds.ReleaseBuffer();
		this->m_sLastError = CIPString(_T("CTERProcessor::ExtractDocumentIds\ttERR: can't retrieve document id text"));
		return FALSE;
	}
	_sFoundIds.ReleaseBuffer();

	int _iSeparatorPosition = _sFoundIds.Find('|', 1); // ReverseFind vielleicht..
	if (_iSeparatorPosition == -1)
		return FALSE;

	sDocumentIds = _sFoundIds.Mid(1, _iSeparatorPosition - 1);

	return TRUE;
}

BOOL CTERProcessor::AddDocumentIds(CIPString &sDocumentIds)
{
	CIPString _sDocumentIds(TAG_DOCIDS + _T("|"));
	_sDocumentIds = _sDocumentIds + sDocumentIds + _T("|");
	
	long _lStartPosition = 0;
	long _lEndPosition = 0;

	if (!this->AppendText(_sDocumentIds, &_lStartPosition, &_lEndPosition))
		return FALSE;

	if (!this->ChangeFontColorToWhite(_lStartPosition, _lEndPosition))
		return FALSE;

	return TRUE;
}

BOOL CTERProcessor::AddDocument(CIPString &sFileName, BOOL bReplaceTag)
{
	long _iInsertPosition = 0;
	BOOL _bTagFound = this->FindUniqueTag(TAG_ADDCONTENTAT, &_iInsertPosition);

	if (bReplaceTag == TRUE)
	{
		long _lEndPosition = _iInsertPosition + TAG_ADDCONTENTAT.GetLength();
		if(!TerSearchReplace(this->m_terWnd.m_hWnd, 0, (LPBYTE)(LPCTSTR)CIPString(""), SRCH_REPLACE, _iInsertPosition, &_lEndPosition, 0))
		{
			CIPString _sRange;
			_sRange.Format("%d - %d", _iInsertPosition, _lEndPosition);
			this->m_sLastError = CIPString(_T("CTERProcessor::AddDocument\ttWARN: can't delete in " + _sRange + " tag " + TAG_ADDCONTENTAT));
			return FALSE;
		}
	}

	if (_bTagFound)
	{
		if (!SetTerCursorPos(this->m_terWnd.m_hWnd, _iInsertPosition, -1, FALSE))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::AddDocument\ttWARN: can't set new cursor position to " + _iInsertPosition));
			return FALSE;
		}
	}

	if(!TerInsertRtfFile(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR)(sFileName), (_bTagFound) ? -1 : -2, 0, FALSE)) //-1 : insert the rtf document at the current cursor position; -2: insert the rtf file at the end of the current document
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::AddDocument\ttWARN: can't insert document " + sFileName));
		return FALSE;
	}

	if (bReplaceTag == FALSE)
	{
		_bTagFound = this->FindUniqueTag(TAG_ADDCONTENTAT, &_iInsertPosition);
		if (_bTagFound)
		{
			TerInsertText(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR) (CIPString(_T("\n"))), -1, -1, FALSE);
		}
		else
		{
			this->AppendText(CIPString(""));
		}
	}

	return TRUE;
}

BOOL CTERProcessor::ChangeFontColorToWhite(long iStartCursorPosition, long iEndCursorPosition)
{
	if (!SelectTerText(this->m_terWnd.m_hWnd, iStartCursorPosition, -1, iEndCursorPosition, -1, FALSE))
	{
		CIPString _sRange;
		_sRange.Format("start %d - end %d", iStartCursorPosition, iEndCursorPosition);
		this->m_sLastError = CIPString(_T("CTERProcessor::ChangeFontColorToWhite\ttERR: can't select text at " + _sRange));
		return FALSE;
	}
	
	if (!SetTerColor(this->m_terWnd.m_hWnd, (COLORREF) 0xFFFFFF, FALSE))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::ChangeFontColorToWhite\ttERR: can't set font color"));
		return FALSE;
	}

	return TRUE;
}

BOOL CTERProcessor::AppendText(CIPString &sText, long *pStartCursorPosition, long *pEndCursorPosition)
{
	CIPString _sAppendText(_T("\n"));
	_sAppendText = _sAppendText + sText;

	int _iLineCount = this->m_terWnd.GetLineCount();
	int _iLineLength = this->m_terWnd.LineLength(_iLineCount - 1);
	
	if (!SetTerCursorPos(this->m_terWnd.m_hWnd, _iLineCount - 1, _iLineLength - 1, FALSE))
	{
		CIPString _sRange;
		_sRange.Format("line %d - column %d", _iLineCount, _iLineLength - 1);
		this->m_sLastError = CIPString(_T("CTERProcessor::AppendText\ttERR: can't set new cursor position at " + _sRange));
		return FALSE;
	}

	if (pStartCursorPosition != NULL)
	{
		int _iCurrentColumn = -1; //to get absolute cursor position
		if (!GetTerCursorPos(this->m_terWnd.m_hWnd, pStartCursorPosition, &_iCurrentColumn))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::AppendText\ttERR: can't get start cursor position"));
			return FALSE;
		}
	}

	if (!TerInsertText(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR)(_sAppendText), -1, -1, FALSE))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::AppendText\ttERR: can't insert text " + sText));
		return FALSE;
	}

	if (pEndCursorPosition != NULL)
	{
		int _iCurrentColumn = -1; //to get absolute cursor position
		if (!GetTerCursorPos(this->m_terWnd.m_hWnd, pEndCursorPosition, &_iCurrentColumn))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::AppendText\ttERR: can't get end cursor position"));
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CTERProcessor::ReplacePlaceholder(CMapStringToString &mapReplaceTags)
{
	if (mapReplaceTags.GetCount() == 0)
		return TRUE;

	BOOL _bNoError = TRUE;

	POSITION _elementPosition = mapReplaceTags.GetStartPosition();
	while (_elementPosition != NULL)
	{
		CIPString _sReplaceWhat;
		CIPString _sReplaceThrough;

		mapReplaceTags.GetNextAssoc(_elementPosition, _sReplaceWhat, _sReplaceThrough);

		int _iReplaceCount = 0;

		if (this->ReplaceTag(_sReplaceWhat, _sReplaceThrough, &_iReplaceCount))
			_bNoError = FALSE;

		if (_sReplaceWhat == TAG_ADDCONTENTAT && _iReplaceCount == 0)
			this->AppendText(_sReplaceThrough);
	}

	return _bNoError;
}

BOOL CTERProcessor::AddTOC()
{
	long _lTOCStart = 0;

	if (!this->FindUniqueTag(TAG_TOC, &_lTOCStart))
		return TRUE;

	if (_lTOCStart == -1)
		return TRUE;

	return this->ReplaceTag(TAG_TOC, CIPString(""));
}

BOOL CTERProcessor::ReplaceTag(CIPString &sReplaceWhat, CIPString &sReplaceWith, int *pReplacedCount)
{
	if (pReplacedCount != NULL)
		*pReplacedCount = 0;

	if (sReplaceWhat.IsEmpty())
		return TRUE;

	BOOL _bNoError = TRUE;
	this->m_sLastError = CIPString("");

	long _lStartPosition = 0;
	long _lEndPosition = 0;

	while (TRUE)
	{
		if(!TerSearchReplace(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR)(sReplaceWhat), 0, SRCH_SEARCH, _lStartPosition, &_lEndPosition, 0))
			break;

		_lStartPosition = _lEndPosition;
		_lEndPosition = _lStartPosition + sReplaceWhat.GetLength() - 1;

		if(!TerSearchReplace(this->m_terWnd.m_hWnd, 0, (LPBYTE)(LPCTSTR)(sReplaceWith), SRCH_REPLACE, _lStartPosition, &_lEndPosition, 0))
		{
			CIPString _sRange;
			_sRange.Format("%d - %d", _lStartPosition, _lEndPosition);
			this->m_sLastError = this->m_sLastError + CIPString(_T("CTERProcessor::ReplaceTag\ttWARN: can't replace in " + _sRange + " tag " + sReplaceWhat + " with " + sReplaceWith));

			_bNoError = FALSE;
			_lStartPosition = _lEndPosition;
		}
		else
		{
			_lStartPosition = _lStartPosition + sReplaceWhat.GetLength() - 1;
			if (pReplacedCount != NULL)
				*pReplacedCount = *pReplacedCount + 1;
		}

		_lEndPosition = 0;
	}

	return _bNoError;
}

BOOL CTERProcessor::FindUniqueTag(CIPString &sTag, long *lStartPosition)
{
	*lStartPosition = -1;

	if (sTag.IsEmpty())
		return FALSE;

	long _lEndPosition=0;
	if(!TerSearchReplace(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR)(sTag), 0, SRCH_SEARCH, 0, &_lEndPosition, 0))
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::FindUniqueTag\ttWARN: unique tag " + sTag + " not found"));
		return FALSE;
	}
	
	*lStartPosition = _lEndPosition;

	return TRUE;
}

void CTERProcessor::SetTempPath(CIPString &sFilePathFrom)
{
	CIPFile _fFile;			
	_fFile.SetFilePath(sFilePathFrom);
	_fFile.GetPath(__global_PathFrom);
}

void CTERProcessor::CreateTempFileName(CIPString &sFilePathFrom, CIPString &sTempFileName)
{
	sFilePathFrom.Replace('\\','/');

	CIPFile _fFile;
	_fFile.SetFilePath(sFilePathFrom);

	CIPString _sError;
	CIPString _sTempDir;
	_fFile.GetPath(_sTempDir);
	sTempFileName = __GetTempFN(_T("rtf"), _sTempDir, &_sError, TRUE);
	sTempFileName.Replace('\\','/');
}

BOOL CTERProcessor::OpenDocument(CIPString &sFileName)
{
	if (!this->InitializeTer())
		return FALSE;

	::SetFileAttributes( (LPCTSTR) (sFileName), FILE_ATTRIBUTE_NORMAL);
	
	if (this->IsFileExtension(sFileName, CIPString(_T("html"))) || this->IsFileExtension(sFileName, CIPString(_T("htm"))))
	{
		if(!HtsRead(this->m_terWnd.m_hWnd, HTML_FILE, (LPBYTE)(LPCTSTR) sFileName, NULL, NULL, NULL))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::OpenDocument\tERR: can't open file " + sFileName));
			return FALSE;
		}

		return TRUE;
	}

	if (this->IsFileExtension(sFileName, CIPString(_T("rtf"))))
	{
		if(!ReadTerFile(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR) sFileName))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::OpenDocument\tERR: can't open file " + sFileName));
			return FALSE;
		}

		return TRUE;
	}

	this->m_sLastError = CIPString(_T("CTERProcessor::OpenDocument\tERR: can't open file " + sFileName));
	return FALSE;
}

BOOL CTERProcessor::SaveDocumentAs(CIPString &sFileName)
{
	::SetFileAttributes( (LPCTSTR) (sFileName), FILE_ATTRIBUTE_NORMAL);

	TerSetFlags(this->m_terWnd.m_hWnd, TRUE, TFLAG_IGNORE_PICT_LINK);

	TerSetOutputFormat(this->m_terWnd.m_hWnd, SAVE_RTF);

	if (!SaveTerFile(this->m_terWnd.m_hWnd, (LPBYTE)(LPCTSTR) sFileName))
	{
		CIPString _sUserMsg;
		CIPString _sDebugMsg;
		TerGetLastMessage((LPBYTE)(LPCTSTR) _sUserMsg, (LPBYTE)(LPCTSTR) _sDebugMsg);
		this->m_sLastError = CIPString(_T("CTERProcessor::SaveDocumentAs\tERR: can't save opened file as " + sFileName));
		return FALSE;
	}

	return TRUE;
}

BOOL CTERProcessor::CloseDocument()
{
	this->m_terWnd.Clear();
	this->m_terWnd.DeleteContents();
	this->DestroyProcessor();
	return TRUE;
}

LRESULT FAR PASCAL _export VbxCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT user = WM_USER;
	if(message == HTS_PICTURE)
	{
		CIPString _sPict((LPTSTR)lParam);
		_sPict = __global_PathFrom + "\\" + _sPict;

		CIPFile   _f;	  _f.SetFilePath(_sPict);
		CIPString _sName; _f.GetName(_sName);
		CIPString _sExt;  _f.GetExtension(_sExt);
		_sExt.MakeUpper();

		//Convert gif to png
		if(_sExt == _T("GIF"))
		{
			CxImage  image;
			image.Load(_sPict, CXIMAGE_FORMAT_GIF);
			if (image.IsValid())
			{
				CIPString _sFileOut;
				_sName += _T(".png");
				CIPFile::MakeFileName(__global_PathFrom, _sName, _sFileOut);
				image.Save(_sFileOut, CXIMAGE_FORMAT_PNG);
				lstrcpy((LPTSTR)lParam, _sFileOut);

				::__global_PNGTempFileNames.Add(_sFileOut);
			}
		}
		return 0;

	}
	else if(message == HTS_PICT_ID)
	{
	}

	return 0L;
}

BOOL CTERProcessor::InitializeTer()
{
	if (this->m_bIsInitialized == TRUE)
		return TRUE;

	this->m_bIsInitialized = FALSE;

	CRect _rect(0,0,600,600);

	if (!this->m_terWnd.CreateEx(TER_WORD_WRAP|TER_FITTED_VIEW|TER_BORDER_MARGIN, _rect, NULL, 320))
	{
		//if (!this->m_terWnd.Create(TER_WORD_WRAP|TER_FITTED_VIEW|TER_BORDER_MARGIN, _rect, NULL, 329))
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::InitializeTer\tERR: !m_terWnd.Create"));
			return FALSE;
		}
	}

	if(!this->m_terWnd.m_hWnd)
	{
		this->m_sLastError = CIPString(_T("CTERProcessor::InitializeTer\tERR: !m_terWnd.m_hWnd"));
		return FALSE;
	}

	TerRegisterVbxCallback(this->m_terWnd.m_hWnd, (VBX_CALLBACK)VbxCallback);

	HtsInitialize(this->m_terWnd.m_hWnd, NULL);

	this->m_bIsInitialized = TRUE;
	return TRUE;
}

void CTERProcessor::DeleteTempFile(CIPString &sTempFileName)
{
	try
	{
		BOOL _bDeleted = ::DeleteFile(sTempFileName);

		if (_bDeleted == FALSE)
		{
			this->m_sLastError = CIPString(_T("CTERProcessor::DeleteTempFile\tERR:3:Can't delete file: " + sTempFileName));
		}
	}
	catch (CFileException* pEx)
	{
		CIPString _sErrorMessage;
		pEx->GetErrorMessage(_sErrorMessage.GetBuffer(1024), 1024, NULL);
		_sErrorMessage.ReleaseBuffer();
		this->m_sLastError = CIPString(_T("CTERProcessor::DeleteTempFile\tERR:2:Can't delete file: " + sTempFileName + " due to error: " + _sErrorMessage));
		pEx->Delete();
	}
}

void CTERProcessor::DeleteTempFiles(CArray<CIPString, CIPString> &listTempFileNames)
{
	for (int _iElement = 0; _iElement < listTempFileNames.GetCount(); _iElement++)
	{
		if (::_access((CIPString) listTempFileNames.GetAt(_iElement), 00) == 0)
			this->DeleteTempFile((CIPString) listTempFileNames.GetAt(_iElement));
	}

	listTempFileNames.RemoveAll();
}

void CTERProcessor::PrintSleep(int nMilliSeconds)
{
	DWORD n = ::GetTickCount() + nMilliSeconds;
	MSG _msg;

	while(::GetTickCount() <= n)
	{
		while (::PeekMessage(&_msg, NULL, 0, 0, PM_NOREMOVE))      
		{
			if(::GetTickCount() > n) 
				break;

			if (!AfxGetThread()->PumpMessage()) 
			{ 
				::PostQuitMessage(0); 
				break; 
			}
		}

		Sleep(1);
	}
}