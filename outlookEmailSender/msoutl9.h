// Von Klassen-Assistent automatisch erstellte IDispatch-Kapselungsklasse(n). 
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Action 

class Action : public COleDispatchDriver
{
public:
	Action() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Action(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Action(const Action& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCopyLike();
	void SetCopyLike(long nNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetPrefix();
	void SetPrefix(LPCTSTR lpszNewValue);
	long GetReplyStyle();
	void SetReplyStyle(long nNewValue);
	long GetResponseStyle();
	void SetResponseStyle(long nNewValue);
	long GetShowOn();
	void SetShowOn(long nNewValue);
	void Delete();
	LPDISPATCH Execute();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Application 

class _Application : public COleDispatchDriver
{
public:
	_Application() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetAssistant();
	CString GetName();
	CString GetVersion();
	LPDISPATCH ActiveExplorer();
	LPDISPATCH ActiveInspector();
	LPDISPATCH CreateItem(long ItemType);
	LPDISPATCH CreateItemFromTemplate(LPCTSTR TemplatePath, const VARIANT& InFolder);
	LPDISPATCH CreateObject(LPCTSTR ObjectName);
	LPDISPATCH GetNamespace(LPCTSTR Type);
	void Quit();
	LPDISPATCH GetCOMAddIns();
	LPDISPATCH GetExplorers();
	LPDISPATCH GetInspectors();
	LPDISPATCH GetLanguageSettings();
	CString GetProductCode();
	LPDISPATCH GetAnswerWizard();
	LPDISPATCH ActiveWindow();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _NameSpace 

class _NameSpace : public COleDispatchDriver
{
public:
	_NameSpace() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_NameSpace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_NameSpace(const _NameSpace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetCurrentUser();
	LPDISPATCH GetFolders();
	CString GetType();
	LPDISPATCH GetAddressLists();
	LPDISPATCH CreateRecipient(LPCTSTR RecipientName);
	LPDISPATCH GetDefaultFolder(long FolderType);
	LPDISPATCH GetFolderFromID(LPCTSTR EntryIDFolder, const VARIANT& EntryIDStore);
	LPDISPATCH GetItemFromID(LPCTSTR EntryIDItem, const VARIANT& EntryIDStore);
	LPDISPATCH GetRecipientFromID(LPCTSTR EntryID);
	LPDISPATCH GetSharedDefaultFolder(LPDISPATCH Recipient, long FolderType);
	void Logoff();
	void Logon(const VARIANT& Profile, const VARIANT& Password, const VARIANT& ShowDialog, const VARIANT& NewSession);
	LPDISPATCH PickFolder();
	LPDISPATCH GetSyncObjects();
	void AddStore(const VARIANT& Store);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Recipient 

class Recipient : public COleDispatchDriver
{
public:
	Recipient() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Recipient(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Recipient(const Recipient& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetAddress();
	LPDISPATCH GetAddressEntry();
	void SetRefAddressEntry(LPDISPATCH newValue);
	CString GetAutoResponse();
	void SetAutoResponse(LPCTSTR lpszNewValue);
	long GetDisplayType();
	CString GetEntryID();
	long GetIndex();
	long GetMeetingResponseStatus();
	CString GetName();
	BOOL GetResolved();
	long GetTrackingStatus();
	void SetTrackingStatus(long nNewValue);
	DATE GetTrackingStatusTime();
	void SetTrackingStatusTime(DATE newValue);
	long GetType();
	void SetType(long nNewValue);
	void Delete();
	CString FreeBusy(DATE Start, long MinPerChar, const VARIANT& CompleteFormat);
	BOOL Resolve();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse AddressEntry 

class AddressEntry : public COleDispatchDriver
{
public:
	AddressEntry() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	AddressEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddressEntry(const AddressEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetAddress();
	void SetAddress(LPCTSTR lpszNewValue);
	long GetDisplayType();
	CString GetId();
	LPDISPATCH GetManager();
	LPDISPATCH GetMembers();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetType();
	void SetType(LPCTSTR lpszNewValue);
	void Delete();
	void Details(const VARIANT& HWnd);
	CString GetFreeBusy(DATE Start, long MinPerChar, const VARIANT& CompleteFormat);
	void Update(const VARIANT& MakePermanent, const VARIANT& Refresh);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse AddressEntries 

class AddressEntries : public COleDispatchDriver
{
public:
	AddressEntries() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	AddressEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddressEntries(const AddressEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPCTSTR Type, const VARIANT& Name, const VARIANT& Address);
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Sort(const VARIANT& Property_, const VARIANT& Order);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Folders 

class _Folders : public COleDispatchDriver
{
public:
	_Folders() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Folders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Folders(const _Folders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPCTSTR Name, const VARIANT& Type);
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Remove(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse MAPIFolder 

class MAPIFolder : public COleDispatchDriver
{
public:
	MAPIFolder() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	MAPIFolder(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MAPIFolder(const MAPIFolder& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetDefaultItemType();
	CString GetDefaultMessageClass();
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
	CString GetEntryID();
	LPDISPATCH GetFolders();
	LPDISPATCH GetItems();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetStoreID();
	long GetUnReadItemCount();
	LPDISPATCH CopyTo(LPDISPATCH DestinationFolder);
	void Delete();
	void Display();
	LPDISPATCH GetExplorer(const VARIANT& DisplayMode);
	void MoveTo(LPDISPATCH DestinationFolder);
	BOOL GetWebViewOn();
	void SetWebViewOn(BOOL bNewValue);
	CString GetWebViewURL();
	void SetWebViewURL(LPCTSTR lpszNewValue);
	BOOL GetWebViewAllowNavigation();
	void SetWebViewAllowNavigation(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Items 

class _Items : public COleDispatchDriver
{
public:
	_Items() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Items(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Items(const _Items& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	BOOL GetIncludeRecurrences();
	void SetIncludeRecurrences(BOOL bNewValue);
	LPDISPATCH Add(const VARIANT& Type);
	LPDISPATCH Find(LPCTSTR Filter);
	LPDISPATCH FindNext();
	LPDISPATCH GetFirst();
	LPDISPATCH GetLast();
	LPDISPATCH GetNext();
	LPDISPATCH GetPrevious();
	void Remove(long Index);
	void ResetColumns();
	LPDISPATCH Restrict(LPCTSTR Filter);
	void SetColumns(LPCTSTR Columns);
	void Sort(LPCTSTR Property_, const VARIANT& Descending);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Explorer 

class _Explorer : public COleDispatchDriver
{
public:
	_Explorer() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Explorer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Explorer(const _Explorer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetCurrentFolder();
	void SetRefCurrentFolder(LPDISPATCH newValue);
	void Close();
	void Display();
	CString GetCaption();
	VARIANT GetCurrentView();
	void SetCurrentView(const VARIANT& newValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	LPDISPATCH GetPanes();
	LPDISPATCH GetSelection();
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	void Activate();
	BOOL IsPaneVisible(long Pane);
	void ShowPane(long Pane, BOOL Visible);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Panes 

class Panes : public COleDispatchDriver
{
public:
	Panes() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Panes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Panes(const Panes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Selection 

class Selection : public COleDispatchDriver
{
public:
	Selection() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Selection(const Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse AddressLists 

class AddressLists : public COleDispatchDriver
{
public:
	AddressLists() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	AddressLists(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddressLists(const AddressLists& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse AddressList 

class AddressList : public COleDispatchDriver
{
public:
	AddressList() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	AddressList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddressList(const AddressList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetAddressEntries();
	CString GetId();
	long GetIndex();
	BOOL GetIsReadOnly();
	CString GetName();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse SyncObjects 

class SyncObjects : public COleDispatchDriver
{
public:
	SyncObjects() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	SyncObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SyncObjects(const SyncObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _SyncObject 

class _SyncObject : public COleDispatchDriver
{
public:
	_SyncObject() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_SyncObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_SyncObject(const _SyncObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetName();
	void Start();
	void Stop();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse SyncObjectEvents 

class SyncObjectEvents : public COleDispatchDriver
{
public:
	SyncObjectEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	SyncObjectEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SyncObjectEvents(const SyncObjectEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void SyncStart();
	void Progress(long State, LPCTSTR Description, long Value, long Max);
	void OnError(long Code, LPCTSTR Description);
	void SyncEnd();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Inspector 

class _Inspector : public COleDispatchDriver
{
public:
	_Inspector() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Inspector(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Inspector(const _Inspector& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetCurrentItem();
	long GetEditorType();
	LPDISPATCH GetModifiedFormPages();
	void Close(long SaveMode);
	void Display(const VARIANT& Modal);
	void HideFormPage(LPCTSTR PageName);
	BOOL IsWordMail();
	void SetCurrentFormPage(LPCTSTR PageName);
	void ShowFormPage(LPCTSTR PageName);
	LPDISPATCH GetHTMLEditor();
	LPDISPATCH GetWordEditor();
	CString GetCaption();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	void Activate();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Explorers 

class _Explorers : public COleDispatchDriver
{
public:
	_Explorers() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Explorers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Explorers(const _Explorers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(const VARIANT& Folder, long DisplayMode);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ExplorerEvents 

class ExplorerEvents : public COleDispatchDriver
{
public:
	ExplorerEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ExplorerEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ExplorerEvents(const ExplorerEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void Activate();
	void FolderSwitch();
	void BeforeFolderSwitch(LPDISPATCH NewFolder, BOOL* Cancel);
	void ViewSwitch();
	void BeforeViewSwitch(const VARIANT& NewView, BOOL* Cancel);
	void Deactivate();
	void SelectionChange();
	void Close();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _Inspectors 

class _Inspectors : public COleDispatchDriver
{
public:
	_Inspectors() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_Inspectors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Inspectors(const _Inspectors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPDISPATCH Item);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse InspectorEvents 

class InspectorEvents : public COleDispatchDriver
{
public:
	InspectorEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	InspectorEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	InspectorEvents(const InspectorEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void Activate();
	void Deactivate();
	void Close();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Actions 

class Actions : public COleDispatchDriver
{
public:
	Actions() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Actions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Actions(const Actions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add();
	void Remove(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ApplicationEvents 

class ApplicationEvents : public COleDispatchDriver
{
public:
	ApplicationEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ApplicationEvents(const ApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void ItemSend(LPDISPATCH Item, BOOL* Cancel);
	void NewMail();
	void Reminder(LPDISPATCH Item);
	void OptionsPagesAdd(LPDISPATCH Pages);
	void Startup();
	void Quit();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse PropertyPages 

class PropertyPages : public COleDispatchDriver
{
public:
	PropertyPages() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	PropertyPages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PropertyPages(const PropertyPages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	void Add(const VARIANT& Page, LPCTSTR Title);
	void Remove(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _AppointmentItem 

class _AppointmentItem : public COleDispatchDriver
{
public:
	_AppointmentItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_AppointmentItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_AppointmentItem(const _AppointmentItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	BOOL GetAllDayEvent();
	void SetAllDayEvent(BOOL bNewValue);
	long GetBusyStatus();
	void SetBusyStatus(long nNewValue);
	long GetDuration();
	void SetDuration(long nNewValue);
	DATE GetEnd();
	void SetEnd(DATE newValue);
	BOOL GetIsOnlineMeeting();
	void SetIsOnlineMeeting(BOOL bNewValue);
	BOOL GetIsRecurring();
	CString GetLocation();
	void SetLocation(LPCTSTR lpszNewValue);
	long GetMeetingStatus();
	void SetMeetingStatus(long nNewValue);
	BOOL GetNetMeetingAutoStart();
	void SetNetMeetingAutoStart(BOOL bNewValue);
	CString GetNetMeetingOrganizerAlias();
	void SetNetMeetingOrganizerAlias(LPCTSTR lpszNewValue);
	CString GetNetMeetingServer();
	void SetNetMeetingServer(LPCTSTR lpszNewValue);
	long GetNetMeetingType();
	void SetNetMeetingType(long nNewValue);
	CString GetOptionalAttendees();
	void SetOptionalAttendees(LPCTSTR lpszNewValue);
	CString GetOrganizer();
	LPDISPATCH GetRecipients();
	long GetRecurrenceState();
	long GetReminderMinutesBeforeStart();
	void SetReminderMinutesBeforeStart(long nNewValue);
	BOOL GetReminderOverrideDefault();
	void SetReminderOverrideDefault(BOOL bNewValue);
	BOOL GetReminderPlaySound();
	void SetReminderPlaySound(BOOL bNewValue);
	BOOL GetReminderSet();
	void SetReminderSet(BOOL bNewValue);
	CString GetReminderSoundFile();
	void SetReminderSoundFile(LPCTSTR lpszNewValue);
	DATE GetReplyTime();
	void SetReplyTime(DATE newValue);
	CString GetRequiredAttendees();
	void SetRequiredAttendees(LPCTSTR lpszNewValue);
	CString GetResources();
	void SetResources(LPCTSTR lpszNewValue);
	BOOL GetResponseRequested();
	void SetResponseRequested(BOOL bNewValue);
	long GetResponseStatus();
	DATE GetStart();
	void SetStart(DATE newValue);
	void ClearRecurrencePattern();
	LPDISPATCH ForwardAsVcal();
	LPDISPATCH GetRecurrencePattern();
	LPDISPATCH Respond(long Response, const VARIANT& fNoUI, const VARIANT& fAdditionalTextDialog);
	void Send();
	CString GetNetMeetingDocPathName();
	void SetNetMeetingDocPathName(LPCTSTR lpszNewValue);
	CString GetNetShowURL();
	void SetNetShowURL(LPCTSTR lpszNewValue);
	LPDISPATCH GetLinks();
	BOOL GetConferenceServerAllowExternal();
	void SetConferenceServerAllowExternal(BOOL bNewValue);
	CString GetConferenceServerPassword();
	void SetConferenceServerPassword(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Attachments 

class Attachments : public COleDispatchDriver
{
public:
	Attachments() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Attachments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Attachments(const Attachments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(const VARIANT& Source, const VARIANT& Type, const VARIANT& Position, const VARIANT& DisplayName);
	void Remove(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Attachment 

class Attachment : public COleDispatchDriver
{
public:
	Attachment() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Attachment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Attachment(const Attachment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetDisplayName();
	void SetDisplayName(LPCTSTR lpszNewValue);
	CString GetFileName();
	long GetIndex();
	CString GetPathName();
	long GetPosition();
	void SetPosition(long nNewValue);
	long GetType();
	void Delete();
	void SaveAsFile(LPCTSTR Path);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse FormDescription 

class FormDescription : public COleDispatchDriver
{
public:
	FormDescription() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	FormDescription(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FormDescription(const FormDescription& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetCategory();
	void SetCategory(LPCTSTR lpszNewValue);
	CString GetCategorySub();
	void SetCategorySub(LPCTSTR lpszNewValue);
	CString GetComment();
	void SetComment(LPCTSTR lpszNewValue);
	CString GetContactName();
	void SetContactName(LPCTSTR lpszNewValue);
	CString GetDisplayName();
	void SetDisplayName(LPCTSTR lpszNewValue);
	BOOL GetHidden();
	void SetHidden(BOOL bNewValue);
	CString GetIcon();
	void SetIcon(LPCTSTR lpszNewValue);
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	CString GetMessageClass();
	CString GetMiniIcon();
	void SetMiniIcon(LPCTSTR lpszNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetNumber();
	void SetNumber(LPCTSTR lpszNewValue);
	BOOL GetOneOff();
	void SetOneOff(BOOL bNewValue);
	CString GetPassword();
	void SetPassword(LPCTSTR lpszNewValue);
	CString GetScriptText();
	CString GetTemplate();
	void SetTemplate(LPCTSTR lpszNewValue);
	BOOL GetUseWordMail();
	void SetUseWordMail(BOOL bNewValue);
	CString GetVersion();
	void SetVersion(LPCTSTR lpszNewValue);
	void PublishForm(long Registry, const VARIANT& Folder);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse UserProperties 

class UserProperties : public COleDispatchDriver
{
public:
	UserProperties() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	UserProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	UserProperties(const UserProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPCTSTR Name, long Type, const VARIANT& AddToFolderFields, const VARIANT& DisplayFormat);
	LPDISPATCH Find(LPCTSTR Name, const VARIANT& Custom);
	void Remove(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse UserProperty 

class UserProperty : public COleDispatchDriver
{
public:
	UserProperty() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	UserProperty(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	UserProperty(const UserProperty& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetFormula();
	void SetFormula(LPCTSTR lpszNewValue);
	CString GetName();
	long GetType();
	CString GetValidationFormula();
	void SetValidationFormula(LPCTSTR lpszNewValue);
	CString GetValidationText();
	void SetValidationText(LPCTSTR lpszNewValue);
	VARIANT GetValue();
	void SetValue(const VARIANT& newValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Recipients 

class Recipients : public COleDispatchDriver
{
public:
	Recipients() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Recipients(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Recipients(const Recipients& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPCTSTR Name);
	void Remove(long Index);
	BOOL ResolveAll();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _MailItem 

class _MailItem : public COleDispatchDriver
{
public:
	_MailItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_MailItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_MailItem(const _MailItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	BOOL GetAlternateRecipientAllowed();
	void SetAlternateRecipientAllowed(BOOL bNewValue);
	BOOL GetAutoForwarded();
	void SetAutoForwarded(BOOL bNewValue);
	CString GetBcc();
	void SetBcc(LPCTSTR lpszNewValue);
	CString GetCc();
	void SetCc(LPCTSTR lpszNewValue);
	DATE GetDeferredDeliveryTime();
	void SetDeferredDeliveryTime(DATE newValue);
	BOOL GetDeleteAfterSubmit();
	void SetDeleteAfterSubmit(BOOL bNewValue);
	DATE GetExpiryTime();
	void SetExpiryTime(DATE newValue);
	DATE GetFlagDueBy();
	void SetFlagDueBy(DATE newValue);
	CString GetFlagRequest();
	void SetFlagRequest(LPCTSTR lpszNewValue);
	long GetFlagStatus();
	void SetFlagStatus(long nNewValue);
	CString GetHTMLBody();
	void SetHTMLBody(LPCTSTR lpszNewValue);
	BOOL GetOriginatorDeliveryReportRequested();
	void SetOriginatorDeliveryReportRequested(BOOL bNewValue);
	BOOL GetReadReceiptRequested();
	void SetReadReceiptRequested(BOOL bNewValue);
	CString GetReceivedByEntryID();
	CString GetReceivedByName();
	CString GetReceivedOnBehalfOfEntryID();
	CString GetReceivedOnBehalfOfName();
	DATE GetReceivedTime();
	BOOL GetRecipientReassignmentProhibited();
	void SetRecipientReassignmentProhibited(BOOL bNewValue);
	LPDISPATCH GetRecipients();
	BOOL GetReminderOverrideDefault();
	void SetReminderOverrideDefault(BOOL bNewValue);
	BOOL GetReminderPlaySound();
	void SetReminderPlaySound(BOOL bNewValue);
	BOOL GetReminderSet();
	void SetReminderSet(BOOL bNewValue);
	CString GetReminderSoundFile();
	void SetReminderSoundFile(LPCTSTR lpszNewValue);
	DATE GetReminderTime();
	void SetReminderTime(DATE newValue);
	long GetRemoteStatus();
	void SetRemoteStatus(long nNewValue);
	CString GetReplyRecipientNames();
	LPDISPATCH GetReplyRecipients();
	LPDISPATCH GetSaveSentMessageFolder();
	void SetRefSaveSentMessageFolder(LPDISPATCH newValue);
	CString GetSenderName();
	BOOL GetSent();
	DATE GetSentOn();
	CString GetSentOnBehalfOfName();
	void SetSentOnBehalfOfName(LPCTSTR lpszNewValue);
	BOOL GetSubmitted();
	CString GetTo();
	void SetTo(LPCTSTR lpszNewValue);
	CString GetVotingOptions();
	void SetVotingOptions(LPCTSTR lpszNewValue);
	CString GetVotingResponse();
	void SetVotingResponse(LPCTSTR lpszNewValue);
	void ClearConversationIndex();
	LPDISPATCH Forward();
	LPDISPATCH Reply();
	LPDISPATCH ReplyAll();
	void Send();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Links 

class Links : public COleDispatchDriver
{
public:
	Links() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Links(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Links(const Links& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPDISPATCH Item);
	void Remove(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Link 

class Link : public COleDispatchDriver
{
public:
	Link() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Link(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Link(const Link& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetName();
	long GetType();
	LPDISPATCH GetItem();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ItemEvents 

class ItemEvents : public COleDispatchDriver
{
public:
	ItemEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ItemEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ItemEvents(const ItemEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void Open(BOOL* Cancel);
	void CustomAction(LPDISPATCH Action, LPDISPATCH Response, BOOL* Cancel);
	void CustomPropertyChange(LPCTSTR Name);
	void Forward(LPDISPATCH Forward, BOOL* Cancel);
	void Close(BOOL* Cancel);
	void PropertyChange(LPCTSTR Name);
	void Read();
	void Reply(LPDISPATCH Response, BOOL* Cancel);
	void ReplyAll(LPDISPATCH Response, BOOL* Cancel);
	void Send(BOOL* Cancel);
	void Write(BOOL* Cancel);
	void BeforeCheckNames(BOOL* Cancel);
	void AttachmentAdd(LPDISPATCH Attachment);
	void AttachmentRead(LPDISPATCH Attachment);
	void BeforeAttachmentSave(LPDISPATCH Attachment, BOOL* Cancel);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse RecurrencePattern 

class RecurrencePattern : public COleDispatchDriver
{
public:
	RecurrencePattern() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	RecurrencePattern(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RecurrencePattern(const RecurrencePattern& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetDayOfMonth();
	void SetDayOfMonth(long nNewValue);
	long GetDayOfWeekMask();
	void SetDayOfWeekMask(long nNewValue);
	long GetDuration();
	void SetDuration(long nNewValue);
	DATE GetEndTime();
	void SetEndTime(DATE newValue);
	LPDISPATCH GetExceptions();
	long GetInstance();
	void SetInstance(long nNewValue);
	long GetInterval();
	void SetInterval(long nNewValue);
	long GetMonthOfYear();
	void SetMonthOfYear(long nNewValue);
	BOOL GetNoEndDate();
	void SetNoEndDate(BOOL bNewValue);
	long GetOccurrences();
	void SetOccurrences(long nNewValue);
	DATE GetPatternEndDate();
	void SetPatternEndDate(DATE newValue);
	DATE GetPatternStartDate();
	void SetPatternStartDate(DATE newValue);
	long GetRecurrenceType();
	void SetRecurrenceType(long nNewValue);
	BOOL GetRegenerate();
	void SetRegenerate(BOOL bNewValue);
	DATE GetStartTime();
	void SetStartTime(DATE newValue);
	LPDISPATCH GetOccurrence(DATE StartDate);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Exceptions 

class Exceptions : public COleDispatchDriver
{
public:
	Exceptions() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Exceptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Exceptions(const Exceptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Exception 

class Exception : public COleDispatchDriver
{
public:
	Exception() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Exception(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Exception(const Exception& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetAppointmentItem();
	BOOL GetDeleted();
	DATE GetOriginalDate();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _MeetingItem 

class _MeetingItem : public COleDispatchDriver
{
public:
	_MeetingItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_MeetingItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_MeetingItem(const _MeetingItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	BOOL GetAutoForwarded();
	void SetAutoForwarded(BOOL bNewValue);
	DATE GetDeferredDeliveryTime();
	void SetDeferredDeliveryTime(DATE newValue);
	BOOL GetDeleteAfterSubmit();
	void SetDeleteAfterSubmit(BOOL bNewValue);
	DATE GetExpiryTime();
	void SetExpiryTime(DATE newValue);
	DATE GetFlagDueBy();
	void SetFlagDueBy(DATE newValue);
	CString GetFlagRequest();
	void SetFlagRequest(LPCTSTR lpszNewValue);
	long GetFlagStatus();
	void SetFlagStatus(long nNewValue);
	BOOL GetOriginatorDeliveryReportRequested();
	void SetOriginatorDeliveryReportRequested(BOOL bNewValue);
	DATE GetReceivedTime();
	void SetReceivedTime(DATE newValue);
	LPDISPATCH GetRecipients();
	BOOL GetReminderSet();
	void SetReminderSet(BOOL bNewValue);
	DATE GetReminderTime();
	void SetReminderTime(DATE newValue);
	LPDISPATCH GetReplyRecipients();
	LPDISPATCH GetSaveSentMessageFolder();
	void SetRefSaveSentMessageFolder(LPDISPATCH newValue);
	CString GetSenderName();
	BOOL GetSent();
	DATE GetSentOn();
	BOOL GetSubmitted();
	LPDISPATCH Forward();
	LPDISPATCH GetAssociatedAppointment(BOOL AddToCalendar);
	LPDISPATCH Reply();
	LPDISPATCH ReplyAll();
	void Send();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _ContactItem 

class _ContactItem : public COleDispatchDriver
{
public:
	_ContactItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_ContactItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ContactItem(const _ContactItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	CString GetAccount();
	void SetAccount(LPCTSTR lpszNewValue);
	DATE GetAnniversary();
	void SetAnniversary(DATE newValue);
	CString GetAssistantName();
	void SetAssistantName(LPCTSTR lpszNewValue);
	CString GetAssistantTelephoneNumber();
	void SetAssistantTelephoneNumber(LPCTSTR lpszNewValue);
	DATE GetBirthday();
	void SetBirthday(DATE newValue);
	CString GetBusiness2TelephoneNumber();
	void SetBusiness2TelephoneNumber(LPCTSTR lpszNewValue);
	CString GetBusinessAddress();
	void SetBusinessAddress(LPCTSTR lpszNewValue);
	CString GetBusinessAddressCity();
	void SetBusinessAddressCity(LPCTSTR lpszNewValue);
	CString GetBusinessAddressCountry();
	void SetBusinessAddressCountry(LPCTSTR lpszNewValue);
	CString GetBusinessAddressPostalCode();
	void SetBusinessAddressPostalCode(LPCTSTR lpszNewValue);
	CString GetBusinessAddressPostOfficeBox();
	void SetBusinessAddressPostOfficeBox(LPCTSTR lpszNewValue);
	CString GetBusinessAddressState();
	void SetBusinessAddressState(LPCTSTR lpszNewValue);
	CString GetBusinessAddressStreet();
	void SetBusinessAddressStreet(LPCTSTR lpszNewValue);
	CString GetBusinessFaxNumber();
	void SetBusinessFaxNumber(LPCTSTR lpszNewValue);
	CString GetBusinessHomePage();
	void SetBusinessHomePage(LPCTSTR lpszNewValue);
	CString GetBusinessTelephoneNumber();
	void SetBusinessTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetCallbackTelephoneNumber();
	void SetCallbackTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetCarTelephoneNumber();
	void SetCarTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetChildren();
	void SetChildren(LPCTSTR lpszNewValue);
	CString GetCompanyAndFullName();
	CString GetCompanyLastFirstNoSpace();
	CString GetCompanyLastFirstSpaceOnly();
	CString GetCompanyMainTelephoneNumber();
	void SetCompanyMainTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetCompanyName();
	void SetCompanyName(LPCTSTR lpszNewValue);
	CString GetComputerNetworkName();
	void SetComputerNetworkName(LPCTSTR lpszNewValue);
	CString GetCustomerID();
	void SetCustomerID(LPCTSTR lpszNewValue);
	CString GetDepartment();
	void SetDepartment(LPCTSTR lpszNewValue);
	CString GetEmail1Address();
	void SetEmail1Address(LPCTSTR lpszNewValue);
	CString GetEmail1AddressType();
	void SetEmail1AddressType(LPCTSTR lpszNewValue);
	CString GetEmail1DisplayName();
	CString GetEmail1EntryID();
	CString GetEmail2Address();
	void SetEmail2Address(LPCTSTR lpszNewValue);
	CString GetEmail2AddressType();
	void SetEmail2AddressType(LPCTSTR lpszNewValue);
	CString GetEmail2DisplayName();
	CString GetEmail2EntryID();
	CString GetEmail3Address();
	void SetEmail3Address(LPCTSTR lpszNewValue);
	CString GetEmail3AddressType();
	void SetEmail3AddressType(LPCTSTR lpszNewValue);
	CString GetEmail3DisplayName();
	CString GetEmail3EntryID();
	CString GetFileAs();
	void SetFileAs(LPCTSTR lpszNewValue);
	CString GetFirstName();
	void SetFirstName(LPCTSTR lpszNewValue);
	CString GetFTPSite();
	void SetFTPSite(LPCTSTR lpszNewValue);
	CString GetFullName();
	void SetFullName(LPCTSTR lpszNewValue);
	CString GetFullNameAndCompany();
	long GetGender();
	void SetGender(long nNewValue);
	CString GetGovernmentIDNumber();
	void SetGovernmentIDNumber(LPCTSTR lpszNewValue);
	CString GetHobby();
	void SetHobby(LPCTSTR lpszNewValue);
	CString GetHome2TelephoneNumber();
	void SetHome2TelephoneNumber(LPCTSTR lpszNewValue);
	CString GetHomeAddress();
	void SetHomeAddress(LPCTSTR lpszNewValue);
	CString GetHomeAddressCity();
	void SetHomeAddressCity(LPCTSTR lpszNewValue);
	CString GetHomeAddressCountry();
	void SetHomeAddressCountry(LPCTSTR lpszNewValue);
	CString GetHomeAddressPostalCode();
	void SetHomeAddressPostalCode(LPCTSTR lpszNewValue);
	CString GetHomeAddressPostOfficeBox();
	void SetHomeAddressPostOfficeBox(LPCTSTR lpszNewValue);
	CString GetHomeAddressState();
	void SetHomeAddressState(LPCTSTR lpszNewValue);
	CString GetHomeAddressStreet();
	void SetHomeAddressStreet(LPCTSTR lpszNewValue);
	CString GetHomeFaxNumber();
	void SetHomeFaxNumber(LPCTSTR lpszNewValue);
	CString GetHomeTelephoneNumber();
	void SetHomeTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetInitials();
	void SetInitials(LPCTSTR lpszNewValue);
	CString GetInternetFreeBusyAddress();
	void SetInternetFreeBusyAddress(LPCTSTR lpszNewValue);
	CString GetISDNNumber();
	void SetISDNNumber(LPCTSTR lpszNewValue);
	CString GetJobTitle();
	void SetJobTitle(LPCTSTR lpszNewValue);
	BOOL GetJournal();
	void SetJournal(BOOL bNewValue);
	CString GetLanguage();
	void SetLanguage(LPCTSTR lpszNewValue);
	CString GetLastFirstAndSuffix();
	CString GetLastFirstNoSpace();
	CString GetLastFirstNoSpaceCompany();
	CString GetLastFirstSpaceOnly();
	CString GetLastFirstSpaceOnlyCompany();
	CString GetLastName();
	void SetLastName(LPCTSTR lpszNewValue);
	CString GetLastNameAndFirstName();
	CString GetMailingAddress();
	void SetMailingAddress(LPCTSTR lpszNewValue);
	CString GetMailingAddressCity();
	void SetMailingAddressCity(LPCTSTR lpszNewValue);
	CString GetMailingAddressCountry();
	void SetMailingAddressCountry(LPCTSTR lpszNewValue);
	CString GetMailingAddressPostalCode();
	void SetMailingAddressPostalCode(LPCTSTR lpszNewValue);
	CString GetMailingAddressPostOfficeBox();
	void SetMailingAddressPostOfficeBox(LPCTSTR lpszNewValue);
	CString GetMailingAddressState();
	void SetMailingAddressState(LPCTSTR lpszNewValue);
	CString GetMailingAddressStreet();
	void SetMailingAddressStreet(LPCTSTR lpszNewValue);
	CString GetManagerName();
	void SetManagerName(LPCTSTR lpszNewValue);
	CString GetMiddleName();
	void SetMiddleName(LPCTSTR lpszNewValue);
	CString GetMobileTelephoneNumber();
	void SetMobileTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetNetMeetingAlias();
	void SetNetMeetingAlias(LPCTSTR lpszNewValue);
	CString GetNetMeetingServer();
	void SetNetMeetingServer(LPCTSTR lpszNewValue);
	CString GetNickName();
	void SetNickName(LPCTSTR lpszNewValue);
	CString GetOfficeLocation();
	void SetOfficeLocation(LPCTSTR lpszNewValue);
	CString GetOrganizationalIDNumber();
	void SetOrganizationalIDNumber(LPCTSTR lpszNewValue);
	CString GetOtherAddress();
	void SetOtherAddress(LPCTSTR lpszNewValue);
	CString GetOtherAddressCity();
	void SetOtherAddressCity(LPCTSTR lpszNewValue);
	CString GetOtherAddressCountry();
	void SetOtherAddressCountry(LPCTSTR lpszNewValue);
	CString GetOtherAddressPostalCode();
	void SetOtherAddressPostalCode(LPCTSTR lpszNewValue);
	CString GetOtherAddressPostOfficeBox();
	void SetOtherAddressPostOfficeBox(LPCTSTR lpszNewValue);
	CString GetOtherAddressState();
	void SetOtherAddressState(LPCTSTR lpszNewValue);
	CString GetOtherAddressStreet();
	void SetOtherAddressStreet(LPCTSTR lpszNewValue);
	CString GetOtherFaxNumber();
	void SetOtherFaxNumber(LPCTSTR lpszNewValue);
	CString GetOtherTelephoneNumber();
	void SetOtherTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetPagerNumber();
	void SetPagerNumber(LPCTSTR lpszNewValue);
	CString GetPersonalHomePage();
	void SetPersonalHomePage(LPCTSTR lpszNewValue);
	CString GetPrimaryTelephoneNumber();
	void SetPrimaryTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetProfession();
	void SetProfession(LPCTSTR lpszNewValue);
	CString GetRadioTelephoneNumber();
	void SetRadioTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetReferredBy();
	void SetReferredBy(LPCTSTR lpszNewValue);
	long GetSelectedMailingAddress();
	void SetSelectedMailingAddress(long nNewValue);
	CString GetSpouse();
	void SetSpouse(LPCTSTR lpszNewValue);
	CString GetSuffix();
	void SetSuffix(LPCTSTR lpszNewValue);
	CString GetTelexNumber();
	void SetTelexNumber(LPCTSTR lpszNewValue);
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	CString GetTTYTDDTelephoneNumber();
	void SetTTYTDDTelephoneNumber(LPCTSTR lpszNewValue);
	CString GetUser1();
	void SetUser1(LPCTSTR lpszNewValue);
	CString GetUser2();
	void SetUser2(LPCTSTR lpszNewValue);
	CString GetUser3();
	void SetUser3(LPCTSTR lpszNewValue);
	CString GetUser4();
	void SetUser4(LPCTSTR lpszNewValue);
	CString GetUserCertificate();
	void SetUserCertificate(LPCTSTR lpszNewValue);
	CString GetWebPage();
	void SetWebPage(LPCTSTR lpszNewValue);
	CString GetYomiCompanyName();
	void SetYomiCompanyName(LPCTSTR lpszNewValue);
	CString GetYomiFirstName();
	void SetYomiFirstName(LPCTSTR lpszNewValue);
	CString GetYomiLastName();
	void SetYomiLastName(LPCTSTR lpszNewValue);
	LPDISPATCH ForwardAsVcard();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _DistListItem 

class _DistListItem : public COleDispatchDriver
{
public:
	_DistListItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_DistListItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DistListItem(const _DistListItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	CString GetDLName();
	void SetDLName(LPCTSTR lpszNewValue);
	long GetMemberCount();
	LPDISPATCH GetLinks();
	void AddMembers(LPDISPATCH Recipients);
	void RemoveMembers(LPDISPATCH Recipients);
	LPDISPATCH GetMember(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _DocumentItem 

class _DocumentItem : public COleDispatchDriver
{
public:
	_DocumentItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_DocumentItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DocumentItem(const _DocumentItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ExplorersEvents 

class ExplorersEvents : public COleDispatchDriver
{
public:
	ExplorersEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ExplorersEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ExplorersEvents(const ExplorersEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void NewExplorer(LPDISPATCH Explorer);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse FoldersEvents 

class FoldersEvents : public COleDispatchDriver
{
public:
	FoldersEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	FoldersEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FoldersEvents(const FoldersEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void FolderAdd(LPDISPATCH Folder);
	void FolderChange(LPDISPATCH Folder);
	void FolderRemove();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse InspectorsEvents 

class InspectorsEvents : public COleDispatchDriver
{
public:
	InspectorsEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	InspectorsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	InspectorsEvents(const InspectorsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void NewInspector(LPDISPATCH Inspector);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ItemsEvents 

class ItemsEvents : public COleDispatchDriver
{
public:
	ItemsEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ItemsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ItemsEvents(const ItemsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void ItemAdd(LPDISPATCH Item);
	void ItemChange(LPDISPATCH Item);
	void ItemRemove();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _JournalItem 

class _JournalItem : public COleDispatchDriver
{
public:
	_JournalItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_JournalItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_JournalItem(const _JournalItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	CString GetContactNames();
	void SetContactNames(LPCTSTR lpszNewValue);
	BOOL GetDocPosted();
	void SetDocPosted(BOOL bNewValue);
	BOOL GetDocPrinted();
	void SetDocPrinted(BOOL bNewValue);
	BOOL GetDocRouted();
	void SetDocRouted(BOOL bNewValue);
	BOOL GetDocSaved();
	void SetDocSaved(BOOL bNewValue);
	long GetDuration();
	void SetDuration(long nNewValue);
	DATE GetEnd();
	void SetEnd(DATE newValue);
	CString GetType();
	void SetType(LPCTSTR lpszNewValue);
	LPDISPATCH GetRecipients();
	DATE GetStart();
	void SetStart(DATE newValue);
	LPDISPATCH Forward();
	LPDISPATCH Reply();
	LPDISPATCH ReplyAll();
	void StartTimer();
	void StopTimer();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse NameSpaceEvents 

class NameSpaceEvents : public COleDispatchDriver
{
public:
	NameSpaceEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	NameSpaceEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	NameSpaceEvents(const NameSpaceEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void OptionsPagesAdd(LPDISPATCH Pages, LPDISPATCH Folder);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _NoteItem 

class _NoteItem : public COleDispatchDriver
{
public:
	_NoteItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_NoteItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_NoteItem(const _NoteItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	long GetColor();
	void SetColor(long nNewValue);
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetGetInspector();
	long GetHeight();
	void SetHeight(long nNewValue);
	DATE GetLastModificationTime();
	long GetLeft();
	void SetLeft(long nNewValue);
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	BOOL GetSaved();
	long GetSize();
	CString GetSubject();
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse OutlookBarGroup 

class OutlookBarGroup : public COleDispatchDriver
{
public:
	OutlookBarGroup() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	OutlookBarGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OutlookBarGroup(const OutlookBarGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetShortcuts();
	long GetViewType();
	void SetViewType(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _OutlookBarShortcuts 

class _OutlookBarShortcuts : public COleDispatchDriver
{
public:
	_OutlookBarShortcuts() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_OutlookBarShortcuts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_OutlookBarShortcuts(const _OutlookBarShortcuts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(const VARIANT& Target, LPCTSTR Name, const VARIANT& Index);
	void Remove(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse OutlookBarShortcut 

class OutlookBarShortcut : public COleDispatchDriver
{
public:
	OutlookBarShortcut() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	OutlookBarShortcut(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OutlookBarShortcut(const OutlookBarShortcut& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetTarget();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _OutlookBarGroups 

class _OutlookBarGroups : public COleDispatchDriver
{
public:
	_OutlookBarGroups() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_OutlookBarGroups(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_OutlookBarGroups(const _OutlookBarGroups& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(LPCTSTR Name, const VARIANT& Index);
	void Remove(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse OutlookBarGroupsEvents 

class OutlookBarGroupsEvents : public COleDispatchDriver
{
public:
	OutlookBarGroupsEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	OutlookBarGroupsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OutlookBarGroupsEvents(const OutlookBarGroupsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void GroupAdd(LPDISPATCH NewGroup);
	void BeforeGroupAdd(BOOL* Cancel);
	void BeforeGroupRemove(LPDISPATCH Group, BOOL* Cancel);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _OutlookBarPane 

class _OutlookBarPane : public COleDispatchDriver
{
public:
	_OutlookBarPane() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_OutlookBarPane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_OutlookBarPane(const _OutlookBarPane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetContents();
	LPDISPATCH GetCurrentGroup();
	void SetRefCurrentGroup(LPDISPATCH newValue);
	CString GetName();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse OutlookBarStorage 

class OutlookBarStorage : public COleDispatchDriver
{
public:
	OutlookBarStorage() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	OutlookBarStorage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OutlookBarStorage(const OutlookBarStorage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetGroups();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse OutlookBarPaneEvents 

class OutlookBarPaneEvents : public COleDispatchDriver
{
public:
	OutlookBarPaneEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	OutlookBarPaneEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OutlookBarPaneEvents(const OutlookBarPaneEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void BeforeNavigate(LPDISPATCH Shortcut, BOOL* Cancel);
	void BeforeGroupSwitch(LPDISPATCH ToGroup, BOOL* Cancel);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse OutlookBarShortcutsEvents 

class OutlookBarShortcutsEvents : public COleDispatchDriver
{
public:
	OutlookBarShortcutsEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	OutlookBarShortcutsEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OutlookBarShortcutsEvents(const OutlookBarShortcutsEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void ShortcutAdd(LPDISPATCH NewShortcut);
	void BeforeShortcutAdd(BOOL* Cancel);
	void BeforeShortcutRemove(LPDISPATCH Shortcut, BOOL* Cancel);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse PropertyPageSite 

class PropertyPageSite : public COleDispatchDriver
{
public:
	PropertyPageSite() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	PropertyPageSite(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PropertyPageSite(const PropertyPageSite& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	void OnStatusChange();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse Pages 

class Pages : public COleDispatchDriver
{
public:
	Pages() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	Pages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Pages(const Pages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(const VARIANT& Name);
	void Remove(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _PostItem 

class _PostItem : public COleDispatchDriver
{
public:
	_PostItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_PostItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_PostItem(const _PostItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	DATE GetExpiryTime();
	void SetExpiryTime(DATE newValue);
	CString GetHTMLBody();
	void SetHTMLBody(LPCTSTR lpszNewValue);
	DATE GetReceivedTime();
	CString GetSenderName();
	DATE GetSentOn();
	void ClearConversationIndex();
	LPDISPATCH Forward();
	void Post();
	LPDISPATCH Reply();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _RemoteItem 

class _RemoteItem : public COleDispatchDriver
{
public:
	_RemoteItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_RemoteItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_RemoteItem(const _RemoteItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	BOOL GetHasAttachment();
	CString GetRemoteMessageClass();
	long GetTransferSize();
	long GetTransferTime();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _ReportItem 

class _ReportItem : public COleDispatchDriver
{
public:
	_ReportItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_ReportItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ReportItem(const _ReportItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _TaskItem 

class _TaskItem : public COleDispatchDriver
{
public:
	_TaskItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_TaskItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_TaskItem(const _TaskItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	long GetActualWork();
	void SetActualWork(long nNewValue);
	CString GetCardData();
	void SetCardData(LPCTSTR lpszNewValue);
	BOOL GetComplete();
	void SetComplete(BOOL bNewValue);
	CString GetContacts();
	void SetContacts(LPCTSTR lpszNewValue);
	CString GetContactNames();
	void SetContactNames(LPCTSTR lpszNewValue);
	DATE GetDateCompleted();
	void SetDateCompleted(DATE newValue);
	long GetDelegationState();
	CString GetDelegator();
	DATE GetDueDate();
	void SetDueDate(DATE newValue);
	BOOL GetIsRecurring();
	long GetOrdinal();
	void SetOrdinal(long nNewValue);
	CString GetOwner();
	void SetOwner(LPCTSTR lpszNewValue);
	long GetOwnership();
	long GetPercentComplete();
	void SetPercentComplete(long nNewValue);
	LPDISPATCH GetRecipients();
	DATE GetReminderTime();
	void SetReminderTime(DATE newValue);
	BOOL GetReminderOverrideDefault();
	void SetReminderOverrideDefault(BOOL bNewValue);
	BOOL GetReminderPlaySound();
	void SetReminderPlaySound(BOOL bNewValue);
	BOOL GetReminderSet();
	void SetReminderSet(BOOL bNewValue);
	CString GetReminderSoundFile();
	void SetReminderSoundFile(LPCTSTR lpszNewValue);
	long GetResponseState();
	CString GetRole();
	void SetRole(LPCTSTR lpszNewValue);
	CString GetSchedulePlusPriority();
	void SetSchedulePlusPriority(LPCTSTR lpszNewValue);
	DATE GetStartDate();
	void SetStartDate(DATE newValue);
	long GetStatus();
	void SetStatus(long nNewValue);
	CString GetStatusOnCompletionRecipients();
	void SetStatusOnCompletionRecipients(LPCTSTR lpszNewValue);
	CString GetStatusUpdateRecipients();
	void SetStatusUpdateRecipients(LPCTSTR lpszNewValue);
	BOOL GetTeamTask();
	void SetTeamTask(BOOL bNewValue);
	long GetTotalWork();
	void SetTotalWork(long nNewValue);
	LPDISPATCH Assign();
	void CancelResponseState();
	void ClearRecurrencePattern();
	LPDISPATCH GetRecurrencePattern();
	void MarkComplete();
	LPDISPATCH Respond(long Response, const VARIANT& fNoUI, const VARIANT& fAdditionalTextDialog);
	void Send();
	BOOL SkipRecurrence();
	LPDISPATCH StatusReport();
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _TaskRequestAcceptItem 

class _TaskRequestAcceptItem : public COleDispatchDriver
{
public:
	_TaskRequestAcceptItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_TaskRequestAcceptItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_TaskRequestAcceptItem(const _TaskRequestAcceptItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetAssociatedTask(BOOL AddToTaskList);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _TaskRequestDeclineItem 

class _TaskRequestDeclineItem : public COleDispatchDriver
{
public:
	_TaskRequestDeclineItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_TaskRequestDeclineItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_TaskRequestDeclineItem(const _TaskRequestDeclineItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetAssociatedTask(BOOL AddToTaskList);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _TaskRequestItem 

class _TaskRequestItem : public COleDispatchDriver
{
public:
	_TaskRequestItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_TaskRequestItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_TaskRequestItem(const _TaskRequestItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetAssociatedTask(BOOL AddToTaskList);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _TaskRequestUpdateItem 

class _TaskRequestUpdateItem : public COleDispatchDriver
{
public:
	_TaskRequestUpdateItem() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_TaskRequestUpdateItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_TaskRequestUpdateItem(const _TaskRequestUpdateItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPDISPATCH GetApplication();
	long GetClass();
	LPDISPATCH GetSession();
	LPDISPATCH GetParent();
	LPDISPATCH GetActions();
	LPDISPATCH GetAttachments();
	CString GetBillingInformation();
	void SetBillingInformation(LPCTSTR lpszNewValue);
	CString GetBody();
	void SetBody(LPCTSTR lpszNewValue);
	CString GetCategories();
	void SetCategories(LPCTSTR lpszNewValue);
	CString GetCompanies();
	void SetCompanies(LPCTSTR lpszNewValue);
	CString GetConversationIndex();
	CString GetConversationTopic();
	DATE GetCreationTime();
	CString GetEntryID();
	LPDISPATCH GetFormDescription();
	LPDISPATCH GetGetInspector();
	long GetImportance();
	void SetImportance(long nNewValue);
	DATE GetLastModificationTime();
	CString GetMessageClass();
	void SetMessageClass(LPCTSTR lpszNewValue);
	CString GetMileage();
	void SetMileage(LPCTSTR lpszNewValue);
	BOOL GetNoAging();
	void SetNoAging(BOOL bNewValue);
	long GetOutlookInternalVersion();
	CString GetOutlookVersion();
	BOOL GetSaved();
	long GetSensitivity();
	void SetSensitivity(long nNewValue);
	long GetSize();
	CString GetSubject();
	void SetSubject(LPCTSTR lpszNewValue);
	BOOL GetUnRead();
	void SetUnRead(BOOL bNewValue);
	LPDISPATCH GetUserProperties();
	void Close(long SaveMode);
	LPDISPATCH Copy();
	void Delete();
	void Display(const VARIANT& Modal);
	LPDISPATCH Move(LPDISPATCH DestFldr);
	void PrintOut();
	void Save();
	void SaveAs(LPCTSTR Path, const VARIANT& Type);
	LPDISPATCH GetAssociatedTask(BOOL AddToTaskList);
	LPDISPATCH GetLinks();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _DRecipientControl 

class _DRecipientControl : public COleDispatchDriver
{
public:
	_DRecipientControl() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_DRecipientControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DRecipientControl(const _DRecipientControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetBackColor();
	void SetBackColor(long nNewValue);
	long GetForeColor();
	void SetForeColor(long nNewValue);
	BOOL GetReadOnly();
	void SetReadOnly(BOOL bNewValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	long GetSpecialEffect();
	void SetSpecialEffect(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _DRecipientControlEvents 

class _DRecipientControlEvents : public COleDispatchDriver
{
public:
	_DRecipientControlEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_DRecipientControlEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DRecipientControlEvents(const _DRecipientControlEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _DDocSiteControl 

class _DDocSiteControl : public COleDispatchDriver
{
public:
	_DDocSiteControl() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_DDocSiteControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DDocSiteControl(const _DDocSiteControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	BOOL GetReadOnly();
	void SetReadOnly(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _DDocSiteControlEvents 

class _DDocSiteControlEvents : public COleDispatchDriver
{
public:
	_DDocSiteControlEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_DDocSiteControlEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DDocSiteControlEvents(const _DDocSiteControlEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
};
