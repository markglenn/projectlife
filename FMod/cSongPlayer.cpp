#include "cSongPlayer.h"
#include "cSoundManager.h"

#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cSongPlayer::cSongPlayer(void)
	: m_file(0), m_sample(0), m_channel(-1)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_channel = FSOUND_FREE;
}

/////////////////////////////////////////////////////////////////////////////////////
cSongPlayer::~cSongPlayer(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_file)
		cFileManager::Singleton()->CloseFile (m_file);
	if (m_sample)
		FSOUND_Sample_Free (m_sample);
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSongPlayer::LoadSong (std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	cFileManager *fmanager = cFileManager::Singleton();
	
	if (!cSoundManager::Singleton()->Initialize ())
		return false;

	// Try opening the file
	m_filename = filename;
	m_file = fmanager->OpenFile (m_filename);

	// If the file doesn't exist, exit
	if (!m_file)
		return false;

	m_sample = FSOUND_Sample_Load (m_channel, (const char *)m_file->GetData(), 
		FSOUND_LOADMEMORY, m_file->Size());

	// If there was a problem loading the file, exit
	if (!m_sample)
	{
		fmanager->CloseFile (m_file);
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSongPlayer::Play ()
/////////////////////////////////////////////////////////////////////////////////////
{
	if ((m_channel = FSOUND_PlaySound (m_channel, m_sample)) != -1)
		return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSongPlayer::Loop ()
/////////////////////////////////////////////////////////////////////////////////////
{
	FSOUND_Sample_SetMode(m_sample, FSOUND_LOOP_NORMAL);
	Play();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cSongPlayer::Stop ()
/////////////////////////////////////////////////////////////////////////////////////
{
	return FSOUND_StopSound (m_channel);
	FSOUND_Sample_SetMode (m_sample, FSOUND_LOOP_OFF);
}