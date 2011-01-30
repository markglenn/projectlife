#include "cTestApplication.h"
#include "Core\cConfigLoader.h"

// Include Paul Nettle's memory manager
#include "Memory/mmgr.h"

#define DEBUG_MESSAGES
#define PLAY_MUSIC

/////////////////////////////////////////////////////////////////////////////////////
cTestApplication::cTestApplication(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cTestApplication::~cTestApplication(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTestApplication::InitializeEngine(HINSTANCE hInstance)
/////////////////////////////////////////////////////////////////////////////////////
{
	cConfigLoader config;

	// Set up the file system
	m_root.GetFileManager()->AddDirectory("");

	// Parse the config file
	config.ParseFile ("life.txt");

	// Get the quake directory and load the PAK file
	std::string quakeDir = config.GetString ("q2dir");
	m_root.GetFileManager()->AddDirectory(quakeDir + "\\baseq2\\pak0.pak");
	
	// Get player speeds
	m_landSpeed = config.GetFloat ("landSpeed");
	m_airMoveMult = config.GetFloat ("airMoveMult");
	int width = config.GetInteger ("width");
	int height = config.GetInteger ("height");

	// Get the application from the root class
	cApplication *app = m_root.GetApplication();

	// Initialize the applications title and size 
	app->SetHInstance (hInstance);
	app->SetTitle ("Project LIFE v1.0");
	app->SetDimensions(width, height);

	// Finish initializing the engine
	m_root.InitializeEngine();


	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTestApplication::HandleInput()
/////////////////////////////////////////////////////////////////////////////////////
{
	int dx, dy;

	static cDirectInput *dinput = m_root.GetDirectInput();
	static cVector angle(90, 0, 0);
	cVector direction;
	
	direction = 0;
	// Check keypresses
	if (dinput->KeyDown (DIK_UP))
		direction += cVector (0, 0, -m_currentMovementSpeed);
	if (dinput->KeyDown (DIK_DOWN))
		direction += cVector (0, 0, m_currentMovementSpeed);
	if (dinput->KeyDown (DIK_LEFT))
		direction += cVector (-m_currentMovementSpeed, 0, 0);
	if (dinput->KeyDown (DIK_RIGHT))
		direction += cVector (m_currentMovementSpeed, 0, 0);

	// Check if the user quit	
	if (dinput->KeyDown(DIK_ESCAPE))
		return false;

	// Check mouse movement
	dinput->GetMouseMovement(dx, dy);

	// Set the player angle
	angle += cVector (float(dy) / 2.f, 0, float(-dx) / 2.f);
	m_player.SetAngle (cQuaternion (angle.x, angle.y, angle.z));

	// If the direction vector has changed, move the player that direction
	if (direction != cVector (0,0,0))
		m_player.ForceRelative(direction);

	// Test for the jump key
	if (dinput->KeyDown (DIK_RSHIFT))
		m_player.Jump (-300);
		
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cTestApplication::Run ()
/////////////////////////////////////////////////////////////////////////////////////
{

	cSongPlayer sPlayer;
	float time;

	cMD2Model gun, monster;

	// Load in the map
	if (!m_world.LoadMap("maps/base1.bsp"))
	{
		LOG()->Print ("Couldn't load map: maps/base1.bsp");
		return false;
	}

	gun.LoadModel ("models/weapons/v_bfg/tris.md2", "models/weapons/v_bfg/skin.pcx");
	gun.ChangeAnimation ("idle");

	monster.LoadModel ("models/monsters/soldier/tris.md2", "models/monsters/soldier/skin_ss.pcx");
	monster.ChangeAnimation("stand");

	// Initialize the player entity
	m_player.SetPosition (cVector (-90, 190, -100));
	m_player.LoadSounds("sound/player/");

#ifdef PLAY_MUSIC
	sPlayer.LoadSong ("White Zombie - Quake II Theme.mp3");
	sPlayer.Loop();
#endif // PLAY_MUSIC

	while (m_root.Run())
	{
		time = m_root.GetTimer()->GetElapsedSeconds();

		// Check movement speeds based on if the player is on the ground
		if (!m_player.OnGround())
			m_currentMovementSpeed = m_landSpeed * m_airMoveMult;
		else
			m_currentMovementSpeed = m_landSpeed;

		if (!HandleInput())
			return true;

		// Apply the friction
		if (m_player.OnGround())
			m_player.ApplyFriction( 2000.0f, time );
		else
			m_player.ApplyFriction( 50.0f, time );

		// Apply gravity
		m_player.Force (cVector (0, 0, 1000));

		m_player.Simulate (time);

		m_world.HandleCollisions(&m_player);

		// Attach the camera to the player's viewport
		m_player.SetPosition (m_player.GetPosition() + cVector (0, 0, -30));
		m_camera.Attach( &m_player );
		m_player.SetPosition (m_player.GetPosition() + cVector (0, 0, 30));
		
		// Draw our world
		m_world.DrawWorld(&m_camera, time);

		cVector p = (m_player.GetPosition() - cVector (807, -712, 50));
		//cMatrix m, d;

		glPushMatrix ();
		glLoadMatrixf (m_camera.GetRotation().GetMatrix().m);
		glTranslatef (p.x, p.y, p.z);
		monster.DoDraw (time);
		glPopMatrix();
		
		glLoadIdentity ();
		glClear (GL_DEPTH_BUFFER_BIT);

		glTranslatef(0, 0, -10);
		glRotatef (90, 0, 1, 0);
		glRotatef (-90, 1, 0, 0);
		gun.DoDraw (time);

#ifdef DEBUG_MESSAGES
		char message[1000];

		sprintf(message, "cluster: %d, %f, %f, %f", m_player.OnGround(), m_player.GetPosition().x, m_player.GetPosition().y, m_player.GetPosition().z);

		m_root.GetApplication()->SetTitle (message);
#endif // DEBUG_MESSAGES
		
		// Update the screen
		m_root.Update();
	}
	sPlayer.Stop();

	return true;
}