#pragma once

#include "../Core/cSingleton.h"

class cSoundManager : public cSingleton <cSoundManager>
{
public:
	cSoundManager(void);
	~cSoundManager(void);

	bool Initialize ();
	bool DeInitialize ();

private:
	bool m_initialized;
};
