#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "cTexture.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cTexture::cTexture(void)
	: m_width (0), m_height (0),
		m_texNum (65535)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cTexture::~cTexture(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	glDeleteTextures (1, &m_texNum);
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTexture::SetImage (std::string filename, cImage *image)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_filename = filename;
	return InitializeTexture (image);
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTexture::InitializeTexture (cImage *image)
/////////////////////////////////////////////////////////////////////////////////////
{
	unsigned int format;

	glGenTextures (1, &m_texNum);
	glBindTexture (GL_TEXTURE_2D, m_texNum);

	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST_MIPMAP_LINEAR);

	m_width  = image->GetWidth ();
	m_height = image->GetHeight ();
	
	if (image->GetBPP() == 24)
		format = GL_RGB;
	else
		format = GL_RGBA;
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, format, m_width, 
		m_height, format, GL_UNSIGNED_BYTE, image->GetImage());

	return true;
}