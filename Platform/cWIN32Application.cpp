#include "cWIN32Application.h"
#include "../Core/cLog.h"

#include "../Core/cRoot.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

#define WND_CLASS "LIFE_WND_CLASS"

/////////////////////////////////////////////////////////////////////////////////////
cWIN32Application::cWIN32Application(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cWIN32Application::~cWIN32Application(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
void cWIN32Application::CheckWIN32Errors()
/////////////////////////////////////////////////////////////////////////////////////
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	cLog::Singleton()->Print ("Internal WIN32 Error: %s", lpMsgBuf);

	// Free the buffer.
	LocalFree( lpMsgBuf );
}

/////////////////////////////////////////////////////////////////////////////////////
bool cWIN32Application::RegisterAppClass()
/////////////////////////////////////////////////////////////////////////////////////
{
	WNDCLASSEX	wcex;
	
	ZeroMemory (&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.hInstance		= m_hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= WND_CLASS;
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wcex))
	{
		CheckWIN32Errors();
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cWIN32Application::CreateAppWindow()
/////////////////////////////////////////////////////////////////////////////////////
{
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT rc = {0, 0, m_width, m_height};
	DWORD windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	AdjustWindowRectEx (&rc, windowStyle, 0, windowExtendedStyle);

	m_hWnd = CreateWindowEx(
		windowExtendedStyle,								// Extended style
		WND_CLASS,											// Window class name
		m_title.c_str(),									// Window title
		windowStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,	// Window style
		0,													// X-position
		0,													// Y-position
		rc.right - rc.left,									// Window width
		rc.bottom-rc.top,									// Window height
		NULL,												// Parent window
		NULL,												// Menu
		m_hInstance,										// Instance
		this);												// L-Param (Pass the app pointer)
	
	if(!m_hWnd)
	{
		CheckWIN32Errors();
		return false;
	}

	ShowWindow (m_hWnd, SW_SHOWDEFAULT);
	cLog::Singleton()->Print ("Created WIN32 application");
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cWIN32Application::InitializeApplication()
/////////////////////////////////////////////////////////////////////////////////////
{
	// Register the window class
	if (!RegisterAppClass())
		return false;
	
	// Create the window
	if (!CreateAppWindow())
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cWIN32Application::CloseApplication()
/////////////////////////////////////////////////////////////////////////////////////
{
	// Close the window
	if (m_hWnd)
		DestroyWindow (m_hWnd);
	m_hWnd = 0;

	// Unregister the class
	UnregisterClass (WND_CLASS, m_hInstance);
	LOG()->Print ("Successfully destroyed WIN32 application");

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK cWIN32Application::WndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Static pointer to the application class
	static cWIN32Application *app = NULL;
	
	switch (uMsg)
	{
		// Called on window creation
		case WM_CREATE:
			app = (cWIN32Application*)lParam;
			return 0;

		// Called on window termination
		case WM_CLOSE:
			PostMessage (hWnd, WM_QUIT, 0, 0);
			return 0;

		case WM_SIZE:
			if (cRoot::Singleton()->GetOGLSystem())
				cRoot::Singleton()->GetOGLSystem()->UpdateViewport(LOWORD(lParam), HIWORD(lParam));
			return 0;
	}

	// Default to the default window procedure
	return DefWindowProc (hWnd, uMsg, wParam, lParam);

}

/////////////////////////////////////////////////////////////////////////////////////
bool cWIN32Application::HandleMessages()
/////////////////////////////////////////////////////////////////////////////////////
{
	static MSG msg;

	//if (GetMessage (&msg, m_hWnd, 0, 0))
	if (PeekMessage (&msg, m_hWnd, 0, 0, PM_REMOVE) != 0)
	{
		// Check For WM_QUIT Message
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		else
		{
			TranslateMessage (&msg);
			DispatchMessage(&msg);
		}
	}
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
void cWIN32Application::SetTitle (std::string title)
/////////////////////////////////////////////////////////////////////////////////////
{
	cApplication::SetTitle (title);

	SetWindowText ( m_hWnd, title.c_str() );
}