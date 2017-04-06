#include "StdAfx.h"
#include ".\officeprocessor.h"
#include "ipfile.h"
#include  <io.h>
#include "terprocessor.h"
#include "microsoftofficeprocessor.h"
#include "openofficeprocessor.h"
#include "atlbase.h"
#include "shlobj.h"
#include "ipcommon.h"

//#define FORCE_OO


CArray<PROCESSOR_TYPE, PROCESSOR_TYPE>	COfficeProcessor::_AVAILABLE_TYPES;
CIPString								COfficeProcessor::_OO_PATH("");
CIPString								COfficeProcessor::_EXE_PATH("");
BOOL									COfficeProcessor::_TYPES_DETERMINED = FALSE;

COfficeProcessor::COfficeProcessor(void)
{
}

COfficeProcessor::~COfficeProcessor(void)
{
}

COfficeProcessor* COfficeProcessor::CreateInstance(PROCESSOR_TYPE typeOfProcessor, CIPString &sErrorMsg)
{
	COfficeProcessor::DetermineAvailableTypes(sErrorMsg);

	COfficeProcessor *pProcessor = NULL;

	PROCESSOR_TYPE _usingType = typeOfProcessor;

	if (_usingType == UNKNOWN)
	{
#ifdef FORCE_OO
		if (COfficeProcessor::IsTypeAvailable(OPENOFFICE))
		{
			_usingType = OPENOFFICE;
		}
		else
		{
			_usingType = TER;
		}
#else

		if (COfficeProcessor::IsTypeAvailable(MSOFFICE))
			_usingType = MSOFFICE;
		else if (COfficeProcessor::IsTypeAvailable(OPENOFFICE))
			_usingType = OPENOFFICE;
		else
			_usingType = TER;
#endif
	}

	if (COfficeProcessor::IsTypeAvailable(_usingType))
	{
		switch (_usingType)
		{
			case (TER) :
				pProcessor = (COfficeProcessor*) new CTERProcessor();
				break;
			case (MSOFFICE) :
				pProcessor = (COfficeProcessor*) new CMicrosoftOfficeProcessor();
				break;
			case (OPENOFFICE) :
				pProcessor = (COfficeProcessor*) new COpenOfficeProcessor(COfficeProcessor::_OO_PATH, COfficeProcessor::_EXE_PATH);
				break;
		}
	}

	return pProcessor;
}

void COfficeProcessor::DetermineAvailableTypes(CIPString &sErrorMsg)
{
	if (COfficeProcessor::_TYPES_DETERMINED == TRUE)
		return;

	CIPString _sCurrentErrorMsg;

	COfficeProcessor::_OO_PATH = CIPString("");
	COfficeProcessor::_EXE_PATH = CIPString("");
	COfficeProcessor::_AVAILABLE_TYPES.RemoveAll();

	if (COfficeProcessor::CheckOOAvailable(COfficeProcessor::_OO_PATH, COfficeProcessor::_EXE_PATH, _sCurrentErrorMsg))
		COfficeProcessor::_AVAILABLE_TYPES.Add(OPENOFFICE);
	else
		sErrorMsg = sErrorMsg + _sCurrentErrorMsg;

	if (COfficeProcessor::CheckMSOAvailable(_sCurrentErrorMsg))
		COfficeProcessor::_AVAILABLE_TYPES.Add(MSOFFICE);
	else
		sErrorMsg = sErrorMsg + _sCurrentErrorMsg;

	COfficeProcessor::_AVAILABLE_TYPES.Add(TER);

	COfficeProcessor::_TYPES_DETERMINED = TRUE;
}

