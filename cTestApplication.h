#pragma once

#include "Core/cRoot.h"
#include "Game/cGameWorld.h"
#include "Entity/cPlayerEntity.h"

class cTestApplication
{
public:
	cTestApplication(void);
	~cTestApplication(void);

	bool Run ();
	bool HandleInput ();
	bool InitializeEngine (HINSTANCE hInstance);

private:
	// Root class
	cRoot			m_root;

	// World
	cGameWorld		m_world;

	// Player stuff
	cPlayerEntity	m_player;
	cCamera			m_camera;

	// Movement information
	float m_landSpeed;
	float m_airMoveMult;
	float m_currentMovementSpeed;

};
