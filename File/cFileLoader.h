#pragma once
#include <string>

#include "../Core/cFactory.h"

class cFileLoader : public cFactory <cFileLoader>
{
public:
	cFileLoader();
	~cFileLoader(void);

	virtual bool InitDirectory (std::string directory);
    virtual unsigned char *ReadFile (std::string filename) { return NULL; }
	
	std::string GetDirectory() { return m_directory; }
	long	GetFileSize () { return m_filesize; }

protected:
	void ClearMemory ();

	std::string		m_directory;
	long m_filesize;
};
