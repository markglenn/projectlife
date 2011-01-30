#pragma once

#include "../Core/Defines.h"
#include "../Math/cPlane.h"
#include "../Math/cQuaternion.h"

class cEntity
{
public:
	cEntity(void);
	~cEntity(void);

	cVector&		GetPosition  ()		{ return m_position; }
	cVector&		GetLastPosition ()	{ return m_lastPosition; }
	cQuaternion&	GetAngle ()			{ return m_angle; }
	cVector&		GetVelocity ()		{ return m_velocity; }
	
	cVector GetDirection ();

	void	SetPosition	( cVector& pos )		{ m_position = pos;  }
	void	SetAngle	( cQuaternion& angle )	{ m_angle = angle; }
	void	SetVelocity ( cVector& vel )		{ m_velocity = vel; }

	virtual void Animate (float deltaTime) {}
	virtual void ApplyFriction ( float coef, float time );
	virtual void Draw () {}

	virtual void ForceRelative ( cVector& direction );
	void Force ( cVector& direction );
	void Rotate (float x, float y, float z);

	virtual cVector HandlePlaneCollision (cPlane planeCollision, cVector pointCollision, cVector start, cVector end);

	virtual bool Simulate (float time);
	void SetOnGround (bool bOnGround) { m_bOnGround = bOnGround; }
	bool OnGround () { return m_bOnGround; }

	cVector* GetForce() { return &m_force; }

protected:
	cVector		m_position;
	cVector		m_lastPosition;
	cQuaternion m_angle;

	// Simulation information
	cVector		m_force;
	cVector		m_velocity;
	bool		m_bOnGround;

	float		m_mass;
};
