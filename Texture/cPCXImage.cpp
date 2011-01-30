#include "cPCXImage.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

REGISTER_CLASS (cImage, cPCXImage, ".PCX")

/////////////////////////////////////////////////////////////////////////////////////
cPCXImage::cPCXImage(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cPCXImage::~cPCXImage(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
bool cPCXImage::LoadTexture (cIFile* file)
/////////////////////////////////////////////////////////////////////////////////////
{
	unsigned int idx = 0;
	unsigned char c;
	int numRepeat;

	unsigned char *data, pal[768];
	
	if (!file)
		return false;

	file->Read (&m_header, sizeof (PCXHeader));

	// Check if it is a valid ZSoft PCX file
	if (m_header.manufacturer != 10)
		return false;

	m_width = m_header.xmax - m_header.xmin + 1;
	m_height = m_header.ymax - m_header.ymin + 1;
	
	data = new unsigned char[m_height * m_header.bytesPerLine];

	// Decompress the data
	file->Seek (128, SEEK_SET);
	while (idx < (m_width * m_height) )
	{
		file->Read(&c, 1);

		if (c > 0xbf)
		{
			numRepeat = 0x3f & c;
			file->Read(&c, 1);

			for (int i = 0; i < numRepeat; i++)
				data[idx++] = c;
		}

		else
			data[idx++] = c;
	}

	// Move to the palette
	file->Seek (-769, SEEK_END);

	file->Read (&c, 1);
	// Make sure there is a palette
	if (c != 12)
	{
		delete[] data;
		return false;
	}

	file->Read (&pal, 768);

	m_bpp = 24;
	m_image = new unsigned char [m_width * m_height * 3];

	// Insert the palette into the final image
	for (unsigned int i = 0; i < m_width * m_height; i++)
	{
		m_image[(3 * i)]		= pal[(data[i] * 3)];
		m_image[(3 * i) + 1]	= pal[(data[i] * 3) + 1];
		m_image[(3 * i) + 2]	= pal[(data[i] * 3) + 2];
	}

	delete[] data;
	return true;
}
