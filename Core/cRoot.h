#pragma once

#include "../Core/cSingleton.h"
#include "../Core/cLog.h"
#include "../Core/cTimer.h"
#include "../File/cFileManager.h"
#include "../Texture/cTextureManager.h"
#include "../Platform/cWIN32Application.h"
#include "../Rendering System/cOGLSystem.h"
#include "../Input System/cDInput.h"
#include "../Input System/cCamera.h"
#include "../Entity/cEntity.h"
#include "../Math/cCatmullRomSpline.h"
#include "../Geometry/cGeometryData.h"
#include "../Models/cMD2Model.h"
#include "../FMod/cSongPlayer.h"
#include "../FMod/cSoundManager.h"

#include <gl/gl.h>
#include <gl/glu.h>


class cRoot : public cSingleton <cRoot>
{
public:
	cRoot(void);
	~cRoot(void);

	cFileManager*		GetFileManager ()		{ return m_fileManager; }
	cTextureManager*	GetTextureManager ()	{ return m_textureManager; }
	cLog*				GetLog ()				{ return m_log; }
	cApplication*		GetApplication ()		{ return m_application; }
	cOGLSystem*			GetOGLSystem ()			{ return m_ogl; }
	cDirectInput*		GetDirectInput ()		{ return m_dinput; }
	cSoundManager*		GetSoundManager ()		{ return m_soundManager; }

	void Update ()								{ m_ogl->SwapScreen(); }
	bool InitializeEngine ();
	virtual bool Run ();

	cTimer*				GetTimer ()				{ return &m_timer; }

protected:
	// Singleton classes
	cFileManager		*m_fileManager;
	cTextureManager		*m_textureManager;
	cLog				*m_log;
	cOGLSystem			*m_ogl;
	cDirectInput		*m_dinput;
	cSoundManager		*m_soundManager;

	cWIN32Application	*m_application;

	cTimer m_timer;
};
