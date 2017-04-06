// DlgProcesses.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wins.h"
#include "ipfile.h"
#include "DlgProcesses.h"
#include <malloc.h>
#include <imagehlp.h>

#include "WinsDlg.h"

#include <sys/types.h>
#include <sys/stat.h>

#include "Winnt.h"
#include "Windows.h"
#include "Winuser.h"

#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr)+(DWORD)(addValue))

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgProcesses 


CDlgProcesses::CDlgProcesses(DWORD dwProcID, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProcesses::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProcesses)
	//}}AFX_DATA_INIT
	this->m_dwProcID = dwProcID;
}


void CDlgProcesses::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProcesses)
	DDX_Control(pDX, IDC_PROC_TREE, m_oProcTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProcesses, CDialog)
	//{{AFX_MSG_MAP(CDlgProcesses)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_MESSAFTERONINIT, OnFillTree)
	ON_NOTIFY(NM_DBLCLK, IDC_PROC_TREE, OnDblclkProcTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgProcesses 

BOOL CDlgProcesses::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;
}

TREEITEMDATA* CDlgProcesses::GetItemDataFromProcID(DWORD dwProcID, DWORD dwModuleID)
{
	PROCESSENTRY32 pe32      = {0}; 
	MODULEENTRY32 me32       = {0}; 

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	if (hProcessSnap == INVALID_HANDLE_VALUE) 
	{
		AfxMessageBox("GetItemDataFromProcID e1");
        return NULL; 
	}

	pe32.dwSize = sizeof(PROCESSENTRY32); 
	if (!Process32First(hProcessSnap, &pe32)) 
	{
		AfxMessageBox("GetItemDataFromProcID e2");
        return NULL; 
	}

	TREEITEMDATA* _p = new TREEITEMDATA();
	if(!GetProcessModule(dwProcID, pe32.th32ModuleID, &me32, sizeof(MODULEENTRY32), &_p->m_aChildren))
	{
		AfxMessageBox("GetItemDataFromProcID e3");
        return NULL; 
	}

    // Get the actual priority class. 
    //HANDLE hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
    //CloseHandle (hProcess); 

	_p->m_sTitle.Format( "Thread Count:%d; modulename:%s; path:%s", pe32.cntThreads, me32.szModule, me32.szExePath);
	_p->m_sTitle.Format( "ProcID:%d, Thread Count:%d, modulename:%s, exe:%s, Modules:%d", dwProcID, pe32.cntThreads, me32.szModule, me32.szExePath, _p->m_aChildren.GetSize());
	_p->m_sModFN.Format("%s", me32.szExePath);
	_p->me=me32;

	return _p;
}

void CDlgProcesses::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_oProcTree.m_hWnd == NULL)
		return;

	RECT _rct;
	GetClientRect(&_rct);	

	_rct.bottom -=5;
	_rct.right	-=5;
	_rct.top	+=5;
	_rct.left	+=5;
	m_oProcTree.MoveWindow(&_rct);
}

