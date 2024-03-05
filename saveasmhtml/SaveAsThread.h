
#pragma once


///////////////////////////////////////////////////////////
//
//     component on an apartment thread.
//
class CSaveAsThread 
{
public:
	// Constructor
	CSaveAsThread() ;

	// Destructor
	virtual ~CSaveAsThread()  ;

	// Create and start the thread.
	BOOL StartThread() ;

	// Stop the thread.
	void StopThread() ;

	// Current thread status
	BOOL IsThreadStarted() ;



	// public API
	//

	void SetKeyWnd(HWND hwnd);
	void Config(CString &szFilename, SaveType type);
	CString GetFilename();
	SaveType GetSaveAsType();


// Member variables
protected:

	// ID of thread
	DWORD m_ThreadId ;

	// Handle to thread
	HANDLE m_hThread ;

	// Event signals thread to continue.
	HANDLE m_hComponentReadyEvent ;

	// Time to wait before calling WorkerFunction
	DWORD m_WaitTime ;

	BOOL m_bShouldStopNow;


	HWND			m_keyhwnd;
	CString			m_szFilename;
	SaveType		m_nSaveType;


// Internal helper functions
private:
	// Thread procedure
	static DWORD WINAPI RealThreadProc(void* pv) ;

	// Member thread procedure
	DWORD ClassThreadProc() ;

} ;


