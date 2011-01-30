#include "ctextmanager.h"
#include "../Rendering System/cOGLSystem.h"

/////////////////////////////////////////////////////////////////////////////////////
cTextManager::cTextManager(void)
	: m_base(0)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cTextManager::~cTextManager(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	ClearFont();
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTextManager::Initialize()
/////////////////////////////////////////////////////////////////////////////////////
{
	// Make sure any previous font is cleared out first
	ClearFont ();

	m_base = glGenLists (96);
	m_hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
							OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
							FF_DONTCARE | DEFAULT_PITCH, "Courier");

	// Make sure it was created successfully
	if (!m_hFont)
		return false;

	// Select a device context for the font
	SelectObject (cOGLSystem::Singleton()->GetHDC(), m_hFont);

	// Prepare the bitmap font
	if (!wglUseFontBitmaps (cOGLSystem::Singleton()->GetHDC(), 32, 96, m_base))
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
void cTextManager::Print(char * str, float x, float y)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (str == NULL)
		return;

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glTranslatef (0, 10, 0);
	
	glRasterPos2f(-0.35f, 0.f);
	glPushAttrib (GL_LIST_BIT);
		glListBase(m_base - 32);
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	glPopAttrib();

	glPopMatrix();
}

/////////////////////////////////////////////////////////////////////////////////////
void cTextManager::ClearFont()
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_base != 0)
		glDeleteLists (m_base, 96);

	m_base = 0;
}