LRESULT CDlgProcesses::OnFillTree(WPARAM wp, LPARAM lp) 
{
	if(!this->IsWindowVisible())
	{
		::__IPVSleep(1);
		PostMessage(WM_MESSAFTERONINIT, 0, 0);
__Log("DlgProcesses::OnFillTree\tINFO: post msg again...");
		return 0;
	}

__Log("DlgProcesses::OnFillTree\tINFO: begin");
	TREEITEMDATA* _pRoot = GetItemDataFromProcID(this->m_dwProcID, 0);
	HTREEITEM h = NULL;

	CArray<HTREEITEM, HTREEITEM> aHtis;

	m_oProcTree.Setup();

	long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\1.bmp");

	if(!_pRoot)
		return 0;

	h = m_oProcTree.InsertItem(_pRoot->m_sTitle, l, l, TVI_ROOT, TVI_LAST); 
	SetItemData(h, TYPE_EXE, _pRoot->m_dwProcessID, _pRoot->m_sModFN, _pRoot->m_sTitle, &(_pRoot->me)); 

	_pRoot->m_hti = h;

	for(int i=1; i < _pRoot->m_aChildren.GetSize(); i++)
	{
///////////////////// get dll /////////////////////////////////////////////////////////////////////////////////
		TREEITEMDATA* _p1Level	= new TREEITEMDATA;

		_p1Level->m_dwProcessID = _pRoot->m_aChildren.GetAt(i).th32ModuleID;
		_p1Level->m_sTitle = _p1Level->m_sModFN		= _pRoot->m_aChildren.GetAt(i).szExePath;
		//_p1Level->m_sTitle		= CIPString(_p1Level->m_sModFN + "\\" + _pRoot->m_aChildren.GetAt(i).szModule);

		long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\2.bmp");
		HTREEITEM htiMod = GetItemFromName(_p1Level->m_sTitle, &aHtis);
		if(!htiMod)
		{
			htiMod = m_oProcTree.InsertItem(_p1Level->m_sTitle, l, l, _pRoot->m_hti, TVI_LAST); 
			SetItemData(htiMod, TYPE_DLL, _p1Level->m_dwProcessID, _p1Level->m_sModFN, _p1Level->m_sTitle, &(_pRoot->m_aChildren.GetAt(i)));
			aHtis.Add(htiMod);
		}
		_p1Level->m_hti = htiMod;
		
		//get exported functions
		HMODULE hm = ::LoadLibrary(_p1Level->m_sModFN);
		if(!hm)
			continue;

		::__IPVSleep(2);

		FillImpsExpsFromHModule(hm, _p1Level, &aHtis);
	}

	return 0;
}

void CDlgProcesses::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	::__IPVSleep(1);
	PostMessage(WM_MESSAFTERONINIT, 0, 0);	
}

HTREEITEM CDlgProcesses::GetItemFromName(CIPString sTitle, CArray<HTREEITEM, HTREEITEM> *paHtis)
{
	if(!paHtis)
		return NULL;
	for(int i=0; i < paHtis->GetSize(); i++)
	{
		if(sTitle.CompareNoCase(m_oProcTree.GetItemText(paHtis->GetAt(i))) == 0)
			return paHtis->GetAt(i);
	}

	return NULL;
}

BOOL CDlgProcesses::FillImpsExpsFromHModule(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis)
{
	if((hm==NULL) || (pTrItemData==NULL) || (paHtis==NULL))
		return FALSE;

	FillImpsFromHModule(hm, pTrItemData, paHtis);
	FillExpsFromHModule(hm, pTrItemData, paHtis);

	return TRUE;
}

