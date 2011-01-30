#include "cwalimage.h"
#include "../File/cFileManager.h"

bool cWALImage::m_bPalette = false;
unsigned char cWALImage::m_palette[768];

REGISTER_CLASS (cImage, cWALImage, ".WAL")

cWALImage::cWALImage(void)
{
}

cWALImage::~cWALImage(void)
{
}

bool cWALImage::LoadTexture(cIFile *file)
{
	unsigned char *data;

	// Make sure the palette is loaded
	if (!cWALImage::m_bPalette)
	{
		cIFile *pal = cFileManager::Singleton()->OpenFile ("quake2.pal");

		if (!pal)
			return false;

		pal->Read (cWALImage::m_palette, 768);
		cFileManager::Singleton()->CloseFile(pal);

		cWALImage::m_bPalette = true;
	}

	sWalHeader header;

	file->Read (&header, sizeof(sWalHeader));
	
	m_width = header.width;
	m_height = header.height;

	m_bpp = 24;
	m_image = new unsigned char [m_width * m_height * 3];
	data = new unsigned char [m_width * m_height];

	file->Seek (header.offset[0], SEEK_SET);
	file->Read (data, m_width * m_height);

	for (int i = 0; i < m_width * m_height; i++)
	{
		m_image[(3 * i)    ] = cWALImage::m_palette[(data[i] * 3)    ];
		m_image[(3 * i) + 1] = cWALImage::m_palette[(data[i] * 3) + 1];
		m_image[(3 * i) + 2] = cWALImage::m_palette[(data[i] * 3) + 2];
	}

	delete[] data;
	return true;
}