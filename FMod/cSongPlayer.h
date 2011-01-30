#pragma once

#include <string>
#include "../File/cFileManager.h"
#include "fmod.h"
#include "fmod_errors.h"

class cSongPlayer
{
public:
	cSongPlayer(void);
	~cSongPlayer(void);

	bool LoadSong (std::string filename);

	bool Play ();
	bool Loop ();
	bool Stop ();

private:
	std::string m_filename;
	cIFile *m_file;
	FSOUND_SAMPLE *m_sample;
	int m_channel;

};
