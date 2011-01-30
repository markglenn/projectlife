#include "cimage.h"
#include "../Core/cRoot.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

cImage::cImage(void)
	: m_image(0), m_width(0), m_height(0), m_bpp(0)
{
}

cImage::~cImage(void)
{
	if (m_image)
		delete[] m_image;
}

void cImage::ResizeImage(unsigned int width, unsigned int height)
{
	float ratio_w = (float)m_width / (float)width;
	float ratio_h = (float)m_height / (float)height;

	unsigned char *data = new unsigned char [width * height * 3];
	char* d = (char*)data;

	for (int y = 0; y < height; y++)
	{
		int j = (int)(y * ratio_h);
		for (int x = 0; x < width; x++)
		{
			int i = (int)(x * ratio_w);

			char *s = ((char *)m_image) + ((j * m_width) + i) * 3;

			*d = *s; d++; s++;
			*d = *s; d++; s++;
			*d = *s; d++; s++;
		}
	}

	delete[] m_image;
	m_image = data;

	m_width = width;
	m_height = height;
}