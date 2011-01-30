#include <algorithm>
#include "../Core/cRoot.h"
#include "cFileManager.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"
/////////////////////////////////////////////////////////////////////////////////////
cFileManager::cFileManager(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Make the compiler compile the singleton class for this object
	cFileManager::Singleton();
}

/////////////////////////////////////////////////////////////////////////////////////
cFileManager::~cFileManager(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Delete all the loaders in the vector
	for (int n = 0; n < m_loaders.size(); n++)
		delete m_loaders[n];

	for (std::list <cIFile *>::iterator i = m_ifiles.begin(); i != m_ifiles.end(); i++)
		delete (*i);

}

/////////////////////////////////////////////////////////////////////////////////////
void cFileManager::AddDirectory (std::string directory)
/////////////////////////////////////////////////////////////////////////////////////
{
	std::string extension = "";
	cFileLoader *fl;
    
	// Check the directory format
	if (directory.find (".") != std::string::npos)
		extension = directory.substr (directory.find("."));

	// Make the extension all uppercase
	std::transform (extension.begin(), extension.end(), 
			extension.begin(), toupper);

	// Create the file loader based on the extension
	fl = cFactory<cFileLoader>::Instance().Create(extension);

	// If the file extension loader doesn't exist, error out
	if (!fl)
	{
		cLog::Singleton()->Print ("Couldn't find a loader to load %s.", 
			directory.c_str());

		return;
	}

	// Initialize the file loader and add it to the loader list
	if (!fl->InitDirectory(directory))
		LOG()->Print ("Couldn't initialize the directory %s", directory.c_str());
	m_loaders.push_back (fl);
}

/////////////////////////////////////////////////////////////////////////////////////
cIFile* cFileManager::OpenFile (std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	std::vector <cFileLoader *>::iterator i;
	cIFile *ifile;
	long size;
	unsigned char* data;

	// Loop through all the loaders
	for (i = m_loaders.begin(); i != m_loaders.end(); i++)
	{
		// Try to load the file in the current loader
		data = (*i)->ReadFile (filename);
		
		// If the file exists
		if (data != NULL)
		{
			// Create the input file
			size = (*i)->GetFileSize();
			ifile = new cIFile (filename, data, size);
			
			// Add the input file to the open file list
			m_ifiles.push_back (ifile);
			return ifile;
		}
	}

	// File did not exist, return NULL
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cFileManager::CloseFile (cIFile *ifile)
/////////////////////////////////////////////////////////////////////////////////////
{
	std::list <cIFile *>::iterator i = m_ifiles.begin();

	// Try to find the file in the open file list
	while (i != m_ifiles.end())
	{
		// If this is the right file
		if ((*i) == ifile)
		{
			// Delete the open file object (does not delete the file)
			delete ifile;

			// Remove the object from the open file list
			m_ifiles.erase(i);
			return true;
		}
		i++;
	}

	// Couldn't close the file
	LOG()->Print("Could not close file: %s", ifile->GetFilename().c_str());
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cFileManager::FileExists (std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	return true;
}