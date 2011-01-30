#pragma once

#include <string>

#include "../Core/cFactory.h"
#include "cImage.h"

#define UNDEFINED_TEXTURE 65535

class cTexture : public cFactory <cTexture>
{
public:
	cTexture(void);
	~cTexture(void);

	bool SetImage (std::string filename, cImage *image);
	bool IsFile (std::string filename) { return filename == m_filename; }

	unsigned int GetTextureNumber () { return m_texNum; }

	unsigned int GetWidth () { return m_width; }
	unsigned int GetHeight () { return m_height; }


protected:
	bool InitializeTexture (cImage *image);
	std::string m_filename;

	unsigned int m_texNum;
	unsigned int m_width;
	unsigned int m_height;
};
