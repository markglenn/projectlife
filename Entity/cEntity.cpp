#include "cEntity.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cEntity::cEntity(void)
	: m_velocity(0), m_force(0), m_mass(1.0f), m_lastPosition(0)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cEntity::~cEntity(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cVector cEntity::GetDirection ()
/////////////////////////////////////////////////////////////////////////////////////
{
	cVector direction, left, up;

	m_angle.GetDirectionalVectors(direction, left, up);
	return direction;

}

/////////////////////////////////////////////////////////////////////////////////////
void cEntity::ForceRelative ( cVector &direction )
/////////////////////////////////////////////////////////////////////////////////////
{
	// Rotate the direction vector and force in that direction
	m_force += m_angle.qvRotate (direction);
}

/////////////////////////////////////////////////////////////////////////////////////
void cEntity::Force ( cVector &direction )
/////////////////////////////////////////////////////////////////////////////////////
{
	// Force in that direction
	m_force += direction;
}

/////////////////////////////////////////////////////////////////////////////////////
void cEntity::Rotate (float x, float y, float z)
/////////////////////////////////////////////////////////////////////////////////////
{
	cQuaternion q;
	q.EulerToQuat(x, y, z);

	m_angle = q * m_angle;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cEntity::Simulate(float time)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_lastPosition = m_position;

	m_velocity = (m_force * time) / m_mass + m_velocity;

	// Check the maximum speed of the velocity (ignoring the z vector)
	float speed = SQR(m_velocity.x) + SQR(m_velocity.y);

	if (speed > SQR(200))
	{
		float multx = m_velocity.x / sqrtf(SQR(m_velocity.x) + SQR(m_velocity.y));
		float multy = m_velocity.y / sqrtf(SQR(m_velocity.x) + SQR(m_velocity.y));

		m_velocity.x = multx * 200.f;//m_velocity | 500.0f;
		m_velocity.y = multy * 200.f;
	}

	m_position = m_velocity * time + m_lastPosition;

	// Reset the force vector
	m_force = 0;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
cVector cEntity::HandlePlaneCollision (cPlane planeCollision, cVector pointCollision, 
									   cVector start, cVector end)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_position = (end + cVector (planeCollision.m_normal * 
					(-1 * (planeCollision.m_normal * end) - planeCollision.m_d)));

	return m_position;
}

/////////////////////////////////////////////////////////////////////////////////////
void cEntity::ApplyFriction ( float coef, float time )
/////////////////////////////////////////////////////////////////////////////////////
{
	cVector friction = m_velocity;
	friction.z = 0.f;

	float velLength = friction.GetLength();

	if (velLength > 1.f)
	{
		friction = friction.Normal() * (-coef * time);

		if (friction.GetLength() > velLength)
			friction = friction | velLength;
        		
		m_velocity += friction;
	}
}