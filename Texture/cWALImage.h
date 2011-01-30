#pragma once
#include "cimage.h"

class cWALImage : public cImage
{
public:
	cWALImage(void);
	~cWALImage(void);

	virtual bool LoadTexture (cIFile *file);

protected:
	struct sWalHeader
	{
		char	name[32];
		unsigned int	width;
		unsigned int	height;

		unsigned int	offset[4];
		unsigned char	nextTexture[32];
		unsigned int	flags, contents, value;
	};
private:
	static bool m_bPalette;
	static unsigned char m_palette[768];
};
