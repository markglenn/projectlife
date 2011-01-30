#include "cquaternion.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cQuaternion::cQuaternion(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	Identity ();
}

/////////////////////////////////////////////////////////////////////////////////////
cQuaternion::cQuaternion( float x, float y, float z, float w )
/////////////////////////////////////////////////////////////////////////////////////
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;

	//Normalize ();
}

/////////////////////////////////////////////////////////////////////////////////////
cQuaternion::cQuaternion(float x, float y, float z)
/////////////////////////////////////////////////////////////////////////////////////
{
	EulerToQuat(x, y, z);
}

/////////////////////////////////////////////////////////////////////////////////////
cQuaternion::~cQuaternion(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuaternion::Identity()
/////////////////////////////////////////////////////////////////////////////////////
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuaternion::Normalize()
/////////////////////////////////////////////////////////////////////////////////////
{
	double norm = Norm ();

	x /= norm;
	y /= norm;
	z /= norm;
	w /= norm;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuaternion::EulerToQuat ( float x, float y, float z )
/////////////////////////////////////////////////////////////////////////////////////
{
	double ex, ey, ez;
	double cr, cp, cy, sr, sp, sy, cpcy, spsy;

	ex = DEG2RAD (x) / 2.0;
	ey = DEG2RAD (y) / 2.0;
	ez = DEG2RAD (z) / 2.0;

	cr = cos (ex);	cp = cos (ey);	cy = cos (ez);
	sr = sin (ex);	sp = sin (ey);	sy = sin (ez);

	cpcy = cp * cy;
	spsy = sp * sy;

	this->w = cr * cpcy + sr * spsy;
	
	this->x = float((sr * cpcy) - (cr * spsy));
	this->y = float((cr * sp * cy) + (sr * cp * sy));
	this->z = float((cr * cp * sy) - (sr * sp * cy));

}

/////////////////////////////////////////////////////////////////////////////////////
cQuaternion cQuaternion::operator * (const cQuaternion &q) const
/////////////////////////////////////////////////////////////////////////////////////
{
	return cQuaternion (w*q.x + x*q.w + y*q.z - z*q.y,
						w*q.y + y*q.w + z*q.x - x*q.z,
						w*q.z + z*q.w + x*q.y - y*q.x,
						w*q.w - x*q.x - y*q.y - z*q.z);
	
	/*return cQuaternion (w*q.w - x*q.x - y*q.y - z*q.z,
						w*q.x + x*q.w + y*q.z - z*q.y,
						w*q.y + y*q.w + z*q.x - x*q.z,
						w*q.z - z*q.w - x*q.y - y*q.x);*/
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuaternion::GetDirectionalVectors(cVector &direction, cVector &left, cVector &up)
/////////////////////////////////////////////////////////////////////////////////////
{
	double x2, y2, z2, w2, xy, xz, yz, wx, wy, wz;

	x2 = SQR(x);	y2 = SQR(y);	z2 = SQR(z);	w2 = SQR(w);

	xy = x * y;
	xz = x * z;
	yz = y * z;
	wx = w * x;
	wy = w * y;
	wz = w * z;

	left		= -cVector (1 - 2 * (y2 + z2),	2 * (xy + wz),		2 * (xz - wy));
	up			=  cVector (2 * (xy - wz),		1 - 2 * (x2 + z2),	2 * (yz + wx));
	direction	= -cVector (2 * (xz + wy),		2 * (yz - wx),		1 - 2 * (x2 + y2));
}

/////////////////////////////////////////////////////////////////////////////////////
cMatrix cQuaternion::GetMatrix()
/////////////////////////////////////////////////////////////////////////////////////
{
	double x2, y2, z2, w2, xy, xz, yz, wx, wy, wz;
	cMatrix matrix;
	x2 = SQR(x);	y2 = SQR(y);	z2 = SQR(z);	w2 = SQR(w);

	xy = x * y;
	xz = x * z;
	yz = y * z;
	wx = w * x;
	wy = w * y;
	wz = w * z;

	matrix.m[0]		= -float (1 - 2 * (y2 + z2));
	matrix.m[4]		= -float (	 2 * (xy + wz));
    matrix.m[8]		= -float (	 2 * (xz - wy));

	matrix.m[1]		=  float (	 2 * (xy - wz));
	matrix.m[5]		=  float (1 - 2 * (x2 + z2));
	matrix.m[9]		=  float (	 2 * (yz + wx));

	matrix.m[2]		= -float (	 2 * (xz + wy));
	matrix.m[6]		= -float (	 2 * (yz - wx));
	matrix.m[10]	= -float (1 - 2 * (x2 + y2));

	matrix.m[15]		= 1.0f;

	return matrix;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuaternion::Slerp (const cQuaternion q1, const cQuaternion q2, const float slerp)
/////////////////////////////////////////////////////////////////////////////////////
{
	double cosom, omega, sinom, scale1, scale2;
	float tx, ty, tz, tw;

	cosom = q1.Dot(q2);

	// If the quaternions aren't exactly opposite
	if (EPSILON < 1.0f + cosom)
	{
		// If the quaternions are close
		if (EPSILON > 1.0f - cosom)
		{
			// Linear interpolation
			scale1 = 1.0f - slerp;
			scale2 = slerp;
		}
		// If the quaternions are not very close
		else
		{
			// Use slerp
			omega = acos (cosom);
			sinom = sin (omega);

			scale1 = sin((1.0f - slerp) * omega) / sinom;
			scale2 = sin(slerp * omega) / sinom;
		}

		tx = q2.x;
		ty = q2.y;
		tz = q2.z;
		tw = q2.w;
	}
	// If quaternions are exactly opposite
	else
	{
		// Calculate a perpendicular quaternion and slerp in that direction
		scale1 = sin(PI * (0.5 - slerp));
		scale2 = sin(PI * slerp);

		tx = -q2.y;
		ty = q2.x;
		tz = -q2.w;
		tw = q2.z;
	}

	x = float(scale1 * q1.x + scale2 * tx);
	y = float(scale1 * q1.y + scale2 * ty);
	z = float(scale1 * q1.z + scale2 * tz);
	w = float(scale1 * q1.w + scale2 * tw);

	Normalize ();
}

/////////////////////////////////////////////////////////////////////////////////////
float cQuaternion::Dot (const cQuaternion& q1) const
/////////////////////////////////////////////////////////////////////////////////////
{
	return w * q1.w + x * q1.x + y * q1.y + z * q1.z;
}

/////////////////////////////////////////////////////////////////////////////////////
cVector cQuaternion::qvRotate (const cVector &v) const
/////////////////////////////////////////////////////////////////////////////////////
{
	cQuaternion t;

	t = (*this) * v;
	t = t * (~(*this));
	return cVector (t.x, t.y, t.z);
}