BOOL COfficeProcessor::CheckMSOAvailable(CIPString &sErrorMsg)
{
	CRegKey _regKey;

	long _lOOSuccess = _regKey.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winword.exe", KEY_READ);

	if (_lOOSuccess != ERROR_SUCCESS)
		_lOOSuccess = _regKey.Open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winword.exe", KEY_READ);

	if (_lOOSuccess != ERROR_SUCCESS)
	{
		_regKey.Close();
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: MS Office: not available"));
		return FALSE;
	}

	CIPString _sKeyValue;
	unsigned long _lBufferSize = 1024;
	if (_regKey.QueryStringValue("", _sKeyValue.GetBuffer(_lBufferSize), &_lBufferSize) != ERROR_SUCCESS)
	{
		_sKeyValue.ReleaseBuffer();
		_regKey.Close();
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: MS Office: not available"));
		return FALSE;
	}

	_regKey.Close();
	_sKeyValue.ReleaseBuffer();
	CIPString _sMSOExeFileName = _sKeyValue;

	if ((_sMSOExeFileName.GetLength() == 0) || (_access(_sMSOExeFileName, 00) != 0))
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: MS Office: not available (probably installed and manually deleted)"));
		return FALSE;
	}

	if (!CMicrosoftOfficeProcessor::IsInitializable())
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: MS Office: not available (probably installed and manually deleted)"));
		return FALSE;
	}

	return TRUE;
}

BOOL COfficeProcessor::CheckOOAvailable(CIPString &sOOPath, CIPString &sEXEPath, CIPString &sErrorMsg)
{
#ifndef FORCE_OO
	CRegKey _regKey;

	long _lOOSuccess = _regKey.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\soffice.exe", KEY_READ);

	if (_lOOSuccess != ERROR_SUCCESS)
		_lOOSuccess = _regKey.Open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\soffice.exe", KEY_READ);

	if (_lOOSuccess != ERROR_SUCCESS)
	{
		_regKey.Close();
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available"));
		return FALSE;
	}

	CIPString _sKeyValue;
	unsigned long _lBufferSize = 1024;
	if (_regKey.QueryStringValue("", _sKeyValue.GetBuffer(_lBufferSize), &_lBufferSize) != ERROR_SUCCESS)
	{
		_sKeyValue.ReleaseBuffer();
		_regKey.Close();
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available"));
		return FALSE;
	}

	_regKey.Close();
	_sKeyValue.ReleaseBuffer();
#else	//FORCE_OO
	CIPString _sKeyValue = "C:\\programs\\OpenOffice.org 2.0\\program\\soffice.exe";
#endif

	CIPString _sOOExeFileName = _sKeyValue;


	if ((_sOOExeFileName.GetLength() == 0) || (_access(_sOOExeFileName, 00) != 0))
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (probably installed and manually deleted)"));
		return FALSE;
	}

	::GetModuleFileName(::AfxGetInstanceHandle(), _sKeyValue.GetBuffer(1024), 1024);
	_sKeyValue.ReleaseBuffer();
	CIPString _sCurrentExeFileName = _sKeyValue;

	CIPString _sCurrentExeFilePath;
	CIPString _sOOExeDirectory;

	CIPFile _fOOExe;
	_fOOExe.SetFilePath(_sOOExeFileName);
	_fOOExe.GetPath(_sOOExeDirectory);

	_fOOExe.SetFilePath(_sCurrentExeFileName);
	_fOOExe.GetPath(_sCurrentExeFilePath);

	_sCurrentExeFileName = _sCurrentExeFilePath + "\\SHIOOAutomation.exe";

	if ((_sCurrentExeFileName.GetLength() == 0) || (_access(_sCurrentExeFileName, 00) != 0))
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (communication app is not available)"+_sCurrentExeFileName));
		return FALSE;
	}


#ifdef FORCE_OO
	sOOPath = _sOOExeDirectory;
	sEXEPath = _sCurrentExeFileName;
	return TRUE;
