#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "../Core/cRoot.h"
#include "../Rendering System/extgl.h"

#include "cOGLSystem.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

#pragma comment( lib, "opengl32.lib" )	// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )		// Search For GLu32.lib While Linking

/////////////////////////////////////////////////////////////////////////////////////
cOGLSystem::cOGLSystem(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cOGLSystem::~cOGLSystem(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
bool cOGLSystem::Initialize (cApplication *app)
/////////////////////////////////////////////////////////////////////////////////////
{
#ifdef WIN32
	GLuint PixelFormat;													// Will Hold The Selected Pixel Format
	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof (PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW |											// Format Must Support Window
		PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER |
		PFD_GENERIC_ACCELERATED,										// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		app->GetBPP(),										 			// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		32,																// 32Bit Z-Buffer (Depth Buffer)  
		0,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	m_hDC = GetDC (app->GetHWnd());										// Grab A Device Context For This Window
	if (m_hDC == 0)												// Did We Get A Device Context?
	{
		// Failed
		DestroyWindow (app->GetHWnd());									// Destroy The Window
		return FALSE;											// Return False
	}

	PixelFormat = ChoosePixelFormat (m_hDC, &pfd);				// Find A Compatible Pixel Format

	if (PixelFormat == 0)										// Did We Find A Compatible Format?
	{
		// Failed
		ReleaseDC (app->GetHWnd(), m_hDC);								// Release Our Device Context
		m_hDC = 0;												// Zero The Device Context
		DestroyWindow (app->GetHWnd());									// Destroy The Window
		return FALSE;													// Return False
	}

	if (SetPixelFormat (m_hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{
		// Failed
		ReleaseDC (app->GetHWnd(), m_hDC);								// Release Our Device Context
		m_hDC = 0;												// Zero The Device Context
		DestroyWindow (app->GetHWnd());									// Destroy The Window
		return FALSE;											// Return False
	}

	m_hRC = wglCreateContext (m_hDC);							// Try To Get A Rendering Context
	if (m_hRC == 0)												// Did We Get A Rendering Context?
	{
		// Failed
		ReleaseDC (app->GetHWnd(), m_hDC);								// Release Our Device Context
		m_hDC = 0;												// Zero The Device Context
		DestroyWindow (app->GetHWnd());									// Destroy The Window
		return FALSE;											// Return False
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (m_hDC, m_hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (m_hRC);								// Delete The Rendering Context
		m_hRC = 0;												// Zero The Rendering Context
		ReleaseDC (app->GetHWnd(), m_hDC);								// Release Our Device Context
		m_hDC = 0;												// Zero The Device Context
		DestroyWindow (app->GetHWnd());									// Destroy The Window
		return FALSE;											// Return False
	}
	
	UpdateViewport (app->GetWidth(), app->GetHeight());
#endif

	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);
	
	glCullFace (GL_BACK);
	glEnable (GL_DEPTH_TEST);
	glFrontFace	(GL_CW);

	extgl_Initialize();
	return true;


}

/////////////////////////////////////////////////////////////////////////////////////
void cOGLSystem::UpdateViewport (unsigned int width, unsigned int height)
/////////////////////////////////////////////////////////////////////////////////////
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));

	gluPerspective(45.0f, (GLfloat)(width)/(GLfloat)(height), 
		1.0f, 10000.0f);

	glMatrixMode (GL_MODELVIEW);
}