#include "cbmpimage.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

REGISTER_CLASS (cImage, cBMPImage, ".BMP")

cBMPImage::cBMPImage(void)
{
}

cBMPImage::~cBMPImage(void)
{
}

bool cBMPImage::LoadTexture (cIFile *file)
{
	unsigned char	tempRGB;
	unsigned int	bytesPerRow;
	unsigned int	difference;
	unsigned char	temp[4];
	
	int dy, pos;
	unsigned char	*palette = NULL;

	BITMAPFILEHEADER	bitmapFileHeader;
	BITMAPINFOHEADER	bitmapInfoHeader;

	// File doesn't exist
	if (NULL == file)
		return false;

	// Read the bitmap file header
	file->Read (&bitmapFileHeader, sizeof(BITMAPFILEHEADER));

	// Is valid BMP format
	if (bitmapFileHeader.bfType != BITMAP_ID)
		return false;

	// Read the bitmap information header
	file->Read (&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

	m_width = bitmapInfoHeader.biWidth;
	m_height = bitmapInfoHeader.biHeight;
	m_bpp = bitmapInfoHeader.biBitCount;

	// Find the correct bytes per row
	bytesPerRow = m_width * m_bpp / 8;

	// BMP lines have to be INT (4 bytes) aligned, here's the difference
	difference = (4 - bytesPerRow % 4) % 4;

	if (bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = m_width * m_height * m_bpp / 8;

	m_image = new unsigned char [m_width * m_height * m_bpp / 8];

	if (!m_image)
		return false;

	ZeroMemory (m_image, m_width * m_height * m_bpp / 8);

	// Load in the palette if needed
	if (8 == m_bpp)
	{
		int numColors = 1 << m_bpp;

		palette = new unsigned char [numColors * 4];
		file->Read (&palette, numColors * 4);

		for (int c = 0; c < numColors * 4; c += 4)
		{
			tempRGB			= palette[c];
			palette[c]		= palette[c + 2];
			palette[c + 2]	= tempRGB;
		}
	}

	file->Seek (bitmapFileHeader.bfOffBits, SEEK_SET);

	// Copy over the image
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			dy = (m_height - 1) - y;
			pos = ((dy * m_width) + x) * m_bpp / 8;

			file->Read (&temp, m_bpp / 8);
			m_image[pos]		= temp[2];
			m_image[pos + 1]	= temp[1];
			m_image[pos	+ 2]	= temp[0];
	
			if (32 == m_bpp)
				m_image[pos + 3]	= temp[3];
		}
		file->Seek(difference, SEEK_CUR);
	}		

	return true;
}
