#pragma once
#include "cImage.h"
#include "../IJL/ijl.h"

class cJPEGImage : public cImage
{
public:
	cJPEGImage (cIFile *file) { LoadTexture (file); }
	
	cJPEGImage(void);
	~cJPEGImage(void);

	virtual bool LoadTexture (cIFile *file);
};
