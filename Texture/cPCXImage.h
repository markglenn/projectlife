#pragma once
#include "cImage.h"

class cPCXImage : public cImage
{
public:
	cPCXImage (cIFile *file) { LoadTexture (file); }
	
	cPCXImage(void);
	~cPCXImage(void);

	virtual bool LoadTexture (cIFile *file);

protected:
	struct PCXHeader {
		char manufacturer;
		char version;
		char encoding;
		char bitsPerPixel;
		short xmin, ymin, xmax, ymax;
		short hdpi;
		short vdpi;
		char colorMap[48];
		char reserved;
		char nPlanes;
		short bytesPerLine;
		short paletteInfo;
		short hScreenSize;
		short vScreenSize;
		char unused[54];
	} m_header;

};
