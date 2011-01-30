#pragma once

#include <math.h>

#include "MathDefines.h"
#include "cVector.h"
#include "cMatrix.h"

class cQuaternion
{
public:
	cQuaternion(void);
	cQuaternion(float x, float y, float z, float w);
	cQuaternion(float x, float y, float z);

	~cQuaternion(void);

	void Identity ();
	void Normalize ();

	__forceinline double Norm () const { return (sqrt( SQR(x) + SQR(y) + SQR(z) + SQR(w))); }
	void GetDirectionalVectors (cVector &direction, cVector &left, cVector &up);
	void EulerToQuat (float x, float y, float z);

	cMatrix GetMatrix ();

	void Slerp (const cQuaternion q1, const cQuaternion q2, const float slerp);
	__forceinline float Dot ( const cQuaternion& q1 ) const;

	// Operators
	cQuaternion operator* (const cQuaternion &q) const;
	cQuaternion operator~ () const
		{ return cQuaternion (-x, -y, -z, w); }

	cVector qvRotate (const cVector &v) const;
	float x, y, z, w;
};

inline cQuaternion operator * (cQuaternion q, cVector v)
{
	return cQuaternion (    q.w*v.x + q.y*v.z - q.z*v.y,
						    q.w*v.y + q.z*v.x - q.x*v.z,
						    q.w*v.z + q.x*v.y - q.y*v.x,
						 - (q.x*v.x + q.y*v.y + q.z*v.z));
}

inline cQuaternion operator * (cVector v, cQuaternion q)
{
	return cQuaternion (	q.w*v.x + q.z*v.y - q.y*v.z,
						    q.w*v.y + q.x*v.z - q.z*v.x,
						    q.w*v.z + q.y*v.x - q.x*v.y,
						 - (q.x*v.x + q.y*v.y + q.z*v.z));
}
