#include "cSoundManager.h"
#include "../Core/cLog.h"

#include "fmod.h"
#include "fmod_errors.h"

/////////////////////////////////////////////////////////////////////////////////////
cSoundManager::cSoundManager(void)
: m_initialized (0)
/////////////////////////////////////////////////////////////////////////////////////
{

}

/////////////////////////////////////////////////////////////////////////////////////
cSoundManager::~cSoundManager(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	DeInitialize ();
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSoundManager::Initialize()
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_initialized)
		return true;

	// Check the version number
	if (FSOUND_GetVersion() < FMOD_VERSION)
	{
		LOG()->Print ("Error : You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
		return false;
	}

	// Initialize to 44kHz, 64bit
	if (!FSOUND_Init (44100, 64, FSOUND_INIT_GLOBALFOCUS))
	{
		LOG()->Print ("%s\n", FMOD_ErrorString(FSOUND_GetError()));
		return false;
	}

	LOG()->Print ("Successfully initialized the FMOD sound manager.");
	m_initialized = true;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSoundManager::DeInitialize()
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_initialized)
	{
		FSOUND_Close ();
		m_initialized = false;
		LOG()->Print ("Successfully de-initialized the FMOD sound manager.");
	}
	return true;
}