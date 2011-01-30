#include "cConfigLoader.h"
#include "../file/cFileManager.h"
#include "../Memory/mmgr.h"

cConfigLoader::cConfigLoader(void)
{
}

cConfigLoader::~cConfigLoader(void)
{
}

std::string cConfigLoader::StripComments (std::string line)
{
	int pos1 = line.find ("#");
	int pos2;

	// Strip out the comments
	if (pos1 != std::string::npos)
		line.assign (line.substr(0, pos1));

	// If the string is now blank, just return
	if (line.size() == 0)
		return line;

	// Remove the spaces
	line.assign(line.substr(line.find_first_not_of(" "), line.find_last_not_of(" ") + 1));

	// Remove the tabs
	return (line.substr(line.find_first_not_of("\x09"), line.find_last_not_of("\x09") + 1));

}

bool cConfigLoader::ParseFile (std::string filename)
{
	std::string line, name, value;

	// Open the file in the filemanager
	cFileManager *fmanager = cFileManager::Singleton();
	cIFile *file = fmanager->OpenFile(filename);

	// If the file doesn't exist, error out
	if (!file)
		return false;

	do
	{
		line = StripComments (file->GetLine());

		//  Add config name and value to map
		if (line.size() != 0)
		{
			name = line.substr(0,line.find_first_of(" "));
			value = line.substr(line.find_first_of(" ")+1, line.length());
			m_values.insert ( std::make_pair ( std::string(name), std::string(value)) );
		}
	}
	while (!file->Eof ());
	
	// Close the file in the filemanager
 	fmanager->CloseFile(file);

	return true;
}

int cConfigLoader::GetInteger (std::string name)
{
	return atoi(m_values[name].c_str());
}

float cConfigLoader::GetFloat (std::string name)
{
	return atof(m_values[name].c_str());
}

std::string cConfigLoader::GetString (std::string name)
{
	return m_values[name];
}


