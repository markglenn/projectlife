// cPlane.h: interface for the cPlane class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CPLANE_H
#define CPLANE_H

#include "../Math/MathDefines.h"
#include "../Math/cVector.h"

enum ePointLoc
{
	PT_FRONT,
	PT_BACK,
	PT_COPLANAR
};

class cPlane  
{

public:
	cPlane();
	cPlane ( const cVector &vec, float D );
	cPlane ( float X, float Y, float Z, float D );
	cPlane ( const cVector &p1, const cVector &p2, const cVector &p3 );

	~cPlane();

	// Point test
	ePointLoc	TestPoint ( const cVector& point );
	cVector		GetIntersection ( const cVector& point1, const cVector& point2 );

	void		Assign (float x, float y, float z, float d)
	{
		m_normal.x = x; m_normal.y = y; m_normal.z = z;
		m_d = d;
	}

	cVector		GetNormal ( ) { return m_normal; }

	bool RayUnder (const cVector &v0, const cVector &v1, cVector *w0, cVector *w1);
	bool RayOver (const cVector &v0, const cVector &v1, cVector *w0, cVector *w1);


	cVector m_normal;
	float	m_d;
};

#endif