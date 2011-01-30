#pragma once

#include <windows.h>
#include "../Core/cSingleton.h"

class cTextManager
{
public:
	cTextManager(void);
	~cTextManager(void);

	bool Initialize ();
	void Print (char *str, float x, float y);
	void ClearFont ();

protected:
	HFONT			m_hFont;
	unsigned int	m_base;
};
