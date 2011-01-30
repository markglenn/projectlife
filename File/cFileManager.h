#pragma once

#include <list>
#include <vector>

#include "cFileLoader.h"
#include "cStandardFileLoader.h"
#include "cZipFileLoader.h"
#include "cIFile.h"
#include "../Core/cSingleton.h"

class cFileManager : public cSingleton <cFileManager>
{
public:
	cFileManager(void);
	~cFileManager(void);

	void AddDirectory (std::string directory);
	bool RemoveDirectory (std::string directory);

	cIFile* OpenFile (std::string filename);
	bool CloseFile (cIFile *IFile);

	bool FileExists (std::string filename);

protected:
	std::vector <cFileLoader *> m_loaders;
	std::list <cIFile *>		m_ifiles;
};
