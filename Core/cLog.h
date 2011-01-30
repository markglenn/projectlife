#pragma once
#include <stdio.h>

#include "cSingleton.h"

#define LOG() cLog::Singleton()

class cLog : public cSingleton <cLog>
{
public:
	cLog();
	~cLog(void) {Shutdown(); }

	bool Print (const char *szText, ...);

protected:
	FILE *m_file;

	bool Initialize ();
	bool Shutdown ();
};
