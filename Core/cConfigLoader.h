#pragma once
#include <string>
#include <map>
#include "../Memory/mmgr.h"

class cConfigLoader
{
public:
	cConfigLoader(void);
	~cConfigLoader(void);

	bool ParseFile (std::string filename);

	int GetInteger (std::string name);
	float GetFloat (std::string name);
	std::string GetString (std::string name);

protected:

	std::string StripComments (std::string line);
	std::map <std::string, std::string> m_values;
};
