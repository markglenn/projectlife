#pragma once

#include <windows.h>
#include "cImage.h"

#define BITMAP_ID	0x4D42

class cBMPImage : public cImage
{
public:
	cBMPImage (cIFile *file) { LoadTexture (file); }

	cBMPImage(void);
	~cBMPImage(void);

	virtual bool LoadTexture (cIFile *file);

};
