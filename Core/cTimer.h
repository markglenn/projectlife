#pragma once

#include <windows.h>

class cTimer
{
public:
	cTimer(void);
	~cTimer(void);

	bool Init ();
	float GetElapsedSeconds ();
	float GetFPS (unsigned long numFrames = 1);
	float LockFPS (unsigned int targetFPS);

private:
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_ticksPerSecond;
};