BOOL CDlgProcesses::FillExpsFromHModule(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis)
{
	if((hm==NULL) || (pTrItemData==NULL) || (paHtis==NULL))
		return FALSE;

	HTREEITEM htiMod3 = GetItemFromName(_T("Exportierte Funktionen von "+pTrItemData->m_sTitle), paHtis);

	IMAGE_DOS_HEADER * dosheader=(IMAGE_DOS_HEADER *)hm;
	IMAGE_OPTIONAL_HEADER * opthdr =(IMAGE_OPTIONAL_HEADER *) ((BYTE*)hm+dosheader->e_lfanew+24);
	IMAGE_EXPORT_DIRECTORY *exp=(IMAGE_EXPORT_DIRECTORY *)((BYTE*) hm+opthdr->DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT]. VirtualAddress);
	ULONG *addressoffunctions=(ULONG*)((BYTE*) hm +exp->AddressOfFunctions);
	ULONG * addressofnames=(ULONG*)((BYTE*) hm +exp->AddressOfNames);
	CIPString sAlls = _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@_");

	for(DWORD x=0; x < exp->NumberOfFunctions;x++)
	{
		if(x==0)
		{
			if(!htiMod3)
			{
				long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\2.bmp");
				htiMod3 = m_oProcTree.InsertItem(_T("Exportierte Funktionen von "+pTrItemData->m_sTitle), l, l, pTrItemData->m_hti, TVI_LAST); 
				SetItemData(htiMod3, TYPE_DLL, pTrItemData->m_dwProcessID, pTrItemData->m_sModFN, pTrItemData->m_sTitle, NULL);
				paHtis->Add(htiMod3);
			}
			else
				htiMod3	= pTrItemData->m_hti;
		}

		char*functionname=(char*)((BYTE*) hm +addressofnames[x]);
		if(!IsBadReadPtr(functionname, sizeof(char*)))
		{
			CIPString sFN=_T("");
			sFN.Format("%s", functionname);
			BOOL bNotOK = FALSE;
			char c=' ';
			if(sFN.GetLength() > 99)
				bNotOK = TRUE;
			else
			{

				for(int k=0; k<sFN.GetLength(); k++)
				{
					if(sAlls.Find(sFN.GetAt(k))<0)
					{
						bNotOK = TRUE;
						c = sFN[k];
						break;
					}

				}
			}

			if(bNotOK)
				continue;

			if(!sFN.IsEmpty())
			{
				sFN += _T(" (exported function)"); 
				long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3e.bmp");
				HTREEITEM htiMod2 = m_oProcTree.InsertItem(sFN, l, l, htiMod3, TVI_LAST); 
				SetItemData(htiMod2, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
			}
		}
	}

	return TRUE;
}

