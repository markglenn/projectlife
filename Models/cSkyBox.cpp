#include "cSkyBox.h"
#include "../texture/cTextureManager.h"


/////////////////////////////////////////////////////////////////////////////////////
cSkyBox::cSkyBox(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cSkyBox::~cSkyBox(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSkyBox::LoadSkyBox(std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	cTextureManager *tm = cTextureManager::Singleton();

	m_skyTextures[SKY_UP]		= tm->LoadTexture (filename + "up.pcx");
	
	// Test if the first file loaded correctly (assume the rest work is this does)
	if (m_skyTextures[SKY_UP] == -1)
		return false;

	m_skyTextures[SKY_DOWN]		= tm->LoadTexture (filename + "dn.pcx");
	m_skyTextures[SKY_LEFT]		= tm->LoadTexture (filename + "lf.pcx");
	m_skyTextures[SKY_FRONT]	= tm->LoadTexture (filename + "ft.pcx");
	m_skyTextures[SKY_RIGHT]	= tm->LoadTexture (filename + "rt.pcx");
	m_skyTextures[SKY_BACK]		= tm->LoadTexture (filename + "bk.pcx");

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
void cSkyBox::Draw (cCamera &camera)
/////////////////////////////////////////////////////////////////////////////////////
{
	cTextureManager *tm = cTextureManager::Singleton();
	
	// Save our current matrix and attributes
	glPushMatrix ();
	glPushAttrib ( GL_FOG_BIT | GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );

	// Pull out only the rotation matrix
	glLoadMatrixf (camera.GetRotation().GetMatrix().m);

	// Don't write to the depth buffer, disable lighting and fog
	glDisable (GL_FOG);
	glDisable (GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);

	// UP plane
	tm->BindTexture (m_skyTextures[SKY_UP]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin (GL_QUADS);
		glTexCoord2f (1.0f, 1.0f);
		glVertex3f (10.f, 10.f, 10.f);
		glTexCoord2f (1.0f, 0.0f);
		glVertex3f (-10.f, 10.f, 10.f);
		glTexCoord2f (0.0f, 0.0f);
		glVertex3f (-10.f, -10.f, 10.f);
		glTexCoord2f (0.0f, 1.0f);
		glVertex3f (10.f, -10.f, 10.f);
	glEnd ();

	// DOWN plane
	tm->BindTexture (m_skyTextures[SKY_DOWN]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f);
		glVertex3f (10.f, -10.f, -10.f);
		glTexCoord2f (1.0f, 0.0f);
		glVertex3f (-10.f, -10.f, -10.f);
		glTexCoord2f (1.0f, 1.0f);
		glVertex3f (-10.f, 10.f, -10.f);
		glTexCoord2f (0.0f, 1.0f);
		glVertex3f (10.f, 10.f, -10.f);
	glEnd ();

	// LEFT plane
	tm->BindTexture (m_skyTextures[SKY_LEFT]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin (GL_QUADS);
		glTexCoord2f (1.0f, 1.0f);
		glVertex3f (-10.f, -10.f, -10.f);
		glTexCoord2f (1.0f, 0.0f);
		glVertex3f (-10.f, -10.f, 10.f);
		glTexCoord2f (0.0f, 0.0f);
		glVertex3f (-10.f, 10.f, 10.f);
		glTexCoord2f (0.0f, 1.0f);
		glVertex3f (-10.f, 10.f, -10.f);
	glEnd ();

	// FRONT plane
	tm->BindTexture (m_skyTextures[SKY_FRONT]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f);
		glVertex3f (10.f, 10.f, 10.f);
		glTexCoord2f (0.0f, 1.0f);
		glVertex3f (10.f, 10.f, -10.f);
		glTexCoord2f (1.0f, 1.0f);
		glVertex3f (-10.f, 10.f, -10.f);
		glTexCoord2f (1.0f, 0.0f);
		glVertex3f (-10.f, 10.f, 10.f);
	glEnd ();

	// RIGHT plane
	tm->BindTexture (m_skyTextures[SKY_RIGHT]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 0.0f);
		glVertex3f (10.f, -10.f, 10.f);
		glTexCoord2f (0.0f, 1.0f);
		glVertex3f (10.f, -10.f, -10.f);
		glTexCoord2f (1.0f, 1.0f);
		glVertex3f (10.f, 10.f, -10.f);
		glTexCoord2f (1.0f, 0.0f);
		glVertex3f (10.f, 10.f, 10.f);
	glEnd ();

	// BACK plane
	tm->BindTexture (m_skyTextures[SKY_BACK]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBegin (GL_QUADS);
		glTexCoord2f (0.0f, 1.0f);
		glVertex3f (-10.f, -10.f, -10.f);
		glTexCoord2f (1.0f, 1.0f);
		glVertex3f (10.f, -10.f, -10.f);
		glTexCoord2f (1.0f, 0.0f);
		glVertex3f (10.f, -10.f, 10.f);
		glTexCoord2f (0.0f, 0.0f);
		glVertex3f (-10.f, -10.f, 10.f);
	glEnd ();

	// Get back our matrix and attributes
	glPopAttrib ();
	glPopMatrix ();
}