#pragma once
#include "cfileloader.h"

#define PAK_NUMBER ('P' + ('A'<<8) + ('C'<<16) + ('K'<<24))

class cPAKFileLoader :
	public cFileLoader
{
public:
	cPAKFileLoader(void);
	~cPAKFileLoader(void);

	virtual bool InitDirectory (std::string directory);
	virtual unsigned char *ReadFile (std::string filename);

protected:

	struct sHeader
	{
		unsigned int signature;
		unsigned int offset;
		unsigned int length;
	};

	struct sDirectory
	{
		unsigned char filename[56];
		unsigned int position;
		unsigned int length;
	};

	sDirectory *m_dirEntries;
	int			m_numEntries;
	FILE *m_fp;

};