#endif


	if (_access(_sOOExeDirectory + "\\version.ini", 00) != 0)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (version not available)"));
		return FALSE;
	}

	GetPrivateProfileString("Version", "MsiProductVersion", "NULL", _sKeyValue.GetBuffer(1024), 1024, _sOOExeDirectory + "\\version.ini"); 
	_sKeyValue.ReleaseBuffer();

	CIPString _sVersion = _sKeyValue;

	if ((_sVersion.GetLength() == 0) || (_sVersion.Left(2) != _T("2.")))
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (wrong version)"));
		return FALSE;
	}

	if(!SHGetSpecialFolderPath(NULL, _sKeyValue.GetBuffer(MAX_PATH), CSIDL_APPDATA, FALSE))
	{
		_sKeyValue.ReleaseBuffer();
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (application data path not available)"));
		return FALSE;
	}

	_sKeyValue.ReleaseBuffer();
	CIPString _sOOAppDataPath = _sKeyValue + "\\OpenOffice.org2\\user\\registry\\data\\org\\openoffice\\Setup.xcu";

	if (_access(_sOOAppDataPath, 00) != 0)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (oo wasn't user started yet)"));
		return FALSE;
	}

	CIPString _sOOConfiguration = _sOOAppDataPath;
	::__GetFileContentFast(_sOOConfiguration);
	
	if (_sOOConfiguration.GetLength() == 0)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (cann't read configuration data)"));
		return FALSE;
	}

	int _iTagPosition = _sOOConfiguration.Find(_T("FirstStartWizardCompleted"));
	if (_iTagPosition == -1)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (oo user hasn't completed first start wizard)"));
		return FALSE;
	}

	_iTagPosition = _sOOConfiguration.Find(_T("value"), _iTagPosition);
	if (_iTagPosition == -1)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (oo user hasn't completed first start wizard)"));
		return FALSE;
	}

	_iTagPosition = _sOOConfiguration.Find(_T(">"), _iTagPosition);
	if (_iTagPosition == -1)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (oo user hasn't completed first start wizard)"));
		return FALSE;
	}

	int _iTagStartPosition  = _iTagPosition + 1;

	_iTagPosition = _sOOConfiguration.Find(_T("<"), _iTagPosition);
	if (_iTagPosition == -1)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (oo user hasn't completed first start wizard)"));
		return FALSE;
	}

	CIPString _sTagValue = _sOOConfiguration.Mid(_iTagStartPosition, _iTagPosition - _iTagStartPosition);
	if (_sTagValue.CompareNoCase(_T("true")) != 0)
	{
		sErrorMsg = CIPString(_T("COfficeProcessor\tINF: OpenOffice: not available (oo user hasn't completed first start wizard)"));
		return FALSE;
	}

	sOOPath = _sOOExeDirectory;
	sEXEPath = _sCurrentExeFileName;

	return TRUE;
}	

BOOL COfficeProcessor::IsTypeAvailable(PROCESSOR_TYPE typeOfProcessor)
{
	if (COfficeProcessor::_TYPES_DETERMINED == FALSE)
		return FALSE;

	for (int _iType = 0; _iType < COfficeProcessor::_AVAILABLE_TYPES.GetCount(); _iType++)
	{
		if ((PROCESSOR_TYPE) COfficeProcessor::_AVAILABLE_TYPES.GetAt(_iType) == typeOfProcessor)
			return TRUE;
	}

	return FALSE;
}

void COfficeProcessor::GetLastError(CIPString &sError)
{
	sError = this->m_sLastError;
}

BOOL COfficeProcessor::IsFileExtension(CIPString &sFilePath, CIPString &sExtension)
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

BOOL COfficeProcessor::CheckDirectory(CIPString &sFileName)
{
	CIPString _sPath;
	CIPFile _fFile;
	_fFile.SetFilePath(sFileName);
	_fFile.GetPath(_sPath);

	if(_access(_sPath, 00) == 0)
		return TRUE;

	if(!CIPFile::MkDirFull(_sPath))
	{
		this->m_sLastError = CIPString(_T("COfficeProcessor::CheckDirectory\tERR: can't create directory: " + _sPath));
		return FALSE;
	}

	return TRUE;
}

BOOL COfficeProcessor::CheckFile(CIPString &sFileName)
{
	if(_access(sFileName, 00) == 0)
		return TRUE;

	this->m_sLastError = CIPString(_T("COfficeProcessor::CheckFile\tERR: file not exists: " + sFileName));
	return FALSE;
}