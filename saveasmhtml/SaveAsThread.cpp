


//
#include "stdafx.h"

#include <stdlib.h>
#include <objbase.h>
#include <assert.h>

#include "SaveAsWebbrowser.h"
#include "SaveAsThread.h"




///////////////////////////////////////////////////////////
//
// Constructor
//
CSaveAsThread::CSaveAsThread() 
{
	m_ThreadId = 0 ;	
	m_hThread  = NULL ;
	m_hComponentReadyEvent = NULL ;
	m_WaitTime = 500 ;
} 

///////////////////////////////////////////////////////////
//
// Destructor
//
CSaveAsThread::~CSaveAsThread()
{
	// The thread must be stopped before we are deleted
	// because the WorkerFunction is in the derived class.
	StopThread();
}


// public API
//

void CSaveAsThread::SetKeyWnd(HWND hwnd) 
{ 
	m_keyhwnd = hwnd; 
}

void CSaveAsThread::Config(CString &szFilename, SaveType type)
{
	m_szFilename = szFilename;
	m_nSaveType = type;
}

CString CSaveAsThread::GetFilename()
{ 
	return m_szFilename; 
}
SaveType CSaveAsThread::GetSaveAsType() 
{ 
	return m_nSaveType; 
}



///////////////////////////////////////////////////////////
//
// StartThread
//   - Create and start the thread.
//
BOOL CSaveAsThread::StartThread() 
{

	m_bShouldStopNow=FALSE;


	if (IsThreadStarted())
	{
		return FALSE ;
	}

	// Create the thread.
	m_hThread = ::CreateThread(NULL,              // Default security
	                           0,                 // Default stack size
	                           RealThreadProc,
	                           (void*)this,
	                           CREATE_SUSPENDED,  // Create the thread suspended.
	                           &m_ThreadId) ;     // Get the Thread ID.
	if (m_hThread == NULL)
	{
		return FALSE ;
	}


	// Create an event for the thread to signal when it is finished. 
	m_hComponentReadyEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL) ;
	if (m_hComponentReadyEvent == NULL)
	{
		return FALSE ;
	}

	// Initialize the wait time.
	m_WaitTime = 250; // 250ms

	// Thread was created suspended; start the thread.
	DWORD r = ResumeThread(m_hThread) ;
	assert(r != 0xffffffff) ;

	return TRUE;
}


///////////////////////////////////////////////////////////
//
// Stop Thread
//
void CSaveAsThread::StopThread()
{
	m_bShouldStopNow = TRUE;
}
	
///////////////////////////////////////////////////////////
//
// Current thread status
//
BOOL CSaveAsThread::IsThreadStarted()
{
	return (m_hThread != NULL) ;
}

///////////////////////////////////////////////////////////
//
// Thread procedure
//
DWORD WINAPI CSaveAsThread::RealThreadProc(void* pv) 
{
	CSaveAsThread* pApartment = reinterpret_cast<CSaveAsThread*>(pv) ;
	return pApartment->ClassThreadProc() ;
}

///////////////////////////////////////////////////////////
//
// Thread procedure
//
DWORD CSaveAsThread::ClassThreadProc()
{

	// Wait for the signal to create a component.
	BOOL bContinue = TRUE;
	BOOL bSignaled = FALSE;

	while ( bContinue )
	{
		switch(	::WaitForSingleObject( m_hComponentReadyEvent, m_WaitTime) )
		{
			// Update the surface becoz now it's ready
			case WAIT_OBJECT_0:
				if ( !m_bShouldStopNow )
				{
					//processPublishDirectory();
				}
				break ;
			// Process Windows messages.
			case (WAIT_OBJECT_0 + 1):
				MSG msg ;
				while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT)
					{
						bContinue = FALSE ;
						break ;
					}
					DispatchMessage(&msg) ;
				}
				break ;
			// Do background processing.
			case WAIT_TIMEOUT:
				if (m_bShouldStopNow)
					bContinue=FALSE;
				else
				{
					if ( ::IsWindowVisible(m_keyhwnd) )
					{
						bSignaled = TRUE;
						bContinue = FALSE;
					}
					MSG msg ;
					while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						if (msg.message == WM_QUIT)
						{
							bContinue = FALSE ;
							break ;
						}
						DispatchMessage(&msg) ;
					}

				}

				break ;

			default:
				break;
		}
	}

	if (bSignaled)
	{
		CSaveAsWebbrowser surrenderNow;
		surrenderNow.Config( GetFilename(), GetSaveAsType() );
		surrenderNow.UpdateSaveAs( m_keyhwnd );
	}


	delete this;

	return 0 ;
}