BOOL CDlgProcesses::FillImpsFromHModule(HMODULE hm, TREEITEMDATA *pTrItemData, CArray<HTREEITEM, HTREEITEM> *paHtis)
{
	if((hm==NULL) || (pTrItemData==NULL) || (paHtis==NULL))
		return FALSE;

	CIPStringArray aFus;

	IMAGE_IMPORT_DESCRIPTOR *ImgImport;
	IMAGE_THUNK_DATA *Thunk;
	unsigned long siziat;

	IMAGE_DOS_HEADER * dosheader=(IMAGE_DOS_HEADER *)hm;
	CIPFile _ipf;
	CIPString _s;

	::GetModuleFileName(hm, _s.GetBuffer(1024), 1024);
	_s.ReleaseBuffer();
	if(_s.IsEmpty())
		return FALSE;

	CIPFile cif;
	cif.SetFilePath(_s);
	cif.GetPath(_s);

	{
		ImgImport=(IMAGE_IMPORT_DESCRIPTOR*)ImageDirectoryEntryToData(hm, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &siziat);
		if(ImgImport && !IsBadReadPtr(ImgImport, sizeof(IMAGE_IMPORT_DESCRIPTOR)) && ImgImport->Name) 
		{
			while(ImgImport->Name)
			{
				char *ModName=((char*)hm + ImgImport->Name);
				CIPString sModName(ModName);

				HMODULE _hdll = GetModuleHandle(sModName);
				if(!_hdll)
					_hdll = GetModuleHandle(CIPString(_s+"\\"+sModName));
				if(_hdll)
				{
					::GetModuleFileName(_hdll, _s.GetBuffer(1024), 1024);
					_s.ReleaseBuffer();
					sModName = _s;
				}

				long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\2.bmp");
				HTREEITEM htiMod2 = GetItemFromName(sModName, paHtis);
				if(!htiMod2)
				{
					htiMod2 = m_oProcTree.InsertItem(sModName, l, l, pTrItemData->m_hti, TVI_LAST); 
					SetItemData(htiMod2, TYPE_DLL, 0, sModName, sModName, NULL);
					paHtis->Add(htiMod2);
				}

				Thunk=(IMAGE_THUNK_DATA*)((PBYTE)hm + ImgImport->FirstThunk);

				if(Thunk->u1.Function)
				{
					HTREEITEM htiMod3 = GetItemFromName(_T("Importierte Funktionen von "+sModName), paHtis);
					if(!htiMod3)
					{
						htiMod3 = m_oProcTree.InsertItem(_T("Importierte Funktionen von "+sModName), l, l, htiMod2, TVI_LAST); 
						SetItemData(htiMod3, TYPE_DLL, 0, sModName, sModName, NULL);
						paHtis->Add(htiMod3);
					}
					htiMod2 = htiMod3;
				}

				while(Thunk->u1.Function)
				{
					PROC *fn=NULL;
					fn=(PROC*)&Thunk->u1.Function;

					BOOL bOK = FALSE;

					{
						LPCTSTR functionname=(char*)((BYTE*)dosheader+(unsigned)Thunk->u1.AddressOfData+2);
						CIPString sFN(functionname);
						if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
						{
							sFN += _T(" (imported function)");
							long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
							HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
							SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
							bOK = TRUE;
						}
					}

					if(!bOK)
					{
							PIMAGE_IMPORT_BY_NAME pName			= MakePtr(PIMAGE_IMPORT_BY_NAME, hm, Thunk->u1.AddressOfData);
							PIMAGE_IMPORT_BY_NAME pImportName	= MakePtr(PIMAGE_IMPORT_BY_NAME, hm, Thunk->u1.AddressOfData );
							
							LPSTR pszNameOrOrdinal = (LPSTR)((DWORD)&pImportName->Name);

							CIPString sFN(pszNameOrOrdinal);
							if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
							{
								sFN += _T(" (imported function)");
								long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
								HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
								SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
								bOK = TRUE;
							}
							else
							{
								LPCSTR azFunctionName = LPCSTR(pName->Name);
								CIPString sFN(azFunctionName);
								if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
								{
									sFN += _T(" (imported function)");
									long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
									HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
									SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
									bOK = TRUE;
								}
							}

							if(!bOK)
							{
								if(! ( IMAGE_SNAP_BY_ORDINAL(Thunk->u1.Ordinal) ))  // import by ordinal
								{
									LPCSTR azFunctionName = LPCSTR(pName->Name);
									CIPString sFN(azFunctionName);
									if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
									{
										sFN += _T(" (imported function)");
										long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
										HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
										SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
										bOK = TRUE;
									}
								}
								else
								{
									PIMAGE_IMPORT_BY_NAME pImportName = MakePtr(PIMAGE_IMPORT_BY_NAME,
																 hm,
																 Thunk->u1.AddressOfData );

									LPSTR pszNameOrOrdinal = (LPSTR)((DWORD)&pImportName->Name);

									CIPString sFN(pszNameOrOrdinal);
									if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
									{
										sFN += _T(" (imported function)");
										long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
										HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
										SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
										bOK = TRUE;
									}
								}
							}
							if(!bOK)
							{
								if(( IMAGE_SNAP_BY_ORDINAL(Thunk->u1.Ordinal) ))  // import by ordinal
								{
									LPCSTR azFunctionName = LPCSTR(pName->Name);
									CIPString sFN(azFunctionName);
									if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
									{
										sFN += _T(" (imported function)");
										long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
										HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
										SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
										bOK = TRUE;
									}
								}
								else
								{
									PIMAGE_IMPORT_BY_NAME pImportName = MakePtr(PIMAGE_IMPORT_BY_NAME,
																 hm,
																 Thunk->u1.AddressOfData );

									LPSTR pszNameOrOrdinal = (LPSTR)((DWORD)&pImportName->Name);

									CIPString sFN(pszNameOrOrdinal);
									if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
									{
										sFN += _T(" (imported function)");
										long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
										HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
										SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
										bOK = TRUE;
									}
								}
							}

							if(!bOK)
							{
								 PIMAGE_THUNK_DATA pIAT;     // Ptr to import address table
								 PIMAGE_THUNK_DATA pINT;     // Ptr to import names table
								 PIMAGE_THUNK_DATA pIteratingIAT;
								 LPSTR pszNameOrOrdinal;
 
								 // Figure out which OS platform we're on
								 OSVERSIONINFO osvi; 
								 osvi.dwOSVersionInfoSize = sizeof(osvi);
								 GetVersionEx( &osvi );
 
								 // If no import names table, we can't redirect this, so bail

									HMODULE hModEXE = hm;//GetModuleHandle( 0 );

									IMAGE_DOS_HEADER * dosheader2=(IMAGE_DOS_HEADER *)hModEXE;
									PIMAGE_NT_HEADERS pExeNTHdr =  MakePtr(PIMAGE_NT_HEADERS, hModEXE, dosheader2->e_lfanew);
									//PIMAGE_NT_HEADERS pExeNTHdr = PEHeaderFromHModule( hModEXE );
									DWORD importRVA = pExeNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress; 
									// Convert imports RVA to a usable pointer
									PIMAGE_IMPORT_DESCRIPTOR pImportDesc = MakePtr( PIMAGE_IMPORT_DESCRIPTOR, hModEXE, importRVA );



								 if ( pImportDesc->OriginalFirstThunk == 0 )
								 {
								 }
								 else
								 {
									 PVOID pBaseLoadAddr = hModEXE;
									 pIAT = MakePtr(PIMAGE_THUNK_DATA, pBaseLoadAddr, pImportDesc->FirstThunk);
									 pINT = MakePtr( PIMAGE_THUNK_DATA, pBaseLoadAddr,
													 pImportDesc->OriginalFirstThunk );
 
									 // Count how many entries there are in this IAT.  Array is 0 terminated
									 pIteratingIAT = pIAT;
									 unsigned cFuncs = 0;
									 int ij=0;
									 while ( pIteratingIAT->u1.Function )
									 {
										 ij++;
										 if(ij>99)
											 break;
										 cFuncs++;
										 pIteratingIAT++;
									 }
 
									 if ( cFuncs == 0 )  // If no imported functions, we're done!
									 {
									 }
									 else
									 {
										 // These next few lines ensure that we'll be able to modify the IAT,
										 // which is often in a read-only section in the EXE.
										 DWORD flOldProtect, flNewProtect;
										 MEMORY_BASIC_INFORMATION mbi;
     
										 // Get the current protection attributes                            
										 VirtualQuery( pIAT, &mbi, sizeof(mbi) );
     
										 // remove ReadOnly and ExecuteRead attributes, add on ReadWrite flag
										 flNewProtect = mbi.Protect;
										 flNewProtect &= ~(PAGE_READONLY | PAGE_EXECUTE_READ);
										 flNewProtect |= (PAGE_READWRITE);
     
										 if ( !VirtualProtect(   pIAT, sizeof(PVOID) * cFuncs,
																 flNewProtect, &flOldProtect) )
										 {
											 //nix
										 }
										 else
										 {
											 // Allocate memory for the redirection stubs.  Make one extra stub at the
											 // end to be a sentinel
 
											 // Scan through the IAT, completing the stubs and redirecting the IAT
											 // entries to point to the stubs
											 pIteratingIAT = pIAT;

											 int iji=0;
											 while ( pIteratingIAT->u1.Function )
											 { 
												 iji++;
												 if(iji>99)
													 break;

												 // Technically, we don't absolutely need the pszNameOrOrdinal field,
												 // but it's nice to have.  It also serves as a useful sentinel value.
												 if ( IMAGE_SNAP_BY_ORDINAL(pINT->u1.Ordinal) )  // import by ordinal
												 {
													 pszNameOrOrdinal = (char*)pINT->u1.Ordinal;
												 }
												 else    // It's imported by name
												 {
													 PIMAGE_IMPORT_BY_NAME pImportName = MakePtr(PIMAGE_IMPORT_BY_NAME,
																								 pBaseLoadAddr,
																								 pINT->u1.AddressOfData );
													 pszNameOrOrdinal = (char*)(DWORD)&pImportName->Name;
												 }
											 }

												CIPString sFN(pszNameOrOrdinal);
												if(!sFN.IsEmpty() && IsValidFunctionName(sFN) && !IsInArray(sFN, &aFus))
												{
													sFN += _T(" (imported function)");
													long l = m_oProcTree.m_ImageList.Add(__GetMyDir()+"\\3i.bmp");
													HTREEITEM h = m_oProcTree.InsertItem(sFN, l, l, htiMod2, TVI_LAST); 
													SetItemData(h, TYPE_FUNCTION, 0, _T(""), sFN, NULL);
													bOK = TRUE;
												}
											}
										 }
								 }

							}
					}

					Thunk++;
				}
				ImgImport++;
			}
		}
	}

	return TRUE;
}

