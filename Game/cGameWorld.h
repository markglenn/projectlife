#pragma once

#include "../Core/cRoot.h"
#include "../BSP/cQuake2BSPFile.h"
#include "../Models/cSkybox.h"

class cGameWorld
{
public:
	cGameWorld(void);
	~cGameWorld(void);

	void DrawWorld (cCamera *camera, float deltaTime);
	void HandleCollisions (cEntity *entity);
	bool LoadMap (std::string filename);

protected:
	
	// Level information
	cQuake2BSPFile	m_bsp;
	cSkyBox			m_skybox;

};
