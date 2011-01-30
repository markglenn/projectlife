#pragma once

#include <string>

#ifdef WIN32
#	include <windows.h>
#endif

/** The window creation class
    @remarks
		This is the base class for the main window.  It is subclassed
		for each platform.  As of now, there is no other platform
		supported besides windows.  This may change, but not at this time.
		The class also handles all the window messages that come to 
		the main window.  As of now	there is now way of creating multiple
		windows, and right now there is no plan to implement this feature.
*/
class cApplication
{
public:
	cApplication(void);
	~cApplication(void);

	/// Creates the main window, and initializes anything that is needed	
	virtual bool InitializeApplication ()	{ return false; }
	/// Closes the message hander and window
	virtual bool CloseApplication ()		{ return false; }
	/// Handles the messages passed in by the windows manager
	virtual bool HandleMessages ()			{ return false; }
	// Setters
	/// Sets the title of the window
	virtual void SetTitle (std::string title)				{ m_title = title; }
	/// Sets the dimensions of the window
	void SetDimensions (unsigned int width, unsigned int height, unsigned int bpp = 32)
		{ m_width = width; m_height = height; m_bpp = bpp; }

#ifdef WIN32
	/** Sets the HInstance of the application.
		@param hInstance The HINSTANCE passed in from WinMain ()
	*/			
	void			SetHInstance (HINSTANCE hInstance) { m_hInstance = hInstance; }
	HWND			GetHWnd ()		{ return m_hWnd; }
	HINSTANCE		GetHInstance () { return m_hInstance; }
#endif

	// Getters
	/// Returns the width of the window
	unsigned int	GetWidth ()		{ return m_width;	}
	/// Returns the height of the window
	unsigned int	GetHeight ()	{ return m_height;	}
	/// Returns the window's bitcount
	unsigned int	GetBPP ()		{ return m_bpp;		}

protected:
	/// Title of the window
	std::string		m_title;
	/// Width of the window
	unsigned int	m_width;
	/// Height of the window
	unsigned int	m_height;
	/// Bitcount of the window
	unsigned int	m_bpp;
	/// True if fullscreen
	bool			m_fullscreen;

#ifdef WIN32
	HWND			m_hWnd;
	HINSTANCE		m_hInstance;
#endif
};
