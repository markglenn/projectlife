#include "cJPEGImage.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

// Register the class in the image factory
REGISTER_CLASS (cImage, cJPEGImage, ".JPG")

/////////////////////////////////////////////////////////////////////////////////////
cJPEGImage::cJPEGImage(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cJPEGImage::~cJPEGImage(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
bool cJPEGImage::LoadTexture (cIFile *file)
/////////////////////////////////////////////////////////////////////////////////////
{
	JPEG_CORE_PROPERTIES jcprops;

	// Intialize the IJL
	if (ijlInit(&jcprops) != IJL_OK )
	{
		ijlFree(&jcprops);
		return false;
	}

	//jcprops.JPGBytes = (unsigned char *) data;
	jcprops.JPGBytes = file->GetData ();
	jcprops.JPGSizeBytes = file->Size ();
	jcprops.jquality = 100;

	// Read in the jpeg image
	if ( ijlRead (&jcprops, IJL_JBUFF_READPARAMS) != IJL_OK )
	{
		ijlFree (&jcprops);
		return false;
	}

	m_width = jcprops.JPGWidth;
	m_height = jcprops.JPGHeight;
	IJLIOTYPE mode;

	mode = IJL_JBUFF_READWHOLEIMAGE;
	int nchannels = jcprops.JPGChannels;

	m_bpp = nchannels * 8;

	// Allocate the image buffer
	m_image = new unsigned char[m_width * m_height * nchannels];
	
	// If there was a memory error
	if ( !m_image )
	{
		ijlFree (&jcprops);
		return false;
	}

	// Setup the JPEG Core properties
	jcprops.DIBWidth = m_width;
	jcprops.DIBHeight = m_height;
	jcprops.DIBChannels = nchannels;
	jcprops.DIBPadBytes = 0;
	jcprops.DIBBytes = (unsigned char *)m_image;

	if ( jcprops.JPGChannels == 3 )
	{
		jcprops.DIBColor = IJL_RGB;
		jcprops.JPGColor = IJL_YCBCR;
		jcprops.JPGSubsampling = IJL_411;
		jcprops.DIBSubsampling = (IJL_DIBSUBSAMPLING) 0;
	}
	else
	{
		jcprops.DIBColor = IJL_G;
		jcprops.JPGColor = IJL_G;
		jcprops.JPGSubsampling = (IJL_JPGSUBSAMPLING) 0;
		jcprops.DIBSubsampling = (IJL_DIBSUBSAMPLING) 0;
	}

	if (ijlRead(&jcprops, mode) != IJL_OK)
	{
		ijlFree(&jcprops);
		return false;
	}
	
	if ( ijlFree(&jcprops) != IJL_OK ) return false;

	return true;
}