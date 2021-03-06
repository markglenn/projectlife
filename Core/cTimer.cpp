#include "cTimer.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cTimer::cTimer(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cTimer::~cTimer(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTimer::Init ()
/////////////////////////////////////////////////////////////////////////////////////
{
	if (!QueryPerformanceFrequency(&m_ticksPerSecond))
		return false;

	QueryPerformanceCounter(&m_startTime);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
float cTimer::GetElapsedSeconds()
/////////////////////////////////////////////////////////////////////////////////////
{
	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);

	float seconds = ((float)currentTime.QuadPart - (float)s_lastTime.QuadPart) /
				(float)m_ticksPerSecond.QuadPart;

	s_lastTime = currentTime;

	return seconds;
}

/////////////////////////////////////////////////////////////////////////////////////
float cTimer::GetFPS (unsigned long numFrames)
/////////////////////////////////////////////////////////////////////////////////////
{
	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);

	float fps = (float)numFrames * (float)m_ticksPerSecond.QuadPart /
				((float)currentTime.QuadPart - (float)s_lastTime.QuadPart);

	s_lastTime = currentTime;

	return fps;
}

/////////////////////////////////////////////////////////////////////////////////////
float cTimer::LockFPS(unsigned int targetFPS)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (targetFPS == 0)
		targetFPS = 1;

	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;
	float fps;

	do
	{
		QueryPerformanceCounter(&currentTime);
		fps = (float)m_ticksPerSecond.QuadPart /
					((float)currentTime.QuadPart - (float)s_lastTime.QuadPart);
		
	} while (fps > (float)targetFPS);

	s_lastTime = currentTime;

	return fps;
}