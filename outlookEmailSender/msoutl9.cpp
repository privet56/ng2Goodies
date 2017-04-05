// Von Klassen-Assistent automatisch erstellte IDispatch-Kapselungsklasse(n).

#include "stdafx.h"
#include "msoutl9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Action 

/////////////////////////////////////////////////////////////////////////////
// Operationen Action 

LPDISPATCH Action::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Action::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Action::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Action::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Action::GetCopyLike()
{
	long result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Action::SetCopyLike(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL Action::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void Action::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString Action::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Action::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Action::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Action::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Action::GetPrefix()
{
	CString result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Action::SetPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Action::GetReplyStyle()
{
	long result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Action::SetReplyStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Action::GetResponseStyle()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Action::SetResponseStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Action::GetShowOn()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Action::SetShowOn(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Action::Delete()
{
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Action::Execute()
{
	LPDISPATCH result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Application 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Application 

LPDISPATCH _Application::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Application::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetAssistant()
{
	LPDISPATCH result;
	InvokeHelper(0x114, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _Application::GetVersion()
{
	CString result;
	InvokeHelper(0x116, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::ActiveExplorer()
{
	LPDISPATCH result;
	InvokeHelper(0x111, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::ActiveInspector()
{
	LPDISPATCH result;
	InvokeHelper(0x112, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::CreateItem(long ItemType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ItemType);
	return result;
}

LPDISPATCH _Application::CreateItemFromTemplate(LPCTSTR TemplatePath, const VARIANT& InFolder)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x10b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TemplatePath, &InFolder);
	return result;
}

LPDISPATCH _Application::CreateObject(LPCTSTR ObjectName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x115, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ObjectName);
	return result;
}

LPDISPATCH _Application::GetNamespace(LPCTSTR Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x110, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type);
	return result;
}

void _Application::Quit()
{
	InvokeHelper(0x113, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Application::GetCOMAddIns()
{
	LPDISPATCH result;
	InvokeHelper(0x118, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetExplorers()
{
	LPDISPATCH result;
	InvokeHelper(0x119, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetInspectors()
{
	LPDISPATCH result;
	InvokeHelper(0x11a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetLanguageSettings()
{
	LPDISPATCH result;
	InvokeHelper(0x11b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Application::GetProductCode()
{
	CString result;
	InvokeHelper(0x11c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::GetAnswerWizard()
{
	LPDISPATCH result;
	InvokeHelper(0x11d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Application::ActiveWindow()
{
	LPDISPATCH result;
	InvokeHelper(0x11f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _NameSpace 

/////////////////////////////////////////////////////////////////////////////
// Operationen _NameSpace 

LPDISPATCH _NameSpace::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _NameSpace::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::GetCurrentUser()
{
	LPDISPATCH result;
	InvokeHelper(0x2101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::GetFolders()
{
	LPDISPATCH result;
	InvokeHelper(0x2103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _NameSpace::GetType()
{
	CString result;
	InvokeHelper(0x2104, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::GetAddressLists()
{
	LPDISPATCH result;
	InvokeHelper(0x210d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::CreateRecipient(LPCTSTR RecipientName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x210a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		RecipientName);
	return result;
}

LPDISPATCH _NameSpace::GetDefaultFolder(long FolderType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x210b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FolderType);
	return result;
}

LPDISPATCH _NameSpace::GetFolderFromID(LPCTSTR EntryIDFolder, const VARIANT& EntryIDStore)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x2108, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		EntryIDFolder, &EntryIDStore);
	return result;
}

LPDISPATCH _NameSpace::GetItemFromID(LPCTSTR EntryIDItem, const VARIANT& EntryIDStore)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x2109, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		EntryIDItem, &EntryIDStore);
	return result;
}

LPDISPATCH _NameSpace::GetRecipientFromID(LPCTSTR EntryID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2107, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		EntryID);
	return result;
}

LPDISPATCH _NameSpace::GetSharedDefaultFolder(LPDISPATCH Recipient, long FolderType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x210c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Recipient, FolderType);
	return result;
}

void _NameSpace::Logoff()
{
	InvokeHelper(0x2106, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _NameSpace::Logon(const VARIANT& Profile, const VARIANT& Password, const VARIANT& ShowDialog, const VARIANT& NewSession)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2105, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Profile, &Password, &ShowDialog, &NewSession);
}

LPDISPATCH _NameSpace::PickFolder()
{
	LPDISPATCH result;
	InvokeHelper(0x210e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NameSpace::GetSyncObjects()
{
	LPDISPATCH result;
	InvokeHelper(0x2118, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _NameSpace::AddStore(const VARIANT& Store)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2119, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Store);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Recipient 

/////////////////////////////////////////////////////////////////////////////
// Operationen Recipient 

LPDISPATCH Recipient::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recipient::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recipient::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recipient::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Recipient::GetAddress()
{
	CString result;
	InvokeHelper(0x3003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recipient::GetAddressEntry()
{
	LPDISPATCH result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Recipient::SetRefAddressEntry(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x79, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CString Recipient::GetAutoResponse()
{
	CString result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Recipient::SetAutoResponse(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long Recipient::GetDisplayType()
{
	long result;
	InvokeHelper(0x3900, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Recipient::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Recipient::GetIndex()
{
	long result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long Recipient::GetMeetingResponseStatus()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Recipient::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL Recipient::GetResolved()
{
	BOOL result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long Recipient::GetTrackingStatus()
{
	long result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recipient::SetTrackingStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE Recipient::GetTrackingStatusTime()
{
	DATE result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void Recipient::SetTrackingStatusTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long Recipient::GetType()
{
	long result;
	InvokeHelper(0xc15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Recipient::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void Recipient::Delete()
{
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString Recipient::FreeBusy(DATE Start, long MinPerChar, const VARIANT& CompleteFormat)
{
	CString result;
	static BYTE parms[] =
		VTS_DATE VTS_I4 VTS_VARIANT;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Start, MinPerChar, &CompleteFormat);
	return result;
}

BOOL Recipient::Resolve()
{
	BOOL result;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften AddressEntry 

/////////////////////////////////////////////////////////////////////////////
// Operationen AddressEntry 

LPDISPATCH AddressEntry::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AddressEntry::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntry::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntry::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString AddressEntry::GetAddress()
{
	CString result;
	InvokeHelper(0x3003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void AddressEntry::SetAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long AddressEntry::GetDisplayType()
{
	long result;
	InvokeHelper(0x3900, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString AddressEntry::GetId()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntry::GetManager()
{
	LPDISPATCH result;
	InvokeHelper(0x303, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntry::GetMembers()
{
	LPDISPATCH result;
	InvokeHelper(0x304, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString AddressEntry::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void AddressEntry::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString AddressEntry::GetType()
{
	CString result;
	InvokeHelper(0x3002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void AddressEntry::SetType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void AddressEntry::Delete()
{
	InvokeHelper(0x302, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void AddressEntry::Details(const VARIANT& HWnd)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x301, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &HWnd);
}

CString AddressEntry::GetFreeBusy(DATE Start, long MinPerChar, const VARIANT& CompleteFormat)
{
	CString result;
	static BYTE parms[] =
		VTS_DATE VTS_I4 VTS_VARIANT;
	InvokeHelper(0x306, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Start, MinPerChar, &CompleteFormat);
	return result;
}

void AddressEntry::Update(const VARIANT& MakePermanent, const VARIANT& Refresh)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x300, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &MakePermanent, &Refresh);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften AddressEntries 

/////////////////////////////////////////////////////////////////////////////
// Operationen AddressEntries 

LPDISPATCH AddressEntries::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AddressEntries::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntries::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntries::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AddressEntries::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntries::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH AddressEntries::Add(LPCTSTR Type, const VARIANT& Name, const VARIANT& Address)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Type, &Name, &Address);
	return result;
}

LPDISPATCH AddressEntries::GetFirst()
{
	LPDISPATCH result;
	InvokeHelper(0x56, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntries::GetLast()
{
	LPDISPATCH result;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntries::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressEntries::GetPrevious()
{
	LPDISPATCH result;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void AddressEntries::Sort(const VARIANT& Property_, const VARIANT& Order)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x61, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Property_, &Order);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Folders 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Folders 

LPDISPATCH _Folders::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Folders::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Folders::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Folders::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Folders::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Folders::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH _Folders::Add(LPCTSTR Name, const VARIANT& Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &Type);
	return result;
}

LPDISPATCH _Folders::GetFirst()
{
	LPDISPATCH result;
	InvokeHelper(0x56, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Folders::GetLast()
{
	LPDISPATCH result;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Folders::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Folders::GetPrevious()
{
	LPDISPATCH result;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Folders::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften MAPIFolder 

/////////////////////////////////////////////////////////////////////////////
// Operationen MAPIFolder 

LPDISPATCH MAPIFolder::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long MAPIFolder::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH MAPIFolder::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH MAPIFolder::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long MAPIFolder::GetDefaultItemType()
{
	long result;
	InvokeHelper(0x3106, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString MAPIFolder::GetDefaultMessageClass()
{
	CString result;
	InvokeHelper(0x3107, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString MAPIFolder::GetDescription()
{
	CString result;
	InvokeHelper(0x3004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void MAPIFolder::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString MAPIFolder::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH MAPIFolder::GetFolders()
{
	LPDISPATCH result;
	InvokeHelper(0x2103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH MAPIFolder::GetItems()
{
	LPDISPATCH result;
	InvokeHelper(0x3100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString MAPIFolder::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void MAPIFolder::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString MAPIFolder::GetStoreID()
{
	CString result;
	InvokeHelper(0x3108, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long MAPIFolder::GetUnReadItemCount()
{
	long result;
	InvokeHelper(0x3603, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH MAPIFolder::CopyTo(LPDISPATCH DestinationFolder)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestinationFolder);
	return result;
}

void MAPIFolder::Delete()
{
	InvokeHelper(0xf045, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void MAPIFolder::Display()
{
	InvokeHelper(0x3104, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH MAPIFolder::GetExplorer(const VARIANT& DisplayMode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3101, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&DisplayMode);
	return result;
}

void MAPIFolder::MoveTo(LPDISPATCH DestinationFolder)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 DestinationFolder);
}

BOOL MAPIFolder::GetWebViewOn()
{
	BOOL result;
	InvokeHelper(0x3112, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void MAPIFolder::SetWebViewOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString MAPIFolder::GetWebViewURL()
{
	CString result;
	InvokeHelper(0x3113, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void MAPIFolder::SetWebViewURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3113, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL MAPIFolder::GetWebViewAllowNavigation()
{
	BOOL result;
	InvokeHelper(0x3114, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void MAPIFolder::SetWebViewAllowNavigation(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3114, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Items 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Items 

LPDISPATCH _Items::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Items::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Items::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

BOOL _Items::GetIncludeRecurrences()
{
	BOOL result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Items::SetIncludeRecurrences(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _Items::Add(const VARIANT& Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Type);
	return result;
}

LPDISPATCH _Items::Find(LPCTSTR Filter)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x62, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Filter);
	return result;
}

LPDISPATCH _Items::FindNext()
{
	LPDISPATCH result;
	InvokeHelper(0x63, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::GetFirst()
{
	LPDISPATCH result;
	InvokeHelper(0x56, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::GetLast()
{
	LPDISPATCH result;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::GetNext()
{
	LPDISPATCH result;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Items::GetPrevious()
{
	LPDISPATCH result;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Items::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void _Items::ResetColumns()
{
	InvokeHelper(0x5d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _Items::Restrict(LPCTSTR Filter)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Filter);
	return result;
}

void _Items::SetColumns(LPCTSTR Columns)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Columns);
}

void _Items::Sort(LPCTSTR Property_, const VARIANT& Descending)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x61, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Property_, &Descending);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Explorer 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Explorer 

LPDISPATCH _Explorer::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Explorer::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorer::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorer::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorer::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x2100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorer::GetCurrentFolder()
{
	LPDISPATCH result;
	InvokeHelper(0x2101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Explorer::SetRefCurrentFolder(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2101, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

void _Explorer::Close()
{
	InvokeHelper(0x2103, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _Explorer::Display()
{
	InvokeHelper(0x2104, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _Explorer::GetCaption()
{
	CString result;
	InvokeHelper(0x2111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT _Explorer::GetCurrentView()
{
	VARIANT result;
	InvokeHelper(0x2200, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void _Explorer::SetCurrentView(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2200, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long _Explorer::GetHeight()
{
	long result;
	InvokeHelper(0x2114, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Explorer::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2114, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Explorer::GetLeft()
{
	long result;
	InvokeHelper(0x2115, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Explorer::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2115, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _Explorer::GetPanes()
{
	LPDISPATCH result;
	InvokeHelper(0x2201, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorer::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x2202, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Explorer::GetTop()
{
	long result;
	InvokeHelper(0x2116, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Explorer::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2116, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Explorer::GetWidth()
{
	long result;
	InvokeHelper(0x2117, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Explorer::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2117, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Explorer::GetWindowState()
{
	long result;
	InvokeHelper(0x2112, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Explorer::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Explorer::Activate()
{
	InvokeHelper(0x2113, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _Explorer::IsPaneVisible(long Pane)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2203, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Pane);
	return result;
}

void _Explorer::ShowPane(long Pane, BOOL Visible)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x2204, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Pane, Visible);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Panes 

/////////////////////////////////////////////////////////////////////////////
// Operationen Panes 

LPDISPATCH Panes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Panes::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Panes::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Panes::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Panes::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Panes::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Selection 

/////////////////////////////////////////////////////////////////////////////
// Operationen Selection 

LPDISPATCH Selection::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Selection::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Selection::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Selection::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften AddressLists 

/////////////////////////////////////////////////////////////////////////////
// Operationen AddressLists 

LPDISPATCH AddressLists::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AddressLists::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressLists::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressLists::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AddressLists::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressLists::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften AddressList 

/////////////////////////////////////////////////////////////////////////////
// Operationen AddressList 

LPDISPATCH AddressList::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long AddressList::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressList::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressList::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH AddressList::GetAddressEntries()
{
	LPDISPATCH result;
	InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString AddressList::GetId()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long AddressList::GetIndex()
{
	long result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL AddressList::GetIsReadOnly()
{
	BOOL result;
	InvokeHelper(0xf017, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString AddressList::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften SyncObjects 

/////////////////////////////////////////////////////////////////////////////
// Operationen SyncObjects 

LPDISPATCH SyncObjects::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SyncObjects::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH SyncObjects::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH SyncObjects::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long SyncObjects::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH SyncObjects::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _SyncObject 

/////////////////////////////////////////////////////////////////////////////
// Operationen _SyncObject 

LPDISPATCH _SyncObject::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _SyncObject::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _SyncObject::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _SyncObject::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _SyncObject::GetName()
{
	CString result;
	InvokeHelper(0x2100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _SyncObject::Start()
{
	InvokeHelper(0x2101, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _SyncObject::Stop()
{
	InvokeHelper(0x2102, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften SyncObjectEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen SyncObjectEvents 

void SyncObjectEvents::SyncStart()
{
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void SyncObjectEvents::Progress(long State, LPCTSTR Description, long Value, long Max)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 State, Description, Value, Max);
}

void SyncObjectEvents::OnError(long Code, LPCTSTR Description)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Code, Description);
}

void SyncObjectEvents::SyncEnd()
{
	InvokeHelper(0xf004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Inspector 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Inspector 

LPDISPATCH _Inspector::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Inspector::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspector::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspector::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspector::GetCommandBars()
{
	LPDISPATCH result;
	InvokeHelper(0x2100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspector::GetCurrentItem()
{
	LPDISPATCH result;
	InvokeHelper(0x2102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Inspector::GetEditorType()
{
	long result;
	InvokeHelper(0x2110, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspector::GetModifiedFormPages()
{
	LPDISPATCH result;
	InvokeHelper(0x2106, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _Inspector::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2103, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

void _Inspector::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2104, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

void _Inspector::HideFormPage(LPCTSTR PageName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2108, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PageName);
}

BOOL _Inspector::IsWordMail()
{
	BOOL result;
	InvokeHelper(0x2105, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _Inspector::SetCurrentFormPage(LPCTSTR PageName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x210c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PageName);
}

void _Inspector::ShowFormPage(LPCTSTR PageName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2109, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PageName);
}

LPDISPATCH _Inspector::GetHTMLEditor()
{
	LPDISPATCH result;
	InvokeHelper(0x210e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspector::GetWordEditor()
{
	LPDISPATCH result;
	InvokeHelper(0x210f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _Inspector::GetCaption()
{
	CString result;
	InvokeHelper(0x2111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long _Inspector::GetHeight()
{
	long result;
	InvokeHelper(0x2114, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Inspector::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2114, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Inspector::GetLeft()
{
	long result;
	InvokeHelper(0x2115, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Inspector::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2115, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Inspector::GetTop()
{
	long result;
	InvokeHelper(0x2116, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Inspector::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2116, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Inspector::GetWidth()
{
	long result;
	InvokeHelper(0x2117, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Inspector::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2117, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _Inspector::GetWindowState()
{
	long result;
	InvokeHelper(0x2112, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _Inspector::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _Inspector::Activate()
{
	InvokeHelper(0x2113, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Explorers 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Explorers 

LPDISPATCH _Explorers::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Explorers::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorers::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorers::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Explorers::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Explorers::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH _Explorers::Add(const VARIANT& Folder, long DisplayMode)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Folder, DisplayMode);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ExplorerEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen ExplorerEvents 

void ExplorerEvents::Activate()
{
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ExplorerEvents::FolderSwitch()
{
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ExplorerEvents::BeforeFolderSwitch(LPDISPATCH NewFolder, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NewFolder, Cancel);
}

void ExplorerEvents::ViewSwitch()
{
	InvokeHelper(0xf004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ExplorerEvents::BeforeViewSwitch(const VARIANT& NewView, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_PBOOL;
	InvokeHelper(0xf005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &NewView, Cancel);
}

void ExplorerEvents::Deactivate()
{
	InvokeHelper(0xf006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ExplorerEvents::SelectionChange()
{
	InvokeHelper(0xf007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ExplorerEvents::Close()
{
	InvokeHelper(0xf008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _Inspectors 

/////////////////////////////////////////////////////////////////////////////
// Operationen _Inspectors 

LPDISPATCH _Inspectors::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Inspectors::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspectors::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspectors::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _Inspectors::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _Inspectors::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH _Inspectors::Add(LPDISPATCH Item)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Item);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften InspectorEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen InspectorEvents 

void InspectorEvents::Activate()
{
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void InspectorEvents::Deactivate()
{
	InvokeHelper(0xf006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void InspectorEvents::Close()
{
	InvokeHelper(0xf008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Actions 

/////////////////////////////////////////////////////////////////////////////
// Operationen Actions 

LPDISPATCH Actions::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Actions::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Actions::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Actions::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Actions::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Actions::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH Actions::Add()
{
	LPDISPATCH result;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void Actions::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x52, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ApplicationEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen ApplicationEvents 

void ApplicationEvents::ItemSend(LPDISPATCH Item, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Item, Cancel);
}

void ApplicationEvents::NewMail()
{
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ApplicationEvents::Reminder(LPDISPATCH Item)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Item);
}

void ApplicationEvents::OptionsPagesAdd(LPDISPATCH Pages)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Pages);
}

void ApplicationEvents::Startup()
{
	InvokeHelper(0xf006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ApplicationEvents::Quit()
{
	InvokeHelper(0xf007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften PropertyPages 

/////////////////////////////////////////////////////////////////////////////
// Operationen PropertyPages 

LPDISPATCH PropertyPages::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PropertyPages::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PropertyPages::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PropertyPages::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PropertyPages::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PropertyPages::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void PropertyPages::Add(const VARIANT& Page, LPCTSTR Title)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Page, Title);
}

void PropertyPages::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _AppointmentItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _AppointmentItem 

LPDISPATCH _AppointmentItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _AppointmentItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _AppointmentItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _AppointmentItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _AppointmentItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _AppointmentItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _AppointmentItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _AppointmentItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _AppointmentItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _AppointmentItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _AppointmentItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _AppointmentItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _AppointmentItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _AppointmentItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _AppointmentItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _AppointmentItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _AppointmentItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _AppointmentItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

BOOL _AppointmentItem::GetAllDayEvent()
{
	BOOL result;
	InvokeHelper(0x8215, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetAllDayEvent(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8215, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _AppointmentItem::GetBusyStatus()
{
	long result;
	InvokeHelper(0x8205, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetBusyStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8205, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _AppointmentItem::GetDuration()
{
	long result;
	InvokeHelper(0x8213, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetDuration(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8213, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _AppointmentItem::GetEnd()
{
	DATE result;
	InvokeHelper(0x820e, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetEnd(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x820e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _AppointmentItem::GetIsOnlineMeeting()
{
	BOOL result;
	InvokeHelper(0x8240, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetIsOnlineMeeting(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8240, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _AppointmentItem::GetIsRecurring()
{
	BOOL result;
	InvokeHelper(0x8223, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _AppointmentItem::GetLocation()
{
	CString result;
	InvokeHelper(0x8208, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetLocation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8208, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _AppointmentItem::GetMeetingStatus()
{
	long result;
	InvokeHelper(0x8217, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetMeetingStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8217, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _AppointmentItem::GetNetMeetingAutoStart()
{
	BOOL result;
	InvokeHelper(0x8244, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNetMeetingAutoStart(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8244, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _AppointmentItem::GetNetMeetingOrganizerAlias()
{
	CString result;
	InvokeHelper(0x8243, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNetMeetingOrganizerAlias(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8243, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetNetMeetingServer()
{
	CString result;
	InvokeHelper(0x8242, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNetMeetingServer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8242, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _AppointmentItem::GetNetMeetingType()
{
	long result;
	InvokeHelper(0x8241, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNetMeetingType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8241, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _AppointmentItem::GetOptionalAttendees()
{
	CString result;
	InvokeHelper(0xe03, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetOptionalAttendees(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe03, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetOrganizer()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf814, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _AppointmentItem::GetRecurrenceState()
{
	long result;
	InvokeHelper(0xf545, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _AppointmentItem::GetReminderMinutesBeforeStart()
{
	long result;
	InvokeHelper(0x8501, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetReminderMinutesBeforeStart(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _AppointmentItem::GetReminderOverrideDefault()
{
	BOOL result;
	InvokeHelper(0x851c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetReminderOverrideDefault(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x851c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _AppointmentItem::GetReminderPlaySound()
{
	BOOL result;
	InvokeHelper(0x851e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetReminderPlaySound(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x851e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _AppointmentItem::GetReminderSet()
{
	BOOL result;
	InvokeHelper(0x8503, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetReminderSet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _AppointmentItem::GetReminderSoundFile()
{
	CString result;
	InvokeHelper(0x851f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetReminderSoundFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x851f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _AppointmentItem::GetReplyTime()
{
	DATE result;
	InvokeHelper(0x8220, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetReplyTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8220, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _AppointmentItem::GetRequiredAttendees()
{
	CString result;
	InvokeHelper(0xe04, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetRequiredAttendees(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe04, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetResources()
{
	CString result;
	InvokeHelper(0xe02, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetResources(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe02, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _AppointmentItem::GetResponseRequested()
{
	BOOL result;
	InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetResponseRequested(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _AppointmentItem::GetResponseStatus()
{
	long result;
	InvokeHelper(0x8218, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

DATE _AppointmentItem::GetStart()
{
	DATE result;
	InvokeHelper(0x820d, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetStart(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x820d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void _AppointmentItem::ClearRecurrencePattern()
{
	InvokeHelper(0xf0a5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _AppointmentItem::ForwardAsVcal()
{
	LPDISPATCH result;
	InvokeHelper(0xf547, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::GetRecurrencePattern()
{
	LPDISPATCH result;
	InvokeHelper(0xf0a4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _AppointmentItem::Respond(long Response, const VARIANT& fNoUI, const VARIANT& fAdditionalTextDialog)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xf502, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Response, &fNoUI, &fAdditionalTextDialog);
	return result;
}

void _AppointmentItem::Send()
{
	InvokeHelper(0xf075, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString _AppointmentItem::GetNetMeetingDocPathName()
{
	CString result;
	InvokeHelper(0x8247, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNetMeetingDocPathName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8247, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _AppointmentItem::GetNetShowURL()
{
	CString result;
	InvokeHelper(0x8248, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetNetShowURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8248, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _AppointmentItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _AppointmentItem::GetConferenceServerAllowExternal()
{
	BOOL result;
	InvokeHelper(0x8246, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetConferenceServerAllowExternal(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8246, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _AppointmentItem::GetConferenceServerPassword()
{
	CString result;
	InvokeHelper(0x8249, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _AppointmentItem::SetConferenceServerPassword(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8249, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Attachments 

/////////////////////////////////////////////////////////////////////////////
// Operationen Attachments 

LPDISPATCH Attachments::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Attachments::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Attachments::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Attachments::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Attachments::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Attachments::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH Attachments::Add(const VARIANT& Source, const VARIANT& Type, const VARIANT& Position, const VARIANT& DisplayName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Source, &Type, &Position, &DisplayName);
	return result;
}

void Attachments::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Attachment 

/////////////////////////////////////////////////////////////////////////////
// Operationen Attachment 

LPDISPATCH Attachment::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Attachment::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Attachment::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Attachment::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Attachment::GetDisplayName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void Attachment::SetDisplayName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString Attachment::GetFileName()
{
	CString result;
	InvokeHelper(0x3704, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Attachment::GetIndex()
{
	long result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString Attachment::GetPathName()
{
	CString result;
	InvokeHelper(0x3708, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Attachment::GetPosition()
{
	long result;
	InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Attachment::SetPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long Attachment::GetType()
{
	long result;
	InvokeHelper(0x3705, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void Attachment::Delete()
{
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Attachment::SaveAsFile(LPCTSTR Path)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften FormDescription 

/////////////////////////////////////////////////////////////////////////////
// Operationen FormDescription 

LPDISPATCH FormDescription::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long FormDescription::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FormDescription::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FormDescription::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString FormDescription::GetCategory()
{
	CString result;
	InvokeHelper(0x3304, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetCategory(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3304, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetCategorySub()
{
	CString result;
	InvokeHelper(0x3305, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetCategorySub(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3305, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetComment()
{
	CString result;
	InvokeHelper(0x3004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetComment(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetContactName()
{
	CString result;
	InvokeHelper(0x3303, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetContactName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3303, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetDisplayName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetDisplayName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL FormDescription::GetHidden()
{
	BOOL result;
	InvokeHelper(0x3307, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FormDescription::SetHidden(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3307, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString FormDescription::GetIcon()
{
	CString result;
	InvokeHelper(0xffd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetIcon(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xffd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL FormDescription::GetLocked()
{
	BOOL result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FormDescription::SetLocked(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString FormDescription::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString FormDescription::GetMiniIcon()
{
	CString result;
	InvokeHelper(0xffc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetMiniIcon(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xffc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetName()
{
	CString result;
	InvokeHelper(0xf01d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf01d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetNumber()
{
	CString result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL FormDescription::GetOneOff()
{
	BOOL result;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FormDescription::SetOneOff(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString FormDescription::GetPassword()
{
	CString result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetPassword(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FormDescription::GetScriptText()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString FormDescription::GetTemplate()
{
	CString result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetTemplate(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL FormDescription::GetUseWordMail()
{
	BOOL result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void FormDescription::SetUseWordMail(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString FormDescription::GetVersion()
{
	CString result;
	InvokeHelper(0x3301, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FormDescription::SetVersion(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3301, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void FormDescription::PublishForm(long Registry, const VARIANT& Folder)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Registry, &Folder);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften UserProperties 

/////////////////////////////////////////////////////////////////////////////
// Operationen UserProperties 

LPDISPATCH UserProperties::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long UserProperties::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH UserProperties::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH UserProperties::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long UserProperties::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH UserProperties::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH UserProperties::Add(LPCTSTR Name, long Type, const VARIANT& AddToFolderFields, const VARIANT& DisplayFormat)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, Type, &AddToFolderFields, &DisplayFormat);
	return result;
}

LPDISPATCH UserProperties::Find(LPCTSTR Name, const VARIANT& Custom)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &Custom);
	return result;
}

void UserProperties::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x52, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften UserProperty 

/////////////////////////////////////////////////////////////////////////////
// Operationen UserProperty 

LPDISPATCH UserProperty::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long UserProperty::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH UserProperty::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH UserProperty::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString UserProperty::GetFormula()
{
	CString result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void UserProperty::SetFormula(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString UserProperty::GetName()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long UserProperty::GetType()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString UserProperty::GetValidationFormula()
{
	CString result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void UserProperty::SetValidationFormula(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString UserProperty::GetValidationText()
{
	CString result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void UserProperty::SetValidationText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT UserProperty::GetValue()
{
	VARIANT result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void UserProperty::SetValue(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void UserProperty::Delete()
{
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Recipients 

/////////////////////////////////////////////////////////////////////////////
// Operationen Recipients 

LPDISPATCH Recipients::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recipients::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recipients::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recipients::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Recipients::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Recipients::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH Recipients::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}

void Recipients::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

BOOL Recipients::ResolveAll()
{
	BOOL result;
	InvokeHelper(0x7e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _MailItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _MailItem 

LPDISPATCH _MailItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _MailItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _MailItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _MailItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MailItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _MailItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _MailItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _MailItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _MailItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _MailItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MailItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _MailItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _MailItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _MailItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MailItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _MailItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MailItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _MailItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _MailItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _MailItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _MailItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _MailItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

BOOL _MailItem::GetAlternateRecipientAllowed()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetAlternateRecipientAllowed(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _MailItem::GetAutoForwarded()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetAutoForwarded(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _MailItem::GetBcc()
{
	CString result;
	InvokeHelper(0xe02, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetBcc(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe02, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetCc()
{
	CString result;
	InvokeHelper(0xe03, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetCc(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe03, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _MailItem::GetDeferredDeliveryTime()
{
	DATE result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MailItem::SetDeferredDeliveryTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _MailItem::GetDeleteAfterSubmit()
{
	BOOL result;
	InvokeHelper(0xe01, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetDeleteAfterSubmit(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe01, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

DATE _MailItem::GetExpiryTime()
{
	DATE result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MailItem::SetExpiryTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

DATE _MailItem::GetFlagDueBy()
{
	DATE result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MailItem::SetFlagDueBy(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _MailItem::GetFlagRequest()
{
	CString result;
	InvokeHelper(0x8530, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetFlagRequest(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8530, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _MailItem::GetFlagStatus()
{
	long result;
	InvokeHelper(0x1090, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MailItem::SetFlagStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1090, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _MailItem::GetHTMLBody()
{
	CString result;
	InvokeHelper(0xf404, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetHTMLBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf404, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _MailItem::GetOriginatorDeliveryReportRequested()
{
	BOOL result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetOriginatorDeliveryReportRequested(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _MailItem::GetReadReceiptRequested()
{
	BOOL result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetReadReceiptRequested(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _MailItem::GetReceivedByEntryID()
{
	CString result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetReceivedByName()
{
	CString result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetReceivedOnBehalfOfEntryID()
{
	CString result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetReceivedOnBehalfOfName()
{
	CString result;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _MailItem::GetReceivedTime()
{
	DATE result;
	InvokeHelper(0xe06, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

BOOL _MailItem::GetRecipientReassignmentProhibited()
{
	BOOL result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetRecipientReassignmentProhibited(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _MailItem::GetRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf814, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _MailItem::GetReminderOverrideDefault()
{
	BOOL result;
	InvokeHelper(0x851c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetReminderOverrideDefault(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x851c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _MailItem::GetReminderPlaySound()
{
	BOOL result;
	InvokeHelper(0x851e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetReminderPlaySound(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x851e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _MailItem::GetReminderSet()
{
	BOOL result;
	InvokeHelper(0x8503, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MailItem::SetReminderSet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _MailItem::GetReminderSoundFile()
{
	CString result;
	InvokeHelper(0x851f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetReminderSoundFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x851f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _MailItem::GetReminderTime()
{
	DATE result;
	InvokeHelper(0x8502, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MailItem::SetReminderTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long _MailItem::GetRemoteStatus()
{
	long result;
	InvokeHelper(0x8511, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MailItem::SetRemoteStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8511, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _MailItem::GetReplyRecipientNames()
{
	CString result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetReplyRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf013, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::GetSaveSentMessageFolder()
{
	LPDISPATCH result;
	InvokeHelper(0xf401, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MailItem::SetRefSaveSentMessageFolder(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf401, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _MailItem::GetSenderName()
{
	CString result;
	InvokeHelper(0xc1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _MailItem::GetSent()
{
	BOOL result;
	InvokeHelper(0xf402, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

DATE _MailItem::GetSentOn()
{
	DATE result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetSentOnBehalfOfName()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetSentOnBehalfOfName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _MailItem::GetSubmitted()
{
	BOOL result;
	InvokeHelper(0xf403, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _MailItem::GetTo()
{
	CString result;
	InvokeHelper(0xe04, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetTo(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe04, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetVotingOptions()
{
	CString result;
	InvokeHelper(0xf01b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetVotingOptions(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf01b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MailItem::GetVotingResponse()
{
	CString result;
	InvokeHelper(0x8524, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MailItem::SetVotingResponse(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8524, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void _MailItem::ClearConversationIndex()
{
	InvokeHelper(0xf822, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _MailItem::Forward()
{
	LPDISPATCH result;
	InvokeHelper(0xf813, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::Reply()
{
	LPDISPATCH result;
	InvokeHelper(0xf810, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MailItem::ReplyAll()
{
	LPDISPATCH result;
	InvokeHelper(0xf811, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MailItem::Send()
{
	InvokeHelper(0xf075, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _MailItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Links 

/////////////////////////////////////////////////////////////////////////////
// Operationen Links 

LPDISPATCH Links::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Links::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Links::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Links::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Links::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Links::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH Links::Add(LPDISPATCH Item)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Item);
	return result;
}

void Links::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Link 

/////////////////////////////////////////////////////////////////////////////
// Operationen Link 

LPDISPATCH Link::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Link::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Link::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Link::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString Link::GetName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long Link::GetType()
{
	long result;
	InvokeHelper(0x2101, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Link::GetItem()
{
	LPDISPATCH result;
	InvokeHelper(0x2102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ItemEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen ItemEvents 

void ItemEvents::Open(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void ItemEvents::CustomAction(LPDISPATCH Action, LPDISPATCH Response, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Action, Response, Cancel);
}

void ItemEvents::CustomPropertyChange(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void ItemEvents::Forward(LPDISPATCH Forward, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf468, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Forward, Cancel);
}

void ItemEvents::Close(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void ItemEvents::PropertyChange(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void ItemEvents::Read()
{
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ItemEvents::Reply(LPDISPATCH Response, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf466, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Response, Cancel);
}

void ItemEvents::ReplyAll(LPDISPATCH Response, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf467, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Response, Cancel);
}

void ItemEvents::Send(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void ItemEvents::Write(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void ItemEvents::BeforeCheckNames(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf00a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void ItemEvents::AttachmentAdd(LPDISPATCH Attachment)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf00b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Attachment);
}

void ItemEvents::AttachmentRead(LPDISPATCH Attachment)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf00c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Attachment);
}

void ItemEvents::BeforeAttachmentSave(LPDISPATCH Attachment, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf00d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Attachment, Cancel);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften RecurrencePattern 

/////////////////////////////////////////////////////////////////////////////
// Operationen RecurrencePattern 

LPDISPATCH RecurrencePattern::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long RecurrencePattern::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH RecurrencePattern::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH RecurrencePattern::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long RecurrencePattern::GetDayOfMonth()
{
	long result;
	InvokeHelper(0x1000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetDayOfMonth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long RecurrencePattern::GetDayOfWeekMask()
{
	long result;
	InvokeHelper(0x1001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetDayOfWeekMask(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long RecurrencePattern::GetDuration()
{
	long result;
	InvokeHelper(0x100d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetDuration(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x100d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE RecurrencePattern::GetEndTime()
{
	DATE result;
	InvokeHelper(0x100c, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetEndTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x100c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH RecurrencePattern::GetExceptions()
{
	LPDISPATCH result;
	InvokeHelper(0x100e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long RecurrencePattern::GetInstance()
{
	long result;
	InvokeHelper(0x1003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetInstance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long RecurrencePattern::GetInterval()
{
	long result;
	InvokeHelper(0x1004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetInterval(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long RecurrencePattern::GetMonthOfYear()
{
	long result;
	InvokeHelper(0x1006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetMonthOfYear(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL RecurrencePattern::GetNoEndDate()
{
	BOOL result;
	InvokeHelper(0x100b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetNoEndDate(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x100b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long RecurrencePattern::GetOccurrences()
{
	long result;
	InvokeHelper(0x1005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetOccurrences(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE RecurrencePattern::GetPatternEndDate()
{
	DATE result;
	InvokeHelper(0x1002, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetPatternEndDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x1002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

DATE RecurrencePattern::GetPatternStartDate()
{
	DATE result;
	InvokeHelper(0x1008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetPatternStartDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x1008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long RecurrencePattern::GetRecurrenceType()
{
	long result;
	InvokeHelper(0x1007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetRecurrenceType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL RecurrencePattern::GetRegenerate()
{
	BOOL result;
	InvokeHelper(0x100a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetRegenerate(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x100a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

DATE RecurrencePattern::GetStartTime()
{
	DATE result;
	InvokeHelper(0x1009, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void RecurrencePattern::SetStartTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x1009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH RecurrencePattern::GetOccurrence(DATE StartDate)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x100f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		StartDate);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Exceptions 

/////////////////////////////////////////////////////////////////////////////
// Operationen Exceptions 

LPDISPATCH Exceptions::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Exceptions::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Exceptions::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Exceptions::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Exceptions::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Exceptions::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Exception 

/////////////////////////////////////////////////////////////////////////////
// Operationen Exception 

LPDISPATCH Exception::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Exception::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Exception::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Exception::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Exception::GetAppointmentItem()
{
	LPDISPATCH result;
	InvokeHelper(0x2001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL Exception::GetDeleted()
{
	BOOL result;
	InvokeHelper(0x2002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

DATE Exception::GetOriginalDate()
{
	DATE result;
	InvokeHelper(0x2000, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _MeetingItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _MeetingItem 

LPDISPATCH _MeetingItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _MeetingItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _MeetingItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MeetingItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MeetingItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MeetingItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MeetingItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _MeetingItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _MeetingItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _MeetingItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _MeetingItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _MeetingItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _MeetingItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _MeetingItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _MeetingItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _MeetingItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _MeetingItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _MeetingItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _MeetingItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _MeetingItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _MeetingItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _MeetingItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _MeetingItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MeetingItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _MeetingItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MeetingItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _MeetingItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _MeetingItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _MeetingItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _MeetingItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _MeetingItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

BOOL _MeetingItem::GetAutoForwarded()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetAutoForwarded(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

DATE _MeetingItem::GetDeferredDeliveryTime()
{
	DATE result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetDeferredDeliveryTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _MeetingItem::GetDeleteAfterSubmit()
{
	BOOL result;
	InvokeHelper(0xe01, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetDeleteAfterSubmit(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe01, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

DATE _MeetingItem::GetExpiryTime()
{
	DATE result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetExpiryTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

DATE _MeetingItem::GetFlagDueBy()
{
	DATE result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetFlagDueBy(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _MeetingItem::GetFlagRequest()
{
	CString result;
	InvokeHelper(0x8530, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetFlagRequest(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8530, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _MeetingItem::GetFlagStatus()
{
	long result;
	InvokeHelper(0x1090, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetFlagStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1090, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _MeetingItem::GetOriginatorDeliveryReportRequested()
{
	BOOL result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetOriginatorDeliveryReportRequested(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

DATE _MeetingItem::GetReceivedTime()
{
	DATE result;
	InvokeHelper(0xe06, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetReceivedTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0xe06, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _MeetingItem::GetRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf814, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL _MeetingItem::GetReminderSet()
{
	BOOL result;
	InvokeHelper(0x8503, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetReminderSet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

DATE _MeetingItem::GetReminderTime()
{
	DATE result;
	InvokeHelper(0x8502, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetReminderTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _MeetingItem::GetReplyRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf013, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetSaveSentMessageFolder()
{
	LPDISPATCH result;
	InvokeHelper(0xf401, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MeetingItem::SetRefSaveSentMessageFolder(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf401, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _MeetingItem::GetSenderName()
{
	CString result;
	InvokeHelper(0xc1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _MeetingItem::GetSent()
{
	BOOL result;
	InvokeHelper(0xf402, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

DATE _MeetingItem::GetSentOn()
{
	DATE result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

BOOL _MeetingItem::GetSubmitted()
{
	BOOL result;
	InvokeHelper(0xf403, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::Forward()
{
	LPDISPATCH result;
	InvokeHelper(0xf813, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::GetAssociatedAppointment(BOOL AddToCalendar)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf760, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		AddToCalendar);
	return result;
}

LPDISPATCH _MeetingItem::Reply()
{
	LPDISPATCH result;
	InvokeHelper(0xf810, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _MeetingItem::ReplyAll()
{
	LPDISPATCH result;
	InvokeHelper(0xf811, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _MeetingItem::Send()
{
	InvokeHelper(0xf075, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _MeetingItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _ContactItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _ContactItem 

LPDISPATCH _ContactItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _ContactItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _ContactItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _ContactItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _ContactItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _ContactItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _ContactItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _ContactItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _ContactItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _ContactItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _ContactItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _ContactItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _ContactItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _ContactItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _ContactItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ContactItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _ContactItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _ContactItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ContactItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ContactItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

CString _ContactItem::GetAccount()
{
	CString result;
	InvokeHelper(0x3a00, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetAccount(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a00, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _ContactItem::GetAnniversary()
{
	DATE result;
	InvokeHelper(0x3a41, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetAnniversary(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x3a41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _ContactItem::GetAssistantName()
{
	CString result;
	InvokeHelper(0x3a30, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetAssistantName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetAssistantTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a2e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetAssistantTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _ContactItem::GetBirthday()
{
	DATE result;
	InvokeHelper(0x3a42, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBirthday(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x3a42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _ContactItem::GetBusiness2TelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a1b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusiness2TelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddress()
{
	CString result;
	InvokeHelper(0x801b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x801b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddressCity()
{
	CString result;
	InvokeHelper(0x8046, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddressCity(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8046, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddressCountry()
{
	CString result;
	InvokeHelper(0x8049, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddressCountry(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8049, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddressPostalCode()
{
	CString result;
	InvokeHelper(0x8048, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddressPostalCode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8048, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddressPostOfficeBox()
{
	CString result;
	InvokeHelper(0x804a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddressPostOfficeBox(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x804a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddressState()
{
	CString result;
	InvokeHelper(0x8047, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddressState(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8047, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessAddressStreet()
{
	CString result;
	InvokeHelper(0x8045, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessAddressStreet(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8045, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessFaxNumber()
{
	CString result;
	InvokeHelper(0x3a24, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessFaxNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessHomePage()
{
	CString result;
	InvokeHelper(0x3a51, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessHomePage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetBusinessTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a08, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetBusinessTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a08, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCallbackTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a02, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCallbackTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a02, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCarTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCarTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetChildren()
{
	CString result;
	InvokeHelper(0x800c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetChildren(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x800c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCompanyAndFullName()
{
	CString result;
	InvokeHelper(0x8018, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetCompanyLastFirstNoSpace()
{
	CString result;
	InvokeHelper(0x8032, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetCompanyLastFirstSpaceOnly()
{
	CString result;
	InvokeHelper(0x8033, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetCompanyMainTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a57, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCompanyMainTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a57, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCompanyName()
{
	CString result;
	InvokeHelper(0x3a16, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCompanyName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetComputerNetworkName()
{
	CString result;
	InvokeHelper(0x3a49, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetComputerNetworkName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a49, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetCustomerID()
{
	CString result;
	InvokeHelper(0x3a4a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetCustomerID(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a4a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetDepartment()
{
	CString result;
	InvokeHelper(0x3a18, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetDepartment(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail1Address()
{
	CString result;
	InvokeHelper(0x8083, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetEmail1Address(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8083, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail1AddressType()
{
	CString result;
	InvokeHelper(0x8082, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetEmail1AddressType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8082, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail1DisplayName()
{
	CString result;
	InvokeHelper(0x8080, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetEmail1EntryID()
{
	CString result;
	InvokeHelper(0x8085, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetEmail2Address()
{
	CString result;
	InvokeHelper(0x8093, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetEmail2Address(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8093, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail2AddressType()
{
	CString result;
	InvokeHelper(0x8092, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetEmail2AddressType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8092, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail2DisplayName()
{
	CString result;
	InvokeHelper(0x8090, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetEmail2EntryID()
{
	CString result;
	InvokeHelper(0x8095, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetEmail3Address()
{
	CString result;
	InvokeHelper(0x80a3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetEmail3Address(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail3AddressType()
{
	CString result;
	InvokeHelper(0x80a2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetEmail3AddressType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetEmail3DisplayName()
{
	CString result;
	InvokeHelper(0x80a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetEmail3EntryID()
{
	CString result;
	InvokeHelper(0x80a5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetFileAs()
{
	CString result;
	InvokeHelper(0x8005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetFileAs(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetFirstName()
{
	CString result;
	InvokeHelper(0x3a06, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetFirstName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a06, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetFTPSite()
{
	CString result;
	InvokeHelper(0x3a4c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetFTPSite(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetFullName()
{
	CString result;
	InvokeHelper(0x3001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetFullName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetFullNameAndCompany()
{
	CString result;
	InvokeHelper(0x8019, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long _ContactItem::GetGender()
{
	long result;
	InvokeHelper(0x3a4d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetGender(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3a4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _ContactItem::GetGovernmentIDNumber()
{
	CString result;
	InvokeHelper(0x3a07, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetGovernmentIDNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a07, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHobby()
{
	CString result;
	InvokeHelper(0x3a43, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHobby(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHome2TelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a2f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHome2TelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddress()
{
	CString result;
	InvokeHelper(0x801a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x801a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddressCity()
{
	CString result;
	InvokeHelper(0x3a59, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddressCity(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a59, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddressCountry()
{
	CString result;
	InvokeHelper(0x3a5a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddressCountry(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a5a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddressPostalCode()
{
	CString result;
	InvokeHelper(0x3a5b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddressPostalCode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a5b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddressPostOfficeBox()
{
	CString result;
	InvokeHelper(0x3a5e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddressPostOfficeBox(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a5e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddressState()
{
	CString result;
	InvokeHelper(0x3a5c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddressState(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a5c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeAddressStreet()
{
	CString result;
	InvokeHelper(0x3a5d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeAddressStreet(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a5d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeFaxNumber()
{
	CString result;
	InvokeHelper(0x3a25, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeFaxNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetHomeTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a09, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetHomeTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a09, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetInitials()
{
	CString result;
	InvokeHelper(0x3a0a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetInitials(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a0a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetInternetFreeBusyAddress()
{
	CString result;
	InvokeHelper(0x80d8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetInternetFreeBusyAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x80d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetISDNNumber()
{
	CString result;
	InvokeHelper(0x3a2d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetISDNNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetJobTitle()
{
	CString result;
	InvokeHelper(0x3a17, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetJobTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _ContactItem::GetJournal()
{
	BOOL result;
	InvokeHelper(0x8025, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetJournal(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _ContactItem::GetLanguage()
{
	CString result;
	InvokeHelper(0x3a0c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetLanguage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a0c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetLastFirstAndSuffix()
{
	CString result;
	InvokeHelper(0x8036, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetLastFirstNoSpace()
{
	CString result;
	InvokeHelper(0x8030, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetLastFirstNoSpaceCompany()
{
	CString result;
	InvokeHelper(0x8034, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetLastFirstSpaceOnly()
{
	CString result;
	InvokeHelper(0x8031, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetLastFirstSpaceOnlyCompany()
{
	CString result;
	InvokeHelper(0x8035, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetLastName()
{
	CString result;
	InvokeHelper(0x3a11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetLastName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetLastNameAndFirstName()
{
	CString result;
	InvokeHelper(0x8017, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ContactItem::GetMailingAddress()
{
	CString result;
	InvokeHelper(0x3a15, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMailingAddressCity()
{
	CString result;
	InvokeHelper(0x3a27, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddressCity(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMailingAddressCountry()
{
	CString result;
	InvokeHelper(0x3a26, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddressCountry(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMailingAddressPostalCode()
{
	CString result;
	InvokeHelper(0x3a2a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddressPostalCode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMailingAddressPostOfficeBox()
{
	CString result;
	InvokeHelper(0x3a2b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddressPostOfficeBox(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMailingAddressState()
{
	CString result;
	InvokeHelper(0x3a28, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddressState(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMailingAddressStreet()
{
	CString result;
	InvokeHelper(0x3a29, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMailingAddressStreet(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetManagerName()
{
	CString result;
	InvokeHelper(0x3a4e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetManagerName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMiddleName()
{
	CString result;
	InvokeHelper(0x3a44, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMiddleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetMobileTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a1c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetMobileTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetNetMeetingAlias()
{
	CString result;
	InvokeHelper(0x805f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetNetMeetingAlias(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x805f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetNetMeetingServer()
{
	CString result;
	InvokeHelper(0x8060, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetNetMeetingServer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8060, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetNickName()
{
	CString result;
	InvokeHelper(0x3a4f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetNickName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOfficeLocation()
{
	CString result;
	InvokeHelper(0x3a19, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOfficeLocation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOrganizationalIDNumber()
{
	CString result;
	InvokeHelper(0x3a10, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOrganizationalIDNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddress()
{
	CString result;
	InvokeHelper(0x801c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x801c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddressCity()
{
	CString result;
	InvokeHelper(0x3a5f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddressCity(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a5f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddressCountry()
{
	CString result;
	InvokeHelper(0x3a60, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddressCountry(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a60, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddressPostalCode()
{
	CString result;
	InvokeHelper(0x3a61, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddressPostalCode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddressPostOfficeBox()
{
	CString result;
	InvokeHelper(0x3a64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddressPostOfficeBox(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddressState()
{
	CString result;
	InvokeHelper(0x3a62, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddressState(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherAddressStreet()
{
	CString result;
	InvokeHelper(0x3a63, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherAddressStreet(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherFaxNumber()
{
	CString result;
	InvokeHelper(0x3a23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherFaxNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetOtherTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a1f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetOtherTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetPagerNumber()
{
	CString result;
	InvokeHelper(0x3a21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetPagerNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetPersonalHomePage()
{
	CString result;
	InvokeHelper(0x3a50, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetPersonalHomePage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetPrimaryTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetPrimaryTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetProfession()
{
	CString result;
	InvokeHelper(0x3a46, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetProfession(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetRadioTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetRadioTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetReferredBy()
{
	CString result;
	InvokeHelper(0x3a47, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetReferredBy(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a47, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _ContactItem::GetSelectedMailingAddress()
{
	long result;
	InvokeHelper(0x8022, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetSelectedMailingAddress(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8022, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _ContactItem::GetSpouse()
{
	CString result;
	InvokeHelper(0x3a48, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetSpouse(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetSuffix()
{
	CString result;
	InvokeHelper(0x3a05, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a05, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetTelexNumber()
{
	CString result;
	InvokeHelper(0x3a2c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetTelexNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetTitle()
{
	CString result;
	InvokeHelper(0x3a45, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetTitle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetTTYTDDTelephoneNumber()
{
	CString result;
	InvokeHelper(0x3a4b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetTTYTDDTelephoneNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3a4b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetUser1()
{
	CString result;
	InvokeHelper(0x804f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetUser1(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x804f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetUser2()
{
	CString result;
	InvokeHelper(0x8050, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetUser2(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8050, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetUser3()
{
	CString result;
	InvokeHelper(0x8051, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetUser3(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8051, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetUser4()
{
	CString result;
	InvokeHelper(0x8052, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetUser4(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8052, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetUserCertificate()
{
	CString result;
	InvokeHelper(0x8016, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetUserCertificate(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetWebPage()
{
	CString result;
	InvokeHelper(0x802b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetWebPage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x802b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetYomiCompanyName()
{
	CString result;
	InvokeHelper(0x802e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetYomiCompanyName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x802e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetYomiFirstName()
{
	CString result;
	InvokeHelper(0x802c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetYomiFirstName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x802c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ContactItem::GetYomiLastName()
{
	CString result;
	InvokeHelper(0x802d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ContactItem::SetYomiLastName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x802d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _ContactItem::ForwardAsVcard()
{
	LPDISPATCH result;
	InvokeHelper(0xf8a1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ContactItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _DistListItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _DistListItem 

LPDISPATCH _DistListItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _DistListItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _DistListItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DistListItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DistListItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DistListItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DistListItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DistListItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _DistListItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _DistListItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _DistListItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _DistListItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _DistListItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DistListItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _DistListItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _DistListItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _DistListItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DistListItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _DistListItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _DistListItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _DistListItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _DistListItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _DistListItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DistListItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _DistListItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DistListItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DistListItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _DistListItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _DistListItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DistListItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DistListItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

CString _DistListItem::GetDLName()
{
	CString result;
	InvokeHelper(0x8053, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DistListItem::SetDLName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8053, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _DistListItem::GetMemberCount()
{
	long result;
	InvokeHelper(0x804b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DistListItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DistListItem::AddMembers(LPDISPATCH Recipients)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf900, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Recipients);
}

void _DistListItem::RemoveMembers(LPDISPATCH Recipients)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf901, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Recipients);
}

LPDISPATCH _DistListItem::GetMember(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf905, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _DocumentItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _DocumentItem 

LPDISPATCH _DocumentItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _DocumentItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _DocumentItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DocumentItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _DocumentItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _DocumentItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _DocumentItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _DocumentItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _DocumentItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _DocumentItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _DocumentItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _DocumentItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _DocumentItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _DocumentItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _DocumentItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _DocumentItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _DocumentItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _DocumentItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _DocumentItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DocumentItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _DocumentItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DocumentItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _DocumentItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DocumentItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _DocumentItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _DocumentItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _DocumentItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _DocumentItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ExplorersEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen ExplorersEvents 

void ExplorersEvents::NewExplorer(LPDISPATCH Explorer)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Explorer);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften FoldersEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen FoldersEvents 

void FoldersEvents::FolderAdd(LPDISPATCH Folder)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Folder);
}

void FoldersEvents::FolderChange(LPDISPATCH Folder)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Folder);
}

void FoldersEvents::FolderRemove()
{
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften InspectorsEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen InspectorsEvents 

void InspectorsEvents::NewInspector(LPDISPATCH Inspector)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Inspector);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ItemsEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen ItemsEvents 

void ItemsEvents::ItemAdd(LPDISPATCH Item)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Item);
}

void ItemsEvents::ItemChange(LPDISPATCH Item)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Item);
}

void ItemsEvents::ItemRemove()
{
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _JournalItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _JournalItem 

LPDISPATCH _JournalItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _JournalItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _JournalItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _JournalItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _JournalItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _JournalItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _JournalItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _JournalItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _JournalItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _JournalItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _JournalItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _JournalItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _JournalItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _JournalItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _JournalItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _JournalItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _JournalItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _JournalItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _JournalItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _JournalItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _JournalItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _JournalItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _JournalItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _JournalItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _JournalItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _JournalItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _JournalItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _JournalItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _JournalItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _JournalItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _JournalItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

CString _JournalItem::GetContactNames()
{
	CString result;
	InvokeHelper(0xe04, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetContactNames(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe04, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _JournalItem::GetDocPosted()
{
	BOOL result;
	InvokeHelper(0x8711, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetDocPosted(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8711, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _JournalItem::GetDocPrinted()
{
	BOOL result;
	InvokeHelper(0x870e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetDocPrinted(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x870e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _JournalItem::GetDocRouted()
{
	BOOL result;
	InvokeHelper(0x8710, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetDocRouted(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8710, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _JournalItem::GetDocSaved()
{
	BOOL result;
	InvokeHelper(0x870f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetDocSaved(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x870f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _JournalItem::GetDuration()
{
	long result;
	InvokeHelper(0x8707, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetDuration(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8707, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _JournalItem::GetEnd()
{
	DATE result;
	InvokeHelper(0x8708, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetEnd(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8708, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _JournalItem::GetType()
{
	CString result;
	InvokeHelper(0x8700, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetType(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8700, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH _JournalItem::GetRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf814, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

DATE _JournalItem::GetStart()
{
	DATE result;
	InvokeHelper(0x8706, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _JournalItem::SetStart(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8706, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH _JournalItem::Forward()
{
	LPDISPATCH result;
	InvokeHelper(0xf813, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::Reply()
{
	LPDISPATCH result;
	InvokeHelper(0xf810, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _JournalItem::ReplyAll()
{
	LPDISPATCH result;
	InvokeHelper(0xf811, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _JournalItem::StartTimer()
{
	InvokeHelper(0xf725, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _JournalItem::StopTimer()
{
	InvokeHelper(0xf726, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _JournalItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften NameSpaceEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen NameSpaceEvents 

void NameSpaceEvents::OptionsPagesAdd(LPDISPATCH Pages, LPDISPATCH Folder)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0xf005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Pages, Folder);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _NoteItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _NoteItem 

LPDISPATCH _NoteItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _NoteItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NoteItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NoteItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _NoteItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _NoteItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _NoteItem::GetColor()
{
	long result;
	InvokeHelper(0x8b00, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b00, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _NoteItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _NoteItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _NoteItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _NoteItem::GetHeight()
{
	long result;
	InvokeHelper(0x8b03, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b03, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _NoteItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

long _NoteItem::GetLeft()
{
	long result;
	InvokeHelper(0x8b04, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b04, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _NoteItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _NoteItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _NoteItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _NoteItem::GetSubject()
{
	CString result;
	InvokeHelper(0xf7a0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long _NoteItem::GetTop()
{
	long result;
	InvokeHelper(0x8b05, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b05, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _NoteItem::GetWidth()
{
	long result;
	InvokeHelper(0x8b02, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _NoteItem::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8b02, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void _NoteItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _NoteItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _NoteItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _NoteItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _NoteItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _NoteItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _NoteItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _NoteItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _NoteItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften OutlookBarGroup 

/////////////////////////////////////////////////////////////////////////////
// Operationen OutlookBarGroup 

LPDISPATCH OutlookBarGroup::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long OutlookBarGroup::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarGroup::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarGroup::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString OutlookBarGroup::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void OutlookBarGroup::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH OutlookBarGroup::GetShortcuts()
{
	LPDISPATCH result;
	InvokeHelper(0x2102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long OutlookBarGroup::GetViewType()
{
	long result;
	InvokeHelper(0x2103, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void OutlookBarGroup::SetViewType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2103, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _OutlookBarShortcuts 

/////////////////////////////////////////////////////////////////////////////
// Operationen _OutlookBarShortcuts 

LPDISPATCH _OutlookBarShortcuts::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _OutlookBarShortcuts::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarShortcuts::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarShortcuts::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _OutlookBarShortcuts::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarShortcuts::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH _OutlookBarShortcuts::Add(const VARIANT& Target, LPCTSTR Name, const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Target, Name, &Index);
	return result;
}

void _OutlookBarShortcuts::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften OutlookBarShortcut 

/////////////////////////////////////////////////////////////////////////////
// Operationen OutlookBarShortcut 

LPDISPATCH OutlookBarShortcut::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long OutlookBarShortcut::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarShortcut::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarShortcut::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString OutlookBarShortcut::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void OutlookBarShortcut::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT OutlookBarShortcut::GetTarget()
{
	VARIANT result;
	InvokeHelper(0x2100, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _OutlookBarGroups 

/////////////////////////////////////////////////////////////////////////////
// Operationen _OutlookBarGroups 

LPDISPATCH _OutlookBarGroups::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _OutlookBarGroups::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarGroups::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarGroups::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _OutlookBarGroups::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarGroups::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH _OutlookBarGroups::Add(LPCTSTR Name, const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &Index);
	return result;
}

void _OutlookBarGroups::Remove(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften OutlookBarGroupsEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen OutlookBarGroupsEvents 

void OutlookBarGroupsEvents::GroupAdd(LPDISPATCH NewGroup)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NewGroup);
}

void OutlookBarGroupsEvents::BeforeGroupAdd(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void OutlookBarGroupsEvents::BeforeGroupRemove(LPDISPATCH Group, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Group, Cancel);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _OutlookBarPane 

/////////////////////////////////////////////////////////////////////////////
// Operationen _OutlookBarPane 

LPDISPATCH _OutlookBarPane::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _OutlookBarPane::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarPane::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarPane::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarPane::GetContents()
{
	LPDISPATCH result;
	InvokeHelper(0x2100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _OutlookBarPane::GetCurrentGroup()
{
	LPDISPATCH result;
	InvokeHelper(0x2101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _OutlookBarPane::SetRefCurrentGroup(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2101, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _OutlookBarPane::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _OutlookBarPane::GetVisible()
{
	BOOL result;
	InvokeHelper(0x2103, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _OutlookBarPane::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2103, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften OutlookBarStorage 

/////////////////////////////////////////////////////////////////////////////
// Operationen OutlookBarStorage 

LPDISPATCH OutlookBarStorage::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long OutlookBarStorage::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarStorage::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarStorage::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH OutlookBarStorage::GetGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften OutlookBarPaneEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen OutlookBarPaneEvents 

void OutlookBarPaneEvents::BeforeNavigate(LPDISPATCH Shortcut, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Shortcut, Cancel);
}

void OutlookBarPaneEvents::BeforeGroupSwitch(LPDISPATCH ToGroup, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ToGroup, Cancel);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften OutlookBarShortcutsEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen OutlookBarShortcutsEvents 

void OutlookBarShortcutsEvents::ShortcutAdd(LPDISPATCH NewShortcut)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NewShortcut);
}

void OutlookBarShortcutsEvents::BeforeShortcutAdd(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0xf002, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void OutlookBarShortcutsEvents::BeforeShortcutRemove(LPDISPATCH Shortcut, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PBOOL;
	InvokeHelper(0xf003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Shortcut, Cancel);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften PropertyPageSite 

/////////////////////////////////////////////////////////////////////////////
// Operationen PropertyPageSite 

LPDISPATCH PropertyPageSite::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long PropertyPageSite::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH PropertyPageSite::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH PropertyPageSite::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void PropertyPageSite::OnStatusChange()
{
	InvokeHelper(0x2100, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften Pages 

/////////////////////////////////////////////////////////////////////////////
// Operationen Pages 

LPDISPATCH Pages::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Pages::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Pages::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Pages::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long Pages::GetCount()
{
	long result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH Pages::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

LPDISPATCH Pages::Add(const VARIANT& Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x12c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Name);
	return result;
}

void Pages::Remove(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _PostItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _PostItem 

LPDISPATCH _PostItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _PostItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _PostItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _PostItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _PostItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _PostItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _PostItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _PostItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _PostItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _PostItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _PostItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _PostItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _PostItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _PostItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _PostItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _PostItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _PostItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _PostItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _PostItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _PostItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _PostItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _PostItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _PostItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _PostItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _PostItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _PostItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _PostItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _PostItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _PostItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

DATE _PostItem::GetExpiryTime()
{
	DATE result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _PostItem::SetExpiryTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString _PostItem::GetHTMLBody()
{
	CString result;
	InvokeHelper(0xf404, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _PostItem::SetHTMLBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf404, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _PostItem::GetReceivedTime()
{
	DATE result;
	InvokeHelper(0xe06, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _PostItem::GetSenderName()
{
	CString result;
	InvokeHelper(0xc1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _PostItem::GetSentOn()
{
	DATE result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _PostItem::ClearConversationIndex()
{
	InvokeHelper(0xf822, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _PostItem::Forward()
{
	LPDISPATCH result;
	InvokeHelper(0xf813, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _PostItem::Post()
{
	InvokeHelper(0xf075, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _PostItem::Reply()
{
	LPDISPATCH result;
	InvokeHelper(0xf810, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _PostItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _RemoteItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _RemoteItem 

LPDISPATCH _RemoteItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _RemoteItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _RemoteItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _RemoteItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _RemoteItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _RemoteItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _RemoteItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _RemoteItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _RemoteItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _RemoteItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _RemoteItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _RemoteItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _RemoteItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _RemoteItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _RemoteItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _RemoteItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _RemoteItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _RemoteItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _RemoteItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _RemoteItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _RemoteItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _RemoteItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _RemoteItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _RemoteItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _RemoteItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _RemoteItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

BOOL _RemoteItem::GetHasAttachment()
{
	BOOL result;
	InvokeHelper(0x8f07, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _RemoteItem::GetRemoteMessageClass()
{
	CString result;
	InvokeHelper(0x8f02, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long _RemoteItem::GetTransferSize()
{
	long result;
	InvokeHelper(0x8f05, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _RemoteItem::GetTransferTime()
{
	long result;
	InvokeHelper(0x8f04, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _RemoteItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _ReportItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _ReportItem 

LPDISPATCH _ReportItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _ReportItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ReportItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ReportItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ReportItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ReportItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _ReportItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ReportItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ReportItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ReportItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ReportItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _ReportItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _ReportItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _ReportItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ReportItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _ReportItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _ReportItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _ReportItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _ReportItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _ReportItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _ReportItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _ReportItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _ReportItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _ReportItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _ReportItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _ReportItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _ReportItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _ReportItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _ReportItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _ReportItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _ReportItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _ReportItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _ReportItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ReportItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _ReportItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _ReportItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ReportItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ReportItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _ReportItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _TaskItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _TaskItem 

LPDISPATCH _TaskItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _TaskItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _TaskItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _TaskItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _TaskItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _TaskItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _TaskItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _TaskItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _TaskItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _TaskItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _TaskItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

long _TaskItem::GetActualWork()
{
	long result;
	InvokeHelper(0x8110, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetActualWork(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8110, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _TaskItem::GetCardData()
{
	CString result;
	InvokeHelper(0x812b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetCardData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x812b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskItem::GetComplete()
{
	BOOL result;
	InvokeHelper(0x811c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetComplete(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x811c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _TaskItem::GetContacts()
{
	CString result;
	InvokeHelper(0x853a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetContacts(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetContactNames()
{
	CString result;
	InvokeHelper(0x853c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetContactNames(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _TaskItem::GetDateCompleted()
{
	DATE result;
	InvokeHelper(0x810f, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetDateCompleted(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x810f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long _TaskItem::GetDelegationState()
{
	long result;
	InvokeHelper(0x812a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetDelegator()
{
	CString result;
	InvokeHelper(0x8121, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _TaskItem::GetDueDate()
{
	DATE result;
	InvokeHelper(0x8105, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetDueDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _TaskItem::GetIsRecurring()
{
	BOOL result;
	InvokeHelper(0xf617, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _TaskItem::GetOrdinal()
{
	long result;
	InvokeHelper(0x8123, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetOrdinal(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8123, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _TaskItem::GetOwner()
{
	CString result;
	InvokeHelper(0x811f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetOwner(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x811f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _TaskItem::GetOwnership()
{
	long result;
	InvokeHelper(0x8129, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long _TaskItem::GetPercentComplete()
{
	long result;
	InvokeHelper(0xf61f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetPercentComplete(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf61f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _TaskItem::GetRecipients()
{
	LPDISPATCH result;
	InvokeHelper(0xf814, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

DATE _TaskItem::GetReminderTime()
{
	DATE result;
	InvokeHelper(0x8502, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetReminderTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL _TaskItem::GetReminderOverrideDefault()
{
	BOOL result;
	InvokeHelper(0x851c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetReminderOverrideDefault(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x851c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _TaskItem::GetReminderPlaySound()
{
	BOOL result;
	InvokeHelper(0x851e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetReminderPlaySound(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x851e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL _TaskItem::GetReminderSet()
{
	BOOL result;
	InvokeHelper(0x8503, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetReminderSet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString _TaskItem::GetReminderSoundFile()
{
	CString result;
	InvokeHelper(0x851f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetReminderSoundFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x851f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long _TaskItem::GetResponseState()
{
	long result;
	InvokeHelper(0xf623, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskItem::GetRole()
{
	CString result;
	InvokeHelper(0x8127, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetRole(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8127, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetSchedulePlusPriority()
{
	CString result;
	InvokeHelper(0x812f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetSchedulePlusPriority(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x812f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

DATE _TaskItem::GetStartDate()
{
	DATE result;
	InvokeHelper(0x8104, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetStartDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x8104, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long _TaskItem::GetStatus()
{
	long result;
	InvokeHelper(0x8101, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetStatus(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8101, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString _TaskItem::GetStatusOnCompletionRecipients()
{
	CString result;
	InvokeHelper(0xe02, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetStatusOnCompletionRecipients(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe02, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskItem::GetStatusUpdateRecipients()
{
	CString result;
	InvokeHelper(0xe03, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetStatusUpdateRecipients(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe03, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskItem::GetTeamTask()
{
	BOOL result;
	InvokeHelper(0x8103, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetTeamTask(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8103, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _TaskItem::GetTotalWork()
{
	long result;
	InvokeHelper(0x8111, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskItem::SetTotalWork(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8111, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH _TaskItem::Assign()
{
	LPDISPATCH result;
	InvokeHelper(0xf620, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskItem::CancelResponseState()
{
	InvokeHelper(0xf622, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskItem::ClearRecurrencePattern()
{
	InvokeHelper(0xf0a5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _TaskItem::GetRecurrencePattern()
{
	LPDISPATCH result;
	InvokeHelper(0xf0a4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskItem::MarkComplete()
{
	InvokeHelper(0xf60d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH _TaskItem::Respond(long Response, const VARIANT& fNoUI, const VARIANT& fAdditionalTextDialog)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xf621, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Response, &fNoUI, &fAdditionalTextDialog);
	return result;
}

void _TaskItem::Send()
{
	InvokeHelper(0xf075, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL _TaskItem::SkipRecurrence()
{
	BOOL result;
	InvokeHelper(0xf624, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::StatusReport()
{
	LPDISPATCH result;
	InvokeHelper(0xf612, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _TaskRequestAcceptItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _TaskRequestAcceptItem 

LPDISPATCH _TaskRequestAcceptItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestAcceptItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _TaskRequestAcceptItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestAcceptItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestAcceptItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestAcceptItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestAcceptItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _TaskRequestAcceptItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _TaskRequestAcceptItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestAcceptItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestAcceptItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _TaskRequestAcceptItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestAcceptItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestAcceptItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestAcceptItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _TaskRequestAcceptItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestAcceptItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _TaskRequestAcceptItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _TaskRequestAcceptItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _TaskRequestAcceptItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestAcceptItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestAcceptItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _TaskRequestAcceptItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _TaskRequestAcceptItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestAcceptItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestAcceptItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _TaskRequestAcceptItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _TaskRequestAcceptItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestAcceptItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestAcceptItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _TaskRequestAcceptItem::GetAssociatedTask(BOOL AddToTaskList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf014, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		AddToTaskList);
	return result;
}

LPDISPATCH _TaskRequestAcceptItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _TaskRequestDeclineItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _TaskRequestDeclineItem 

LPDISPATCH _TaskRequestDeclineItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestDeclineItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _TaskRequestDeclineItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestDeclineItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestDeclineItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestDeclineItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestDeclineItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _TaskRequestDeclineItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _TaskRequestDeclineItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestDeclineItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestDeclineItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _TaskRequestDeclineItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestDeclineItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestDeclineItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestDeclineItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _TaskRequestDeclineItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestDeclineItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _TaskRequestDeclineItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _TaskRequestDeclineItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _TaskRequestDeclineItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestDeclineItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestDeclineItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _TaskRequestDeclineItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _TaskRequestDeclineItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestDeclineItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestDeclineItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _TaskRequestDeclineItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _TaskRequestDeclineItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestDeclineItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestDeclineItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _TaskRequestDeclineItem::GetAssociatedTask(BOOL AddToTaskList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf014, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		AddToTaskList);
	return result;
}

LPDISPATCH _TaskRequestDeclineItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _TaskRequestItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _TaskRequestItem 

LPDISPATCH _TaskRequestItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _TaskRequestItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _TaskRequestItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _TaskRequestItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _TaskRequestItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _TaskRequestItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _TaskRequestItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _TaskRequestItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _TaskRequestItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _TaskRequestItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _TaskRequestItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _TaskRequestItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _TaskRequestItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _TaskRequestItem::GetAssociatedTask(BOOL AddToTaskList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf014, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		AddToTaskList);
	return result;
}

LPDISPATCH _TaskRequestItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _TaskRequestUpdateItem 

/////////////////////////////////////////////////////////////////////////////
// Operationen _TaskRequestUpdateItem 

LPDISPATCH _TaskRequestUpdateItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xf000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestUpdateItem::GetClass()
{
	long result;
	InvokeHelper(0xf00a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetSession()
{
	LPDISPATCH result;
	InvokeHelper(0xf00b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xf001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetActions()
{
	LPDISPATCH result;
	InvokeHelper(0xf817, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetAttachments()
{
	LPDISPATCH result;
	InvokeHelper(0xf815, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString _TaskRequestUpdateItem::GetBillingInformation()
{
	CString result;
	InvokeHelper(0x8535, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetBillingInformation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8535, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestUpdateItem::GetBody()
{
	CString result;
	InvokeHelper(0x9100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetBody(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestUpdateItem::GetCategories()
{
	CString result;
	InvokeHelper(0x9001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetCategories(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestUpdateItem::GetCompanies()
{
	CString result;
	InvokeHelper(0x853b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetCompanies(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x853b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestUpdateItem::GetConversationIndex()
{
	CString result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _TaskRequestUpdateItem::GetConversationTopic()
{
	CString result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE _TaskRequestUpdateItem::GetCreationTime()
{
	DATE result;
	InvokeHelper(0x3007, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestUpdateItem::GetEntryID()
{
	CString result;
	InvokeHelper(0xf01e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetFormDescription()
{
	LPDISPATCH result;
	InvokeHelper(0xf095, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetGetInspector()
{
	LPDISPATCH result;
	InvokeHelper(0xf03e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long _TaskRequestUpdateItem::GetImportance()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetImportance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE _TaskRequestUpdateItem::GetLastModificationTime()
{
	DATE result;
	InvokeHelper(0x3008, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString _TaskRequestUpdateItem::GetMessageClass()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetMessageClass(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString _TaskRequestUpdateItem::GetMileage()
{
	CString result;
	InvokeHelper(0x8534, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetMileage(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8534, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestUpdateItem::GetNoAging()
{
	BOOL result;
	InvokeHelper(0x850e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetNoAging(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x850e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _TaskRequestUpdateItem::GetOutlookInternalVersion()
{
	long result;
	InvokeHelper(0x8552, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestUpdateItem::GetOutlookVersion()
{
	CString result;
	InvokeHelper(0x8554, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _TaskRequestUpdateItem::GetSaved()
{
	BOOL result;
	InvokeHelper(0xf0a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long _TaskRequestUpdateItem::GetSensitivity()
{
	long result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetSensitivity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _TaskRequestUpdateItem::GetSize()
{
	long result;
	InvokeHelper(0xe08, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString _TaskRequestUpdateItem::GetSubject()
{
	CString result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetSubject(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL _TaskRequestUpdateItem::GetUnRead()
{
	BOOL result;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::SetUnRead(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf01c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _TaskRequestUpdateItem::GetUserProperties()
{
	LPDISPATCH result;
	InvokeHelper(0xf816, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::Close(long SaveMode)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf023, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SaveMode);
}

LPDISPATCH _TaskRequestUpdateItem::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0xf032, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _TaskRequestUpdateItem::Delete()
{
	InvokeHelper(0xf04a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestUpdateItem::Display(const VARIANT& Modal)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf0a6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Modal);
}

LPDISPATCH _TaskRequestUpdateItem::Move(LPDISPATCH DestFldr)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf034, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		DestFldr);
	return result;
}

void _TaskRequestUpdateItem::PrintOut()
{
	InvokeHelper(0xf033, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestUpdateItem::Save()
{
	InvokeHelper(0xf048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _TaskRequestUpdateItem::SaveAs(LPCTSTR Path, const VARIANT& Type)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0xf051, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Path, &Type);
}

LPDISPATCH _TaskRequestUpdateItem::GetAssociatedTask(BOOL AddToTaskList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf014, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		AddToTaskList);
	return result;
}

LPDISPATCH _TaskRequestUpdateItem::GetLinks()
{
	LPDISPATCH result;
	InvokeHelper(0xf405, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _DRecipientControl 

/////////////////////////////////////////////////////////////////////////////
// Operationen _DRecipientControl 

BOOL _DRecipientControl::GetEnabled()
{
	BOOL result;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DRecipientControl::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long _DRecipientControl::GetBackColor()
{
	long result;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DRecipientControl::SetBackColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long _DRecipientControl::GetForeColor()
{
	long result;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DRecipientControl::SetForeColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL _DRecipientControl::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x8001f008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DRecipientControl::SetReadOnly(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8001f008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH _DRecipientControl::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void _DRecipientControl::SetFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long _DRecipientControl::GetSpecialEffect()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void _DRecipientControl::SetSpecialEffect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _DRecipientControlEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen _DRecipientControlEvents 


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _DDocSiteControl 

/////////////////////////////////////////////////////////////////////////////
// Operationen _DDocSiteControl 

BOOL _DDocSiteControl::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x8001f008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void _DDocSiteControl::SetReadOnly(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8001f008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _DDocSiteControlEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen _DDocSiteControlEvents 
