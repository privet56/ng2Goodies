
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum _SaveType
{
	SAVETYPE_HTMLPAGE = 0,
	SAVETYPE_ARCHIVE,
	SAVETYPE_HTMLONLY,
	SAVETYPE_TXTONLY
} SaveType;



class CSaveAsWebbrowser  
{
public:

	CSaveAsWebbrowser();
	virtual ~CSaveAsWebbrowser();

	// API
	void SetWebBrowser(IWebBrowser2* pWebBrowser);
	void Config(CString &szFilename, SaveType type);
	CString GetFilename();
	SaveType GetSaveAsType();
	BOOL IsSaveAsEnabled();
	void SaveAsDisable();

	BOOL SaveAs();

	// called by internal thread
	void UpdateSaveAs(HWND hwnd);

private:
	bool InvokeDlg(OLECMDID cmdid);
	static LRESULT CALLBACK CbtProc(int nCode, WPARAM wParam, LPARAM lParam);

	IWebBrowser2*	m_pWebBrowser;
	CString			m_szFilename;
	SaveType		m_nSaveType;
	BOOL			m_bUpdateUI;
	BOOL			m_bSaveAsEnabled;
};


