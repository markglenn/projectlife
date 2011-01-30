#include "cplayerentity.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cPlayerEntity::cPlayerEntity(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_currStep = 0;
}

/////////////////////////////////////////////////////////////////////////////////////
cPlayerEntity::~cPlayerEntity(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
void cPlayerEntity::ForceRelative(cVector& direction)
/////////////////////////////////////////////////////////////////////////////////////
{
	cVector force = m_angle.qvRotate (direction);
	force.z = 0;
	m_force += force;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cPlayerEntity::Simulate(float time)
/////////////////////////////////////////////////////////////////////////////////////
{
	static float timer = 0;
	int step;
	timer += time;

	m_lastPosition = m_position;

	m_velocity = (m_force * time) / m_mass + m_velocity;

	// Check the maximum speed of the velocity (ignoring the z vector)
	float speed = SQR(m_velocity.x) + SQR(m_velocity.y);

	if (timer > 0.35f && m_bOnGround && speed > SQR(50.f))
	{
		
		do 
		{
			step = rand() % 4;
		} while (step == m_currStep);

		m_currStep = step;
		steps[m_currStep].Play();
		timer = 0.f;
	}

	if (speed > SQR(300.f))
	{
		float mult = 1.f / sqrtf(speed);
		m_velocity.x *= 300.f * mult;
		m_velocity.y *= 300.f * mult;
	}

	if (ABS(m_velocity.z) > 400.f)
		m_velocity.z = m_velocity.z / ABS(m_velocity.z) * 400.f;

	m_position = m_velocity * time + m_lastPosition;

	// Reset the force vector
	m_force = 0;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
void cPlayerEntity::Jump (float speed)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_bOnGround)
	{
		m_velocity.z = speed;
		jumpWave.Play();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void cPlayerEntity::LoadSounds (std::string path)
/////////////////////////////////////////////////////////////////////////////////////
{
	jumpWave.LoadSong(path + "jump1.wav");
	steps[0].LoadSong(path + "step1.wav");
	steps[1].LoadSong(path + "step2.wav");
	steps[2].LoadSong(path + "step3.wav");
	steps[3].LoadSong(path + "step4.wav");
}