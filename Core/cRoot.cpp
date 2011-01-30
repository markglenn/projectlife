#include "cRoot.h"
#include "../Platform/cWIN32Application.h"
#include "../Geometry/cVertex.h"

#include "../Math/cQuaternion.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cRoot::cRoot(void)
	: m_application(0), m_fileManager(0), m_textureManager(0), m_log(0), m_ogl(0)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Create the singleton classes
	m_log				= new cLog ();
	m_fileManager		= new cFileManager ();
	m_textureManager	= new cTextureManager ();
	m_ogl				= new cOGLSystem ();
	m_dinput			= new cDirectInput ();
	m_soundManager		= new cSoundManager ();
	
	// TODO: Choose a platform
	m_application		= new cWIN32Application ();
}

/////////////////////////////////////////////////////////////////////////////////////
cRoot::~cRoot(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_application->CloseApplication ();
	
	// Free the memory of the singleton classes
	if (m_soundManager)
		delete m_soundManager;
	if (m_fileManager)
		delete m_fileManager;
	if (m_textureManager)
		delete m_textureManager;
	if (m_ogl)
		delete m_ogl;
	if (m_application)
		delete m_application;
	if (m_dinput)
	{
		m_dinput->Shutdown ();
		delete m_dinput;
	}

	if (m_log)
	{
		m_log->Print ("Stopping the Lightning Fast Engine");
		delete m_log;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
bool cRoot::InitializeEngine()
/////////////////////////////////////////////////////////////////////////////////////
{
	m_log->Print ("Starting the Lightning Fast Engine");

	m_application->InitializeApplication();

	// Initialize DirectInput
	m_dinput->Initialize (m_application->GetHWnd(), m_application->GetHInstance(),
			true, IS_USEKEYBOARD | IS_USEMOUSE);
	m_dinput->AcquireAll ();

	// Initialize the OGL system
	if (!m_ogl->Initialize (m_application))
	{
		m_log->Print ("Could not initialize the OGL system");
		return false;
	}

	// Initialize the timer
	if (!m_timer.Init())
	{
		m_log->Print ("Could not initialize high frequency timer");
		return false;
	}
	
	m_log->Print ("Successfully initialized the engine");
		
	glLoadIdentity();

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cRoot::Run()
/////////////////////////////////////////////////////////////////////////////////////
{
	static int count = 0;
	
	if (!m_application->HandleMessages())
		return false;

	// Do input stuff
	m_dinput->Update ();

	// Do frame count
	/*if (count++ > 100000)
	{
		char message[1000];

		sprintf(message, "Frame rate: %f", m_timer.GetFPS(100));

		m_application->SetTitle (message);
		count = 0;
	}*/
	
	m_ogl->ClearScreen();
	return true;

}