BOOL CDlgProcesses::IsValidFunctionName(CIPString sFuName)
{
	CIPString sAlls = _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@_");

	if(sFuName.GetLength() > 99)
		return FALSE;
	for(int k=0; k<sFuName.GetLength(); k++)
	{
		if(sAlls.Find(sFuName.GetAt(k))<0)
		{
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CDlgProcesses::IsInArray(CIPString sName, CIPStringArray *pArray)
{
	if(sName.IsEmpty() || (pArray == NULL))
		return TRUE;

	for(int i=0; i < pArray->GetSize(); i++)
	{
		if(sName.CompareNoCase(pArray->GetAt(i)) == 0)
			return TRUE;
	}

	pArray->Add(sName);

	return FALSE;
}
void CDlgProcesses::OnDblclkProcTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 1;
	HTREEITEM h = m_oProcTree.GetSelectedItem();
	if(!h)
		return;

	TREEITEMDATA* _p = (TREEITEMDATA*)(m_oProcTree.GetItemData(h));
	if(!_p)
		return;

	CIPString sInfo(_T(""));

	if((_p->uType == TYPE_EXE) || (_p->uType == TYPE_DLL))
	{
		sInfo = _p->m_sTitle;	sInfo.Replace("exe:"+_p->m_sModFN,_T(""));
		if(_p->uType == TYPE_EXE)
			sInfo += _T("\nEXE:\t\t\t"+_p->m_sModFN);
		else if(_p->uType == TYPE_DLL)
			sInfo += _T("\nDLL:\t\t\t"+_p->m_sModFN);

		HANDLE h = CreateFile(_p->m_sModFN, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
		if(!h)
			return;

		if (INVALID_HANDLE_VALUE == h) 
			return;

		BY_HANDLE_FILE_INFORMATION fi;

		if(!::GetFileInformationByHandle(h, &fi))
		{
			CloseHandle(h);
			return;
		}
		CloseHandle(h);

		sInfo += _T("\nAttributes:\t\t");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)			sInfo += _T(" FILE_ATTRIBUTE_ARCHIVE");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)			sInfo += _T(" FILE_ATTRIBUTE_COMPRESSED");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)			sInfo += _T(" FILE_ATTRIBUTE_DIRECTORY");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED)			sInfo += _T(" FILE_ATTRIBUTE_ENCRYPTED");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)				sInfo += _T(" FILE_ATTRIBUTE_HIDDEN");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)				sInfo += _T(" FILE_ATTRIBUTE_NORMAL");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)			sInfo += _T(" FILE_ATTRIBUTE_OFFLINE");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_READONLY)			sInfo += _T(" FILE_ATTRIBUTE_READONLY");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)		sInfo += _T(" FILE_ATTRIBUTE_REPARSE_POINT");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE)		sInfo += _T(" FILE_ATTRIBUTE_SPARSE_FILE");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)				sInfo += _T(" FILE_ATTRIBUTE_SYSTEM");
		if(fi.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)			sInfo += _T(" FILE_ATTRIBUTE_TEMPORARY");

		CTime tCreation(fi.ftCreationTime);
		sInfo += _T("\nErstellt am:\t\t"+tCreation.Format("%Y.%m.%d (%A; %B) %H:%M:%S  \t%X %x  -  %z"));
		CTime tLastAccess(fi.ftLastAccessTime);
		sInfo += _T("\nLetzter Zugriff:\t\t"+tLastAccess.Format("%Y.%m.%d (%A; %B) %H:%M:%S  \t\t%X %x  -  %z"));
		CTime tLastWrite(fi.ftLastWriteTime);
		sInfo += _T("\nLetzte Änderung:\t\t"+tLastWrite.Format("%Y.%m.%d (%A; %B) %H:%M:%S  \t%X %x  -  %z"));
		CIPString s; s.Format("%ud", fi.dwVolumeSerialNumber);
		sInfo += _T("\nVolumeSerialNumber:\t"+s);
		s.Format("\nnNumberOfLinks:\t\t%d", fi.nNumberOfLinks);
		sInfo += s;

		unsigned __int64 filesize	= ((unsigned __int64)fi.nFileSizeHigh << 32) + fi.nFileSizeLow;
		UINT mbytesp				= (UINT)(filesize / MEGABYTE);
        UINT bytesp					= (UINT)(filesize % MEGABYTE);
		UINT iosizep				= DB_DEF_IOSIZE;
		s.Format("\nFile size:\t\t\t%d MB; %d Bytes (def-io-size:%d)", mbytesp, bytesp, iosizep);
		sInfo += s;

		{
			HINSTANCE _hdll;
			CIPFile _f;
			_f.SetFilePath(CIPString(_p->m_sModFN));
			CIPString sPath;
			_f.GetPath(sPath);
			_chdir(sPath);
			_hdll = ::LoadLibrary(_p->m_sModFN);
			if (_hdll)
			{
				DLLGETVERSIONPROC pDllGetVersion;
				pDllGetVersion = (DLLGETVERSIONPROC)::GetProcAddress(_hdll, _T("DllGetVersion"));
				if (pDllGetVersion != NULL)
				{
					DLLVERSIONINFO dvi;
					HRESULT hr;
					ZeroMemory(&dvi, sizeof(dvi));
					dvi.cbSize = sizeof(dvi);
					hr = (*pDllGetVersion)(&dvi);
					if(SUCCEEDED(hr))
					{
						s.Format("\nDLL-Version:\t\t%d Minorversion: %d BuildNumber: %d", dvi.dwMajorVersion, dvi.dwMinorVersion, dvi.dwBuildNumber);
						s+=_T(" Plattform: ");
						if (dvi.dwPlatformID == DLLVER_PLATFORM_WINDOWS)
							s +=_T("Windows.");
						else if (dvi.dwPlatformID == DLLVER_PLATFORM_NT)
							s +=_T("Windows NT.");
						else 
							s += _T("unknown.");
						sInfo += s;
					}
				}
				::FreeLibrary(_hdll);
			}
		}
		{
			CModuleVersion ver;
			// 1st get version using File version API
			if (ver.GetFileVersionInfo(_p->m_sModFN)) 
			{
				// display file version from VS_FIXEDFILEINFO struct
				s.Format("\nVersion:\t\t\t%d.%d.%d.%d", HIWORD(ver.dwFileVersionMS), LOWORD(ver.dwFileVersionMS), HIWORD(ver.dwFileVersionLS), LOWORD(ver.dwFileVersionLS));

				// display a bunch of string values
				static LPCTSTR Keys[] = {_T("CompanyName"), _T("FileDescription"), _T("FileVersion"), _T("InternalName"), _T("LegalCopyright"), _T("OriginalFilename"), _T("ProductName"), _T("ProductVersion"), _T("Comments"), _T("LegalTrademarks"), _T("PrivateBuild"), _T("SpecialBuild"), /*_T("FILEOS"), _T("FILETYPE"), _T("FILESUBTYPE"),*/ NULL };
				for (int i=0; Keys[i]; i++) 
				{
					CString temp;
					temp.Format("\n%s:\t\t%s", Keys[i], ver.GetValue(Keys[i]));
					s += temp;
				}
				sInfo += s;
			}
		}

		SHFILEINFO fileInfo;
		SHGetFileInfo(_p->m_sModFN, NULL, &fileInfo, sizeof(fileInfo), SHGFI_ATTRIBUTES|SHGFI_TYPENAME|SHGFI_DISPLAYNAME|SHGFI_EXETYPE|SHGFI_ICON);
		sInfo += _T("\nDisplayName:\t\t"+CIPString(fileInfo.szDisplayName));
		sInfo += _T("\nTypeName:\t\t"+CIPString(fileInfo.szTypeName));
		SHGetFileInfo(_p->m_sModFN, NULL, &fileInfo, sizeof(fileInfo), SHGFI_ICONLOCATION);
		if(!CIPString(fileInfo.szDisplayName).IsEmpty())
			sInfo += _T("\nIconLocation:\t\t"+CIPString(fileInfo.szDisplayName));

		TCHAR szModuleShort[1024];
		GetShortPathName(_p->m_sModFN, szModuleShort, 1024);
		sInfo += _T("\nShortPathName:\t\t"+CIPString(szModuleShort));

		{
			HANDLE hProcess = _p->me.hModule;
			//if(!hProcess)
			{
				hProcess = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, _p->me.th32ProcessID);
			}
			if(hProcess)
			{
				//DWORD dwguiResCount=		GetGuiResources (hProcess, GR_GDIOBJECTS|GR_USEROBJECTS);
				//IO_COUNTERS IoCounters;	GetProcessIoCounters(hProcess,IoCounters);
				//GetUserObjectInformation
				FILETIME ftCreation, ftExit, ftKernel, ftUser;
				if(GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser))
				{
					CTime tCreation(ftCreation);
					CTime tExit(ftExit);
					CTime tKernel(ftKernel);
					CTime tUser(ftUser);
					sInfo += _T("\nTime - Process-creation:\t"+tCreation.Format("%Y.%m.%d (%A; %B) %H:%M:%S"));
/*					sInfo += _T("\nTime - Process-exit:\t"+tExit.Format("%Y.%m.%d (%A; %B) %H:%M:%S"));					sInfo += _T("\nTime - Process-Kernel:\t"+tKernel.Format("%Y.%m.%d (%A; %B) %H:%M:%S"));					sInfo += _T("\nTime - Process-User:\t"+tUser.Format("%Y.%m.%d (%A; %B) %H:%M:%S"));
*/				}

				DWORD MinimumWorkingSetSize, MaximumWorkingSetSize;
				if(GetProcessWorkingSetSize(hProcess, &MinimumWorkingSetSize, &MaximumWorkingSetSize))
				{
					s.Format("\nProcessWorkingSize:\tMinimum:%d Maximum: %d", MinimumWorkingSetSize, MaximumWorkingSetSize);
					sInfo += s;
				}

				//MODULEENTRY32

				CloseHandle(hProcess);
			}

		}






		MessageBox(sInfo, _p->m_sModFN, MB_OK);
	}
	else if(_p->uType == TYPE_FUNCTION)
	{
		AfxMessageBox(_T("Infos über die FUNCTION: "+_p->m_sModFN+"\n"+_p->m_sTitle));
	}
	else
		return;	
}

BOOL CDlgProcesses::SetItemData(HTREEITEM hti, UINT uType, DWORD dwProcessID, CIPString sModFN, CIPString sTitle, MODULEENTRY32* pme)
{
	if(!hti)
		return FALSE;

	TREEITEMDATA* _p = new TREEITEMDATA();

	_p->m_dwProcessID	= dwProcessID;
	_p->m_hti			= hti;
	_p->m_sModFN		= sModFN;
	_p->m_sTitle		= sTitle;
	_p->uType			= uType;
	if(pme)
		_p->me			= *(pme);

	return m_oProcTree.SetItemData(hti, (DWORD)_p);
}
