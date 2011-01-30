#include "capplication.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cApplication::cApplication(void)
	: m_width(800), m_height(600), m_bpp(32), m_fullscreen(false),
	  m_hWnd(0)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cApplication::~cApplication(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}