#pragma once
#include "../Core/cSingleton.h"
#include <windows.h>
#include <gl/gl.h>

class cApplication;

class cOGLSystem : public cSingleton <cOGLSystem>
{
public:
	cOGLSystem(void);
	~cOGLSystem(void);

	bool Initialize (cApplication* app);
	void UpdateViewport (unsigned int width, unsigned int height);

	HDC GetHDC () { return m_hDC; }
	HGLRC GetHGLRC () { return m_hRC; }

	__forceinline void SwapScreen () { SwapBuffers (m_hDC); }
	__forceinline void ClearScreen () { glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

protected:
	
	HDC		m_hDC;
	HGLRC	m_hRC;
};
