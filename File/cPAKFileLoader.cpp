#include <algorithm>
#include "cpakfileloader.h"

#include "../Memory/mmgr.h"

REGISTER_CLASS (cFileLoader, cPAKFileLoader, ".PAK")

/////////////////////////////////////////////////////////////////////////////////////
cPAKFileLoader::cPAKFileLoader(void)
	: m_fp(0), m_dirEntries(0), m_numEntries(0)
/////////////////////////////////////////////////////////////////////////////////////
{
	cFileLoader ();
}

/////////////////////////////////////////////////////////////////////////////////////
cPAKFileLoader::~cPAKFileLoader(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_fp)
		fclose (m_fp);

	if (m_dirEntries)
		delete[] m_dirEntries;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cPAKFileLoader::InitDirectory(std::string directory)
/////////////////////////////////////////////////////////////////////////////////////
{
	sHeader header;
	m_directory = directory;

	// Open the file (directory)
	m_fp = fopen (directory.c_str(), "rb");
	if (m_fp == NULL)
		return false;

	// Read in the header
	fread (&header, sizeof(sHeader), 1, m_fp);

	if (header.signature != PAK_NUMBER)
	{
		fclose (m_fp);
		m_fp = NULL;
		return false;
	}

	m_numEntries = header.length / sizeof (sDirectory);

	fseek (m_fp, header.offset, SEEK_SET);

	// Read in the entries
	m_dirEntries = new sDirectory[m_numEntries];
	fread (m_dirEntries, sizeof(sDirectory), m_numEntries, m_fp);

	for (int i = 0; i < m_numEntries; i++)
	{
		for (int j = 0; j < 56; j++)
		{
			// Convert UNIX slashes to DOS backslashes
			if (m_dirEntries[i].filename[j] == '\\')
				m_dirEntries[i].filename[j] = '/';

			// Make everything lowercase
			m_dirEntries[i].filename[j] = tolower(m_dirEntries[i].filename[j]);
		}
	}
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
unsigned char* cPAKFileLoader::ReadFile (std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	int file = -1;
	unsigned char *data;

	if (!m_fp)
		return NULL;

	std::transform (filename.begin(), filename.end(), filename.begin(), tolower);

	for (int i = 0; i < m_numEntries; i++)
	{
		if (strncmp ((char *)m_dirEntries[i].filename, filename.c_str(), 56) == 0)
		{
			m_filesize = m_dirEntries[i].length;
			fseek (m_fp, m_dirEntries[i].position, SEEK_SET);

			data = new unsigned char [m_filesize];
			fread (data, m_filesize, 1, m_fp);
			return data;
		}
	}

	return NULL;
}