#pragma once

#include "..\Core\cFactory.h"

#include "..\File\cIFile.h"

class cImage : cFactory <cImage>
{
public:
	cImage(void);
	~cImage(void);

	virtual bool LoadTexture (cIFile *file) { return false; }

	unsigned int GetWidth()		{ return m_width; }
	unsigned int GetHeight()	{ return m_height; }
	unsigned int GetBPP()		{ return m_bpp; }

	unsigned char *GetImage()	{ return m_image; }

	// Setters
	void SetImage (unsigned char *image)
	{
		m_image = new unsigned char [m_width * m_height * m_bpp / 8];
		memcpy (m_image, image, m_width * m_height * m_bpp / 8);
	}
	void SetDimensions (unsigned int width, unsigned int height, unsigned int bpp)
		{ m_width = width; m_height = height; m_bpp = bpp; }


	void ResizeImage (unsigned int width, unsigned int height);

protected:

	unsigned char *m_image;
	
	unsigned int m_width, m_height;
	unsigned int m_bpp;
};
