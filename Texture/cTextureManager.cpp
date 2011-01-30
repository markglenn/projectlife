#include <algorithm>

#include "cTextureManager.h"

#include "cBMPImage.h"
#include "../File/cFileManager.h"
#include "../Core/cLog.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cTextureManager::cTextureManager(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	Singleton ();
	glEnable (GL_TEXTURE_2D);
}

/////////////////////////////////////////////////////////////////////////////////////
cTextureManager::~cTextureManager(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Delete the textures from memory
	ClearAll ();
}

/////////////////////////////////////////////////////////////////////////////////////
int cTextureManager::LoadTexture (std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	std::vector <cTexture *>::iterator i;
	std::string	extension;
	cImage		*image;
	cTexture	*texture;
	cIFile		*file;

	// Check to see if this texture is already loaded
	for (unsigned int i = 0; i < m_textures.size(); i++)
		if (m_textures[i]->IsFile (filename))
			return i;
	
	file = cFileManager::Singleton()->OpenFile (filename);

	// Make sure this is a valid file
	if (file == NULL)
		return -1;

	unsigned int pos = filename.find ('.');
	
	// File has no extension
	if (std::string::npos == pos)
		return -1;

	// Extract the uppercase file extension
	extension = filename.substr(pos);
	std::transform (extension.begin(), extension.end(), 
				extension.begin(), toupper);
	
	// Create the image based on the file extension
	image = cFactory<cImage>::Instance().Create(extension.c_str());

	if (!image)
	{
		// Unsupported image format
		cLog::Singleton()->Print ("%s is in an unsupported image format", filename.c_str());
		return -1;
	}

	// Load the image
	if (!image->LoadTexture (file))
	{
		delete image;
		return -1;
	}

	// Close the file
	cFileManager::Singleton()->CloseFile (file);

	// Create the texture from the image
	texture = new cTexture ();
	texture->SetImage (filename, image);

	if (UNDEFINED_TEXTURE == texture->GetTextureNumber())
	{
		delete texture;
		delete image;
		return -1;
	}

	// Place the texture in the first free spot
	int num = GetFreeTexture();
	m_textures[num] = texture;
	
	delete image;

	return num;
}

/////////////////////////////////////////////////////////////////////////////////////
void cTextureManager::ClearAll ()
/////////////////////////////////////////////////////////////////////////////////////
{
	std::vector <cTexture *>::iterator i;

	// Delete any textures still allocated
	for (i = m_textures.begin(); i != m_textures.end(); i++)
		if ((*i) != NULL)
			delete *i;

	// Reset the size of the texture holder
	m_textures.clear();
}

/////////////////////////////////////////////////////////////////////////////////////
void cTextureManager::DeleteTexture (int texNum)
/////////////////////////////////////////////////////////////////////////////////////
{
	// If the texture exists, delete it and mark its spot as free
	if (m_textures[texNum] != NULL)
	{
		delete m_textures[texNum];
		m_textures[texNum] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
int cTextureManager::GetFreeTexture ()
/////////////////////////////////////////////////////////////////////////////////////
{
	// Return at the first unallocated spot in the vector
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		if (m_textures[i] == NULL)
			return i;
	}

	// Create a new spot for the texture
	m_textures.push_back (NULL);
	return m_textures.size() - 1;
}

/////////////////////////////////////////////////////////////////////////////////////
int cTextureManager::LoadTexture (unsigned char *image,	unsigned int width, 
								  unsigned int height,	unsigned int bpp)
/////////////////////////////////////////////////////////////////////////////////////
{
	cImage		cImage;
	int			num;
	cTexture	*texture;

	cImage.SetDimensions(width, height, bpp);
	cImage.SetImage(image);

	texture = new cTexture ();

	// Have to create a unique filename
	std::string filename;

	filename = GetFreeTexture();
	filename += "_UNIQUE_TEXTURE_FILENAME";
	
	texture->SetImage (filename, &cImage);

	if (UNDEFINED_TEXTURE == texture->GetTextureNumber())
		return -1;

	// Place the texture in the first free spot
	num = GetFreeTexture();
	m_textures[num] = texture;
	
	return num;
}