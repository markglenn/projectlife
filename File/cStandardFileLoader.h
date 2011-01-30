#pragma once

#include "cFileLoader.h"

class cStandardFileLoader : public cFileLoader
{
public:
	cStandardFileLoader();
	~cStandardFileLoader(void);

	virtual bool InitDirectory (std::string directory);
	virtual unsigned char* ReadFile (std::string filename);
};
