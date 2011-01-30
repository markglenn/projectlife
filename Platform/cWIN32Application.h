#pragma once

#include <windows.h>
#include "..\Core\cApplication.h"

class cWIN32Application : public cApplication
{
public:
	cWIN32Application(void);
	~cWIN32Application(void);

	void SetHInstance (HINSTANCE hInstance) { m_hInstance = hInstance; }

	bool RegisterAppClass ();
	bool CreateAppWindow ();
	virtual bool InitializeApplication();
	virtual bool CloseApplication ();

	virtual void SetTitle (std::string title);
	virtual bool HandleMessages ();

	static LRESULT CALLBACK WndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void CheckWIN32Errors ();
};
