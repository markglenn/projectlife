#pragma once
#include "centity.h"

#include <string>
#include "../FMod/cSongPlayer.h"

class cPlayerEntity :
	public cEntity
{
public:
	cPlayerEntity(void);
	~cPlayerEntity(void);
	virtual bool Simulate (float time);
	virtual void ForceRelative (cVector& direction);

	void Jump (float speed);

	void LoadSounds (std::string path);

protected:
	cSongPlayer jumpWave;
	cSongPlayer steps[4];

	int m_currStep;
};
