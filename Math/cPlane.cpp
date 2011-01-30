// cPlane.cpp: implementation of the cPlane class.
//
//////////////////////////////////////////////////////////////////////

#include "../Math/cPlane.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cPlane::cPlane()
{
	m_normal = cVector (0, 0, 0);
	m_d = 0;
}

cPlane::~cPlane()
{

}

cPlane::cPlane ( const cVector &vec, float D )
{
	m_normal = vec | 1.0;
	m_d = D;
}

cPlane::cPlane ( float X, float Y, float Z, float D )
{
	m_normal = cVector (X, Y, Z) | 1.0;
	m_d = D;
}

cPlane::cPlane ( const cVector &p1, const cVector &p2, const cVector &p3 )
{

	cVector normalA = ((p3 - p1) | 1.0);
	cVector normalB = ((p3 - p2) | 1.0);

	m_normal = normalA % normalB | 1.0;
	m_d = - p1 * m_normal;
}

ePointLoc cPlane::TestPoint ( const cVector& point )
{
	float dp = (point * m_normal) + m_d;

	if (dp > EPSILON)
	{
		return PT_FRONT;
	}
	if (dp < -EPSILON)
	{
		return PT_BACK;
	}
	
	return PT_COPLANAR;
}

cVector	cPlane::GetIntersection ( const cVector& point1, const cVector& point2 )
{
	float aDot = (point1 * m_normal);
	float bDot = (point2 * m_normal);

	float scale = ( -m_d - aDot ) / ( bDot - aDot );

	return (point1 + ((point2 - point1) * scale));
	
}

bool cPlane::RayOver (const cVector &v0, const cVector &v1, cVector *w0, cVector *w1)
{
	ePointLoc p0, p1;

	p0 = TestPoint (v0);
	p1 = TestPoint (v1);

	// Both points are in front
	if ((p0 == PT_FRONT && p1 == PT_FRONT) || 
		(p0 == PT_FRONT && p1 == PT_COPLANAR) ||
		(p0 == PT_COPLANAR && p1 == PT_FRONT) ||
		(p0 == PT_COPLANAR && p1 == PT_COPLANAR))
	{
		w0->SetVector(v0);
		w1->SetVector(v1);
		return true;
	}

	// Both points are behind
	if (p0 != PT_FRONT && p1 != PT_FRONT)
		return false;

	// p0 in front, p1 behind
	if (p0 == PT_FRONT)
	{
		w1->SetVector(GetIntersection(v0, v1));
		w1->SetVector (v1);
		return true;
	}

	// p0 behind, p1 in front
	w0->SetVector(GetIntersection(v0, v1));
	w1->SetVector(v1);
	return true;

}

bool cPlane::RayUnder (const cVector &v0, const cVector &v1, cVector *w0, cVector *w1)
{
	ePointLoc p0, p1;

	p0 = TestPoint (v0);
	p1 = TestPoint (v1);

	// Both points are in front
	if ((p0 == PT_BACK && p1 == PT_BACK) || 
		(p0 == PT_BACK && p1 == PT_COPLANAR) ||
		(p0 == PT_COPLANAR && p1 == PT_BACK) ||
		(p0 == PT_COPLANAR && p1 == PT_COPLANAR))
	{
		w0->SetVector(v0);
		w1->SetVector(v1);
		return true;
	}

	// Both points are in front
	if (p0 != PT_BACK && p1 != PT_BACK)
		return false;


	// p0 in front, p1 behind
	if (p0 == PT_BACK)
	{
		w0->SetVector(v0);
		w1->SetVector(GetIntersection(v0, v1));
		return true;
	}

	// p0 behind, p1 in front
	w0->SetVector(GetIntersection(v0, v1));
	w1->SetVector(v1);
	return true;

}