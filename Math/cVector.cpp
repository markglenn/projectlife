// cVector.cpp: implementation of the cVector class.
//
//////////////////////////////////////////////////////////////////////

#include "../Math/cVector.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cVector::cVector()
{

}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////

cVector& cVector::operator+= ( const cVector& v )
{
    x += v.x;  y += v.y;  z += v.z;
    return *this;
}

cVector& cVector::operator -= ( const cVector& v)
{
    x -= v.x;  y -= v.y;  z -= v.z;
    return *this;
}

cVector& cVector::operator *= ( const cVector& v)
{
    x *= v.x;  y *= v.y;  z *= v.z;
    return *this;
}

cVector& cVector::operator *= ( float v )
{
	x *= v; y *= v; z *= v;
	return *this;
}

cVector& cVector::operator /= ( float v )
{
	x /= v; y /= v; z /= v;
	return *this;
}
