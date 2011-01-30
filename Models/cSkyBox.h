#pragma once

#include <string>
#include "../Input System/cCamera.h"

class cSkyBox
{
public:
	cSkyBox(void);
	~cSkyBox(void);

	bool LoadSkyBox (std::string filename);
	void Draw (cCamera &camera);

private:
	typedef enum
	{
		SKY_UP,		SKY_DOWN,	SKY_LEFT, 
		SKY_FRONT,	SKY_RIGHT,	SKY_BACK,
		MAX_SKY_DIRECTIONS
	} eSkyDirection;

	int m_skyTextures[MAX_SKY_DIRECTIONS];
};
