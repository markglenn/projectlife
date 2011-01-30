#ifndef CVECTOR_H
#define CVECTOR_H

#include "MathDefines.h"

class cVector
{
public:
	// Constructors
	cVector ();
	cVector ( float X, float Y, float Z )	{ x = X; y = Y; z = Z; }
	cVector ( float X )						{ x = y = z = X; }
	cVector ( const cVector &v )			{ x = v.x; y = v.y; z = v.z; }

	float GetLength ( ) { return !(*this); }
	void SetVector (const cVector &v)
		{ x = v.x; y = v.y; z = v.z; }
	
	// Accessors
	float & operator[] (int inx) { return m_v[inx]; }
	const float & operator[] (int inx) const { return m_v[inx]; }
	inline float *GetVertex ( ) { return m_v; }

	// Reflect this vector off surface with normal vector
    const cVector inline Reflection(const cVector& normal) const
    {    
         const cVector vec(*this | 1);     // normalize this vector
         return (vec - normal * 2.0 * (vec * normal)) * !*this;
    }

	// Assignment operators
	cVector& operator += ( const cVector& v);
	cVector& operator -= ( const cVector& v);
	cVector& operator *= ( const cVector& v);
	cVector& operator *= ( float v );
	cVector& operator /= ( float v );

	// Binary operators
    friend cVector operator + (const cVector& A, const cVector& B);
    friend cVector operator - (const cVector& A, const cVector& B);
    friend cVector operator - (const cVector& A);
    friend cVector operator * (const cVector& A, const float& v);
    friend cVector operator / (const cVector& A, const float& v);

	// Dot product
    friend float   operator * (const cVector& A, const cVector& B);
	// Cross product
	friend cVector operator % (const cVector& A, const cVector& B);
	// Vector Length
	friend float   operator ! (const cVector& A);
	friend cVector operator | (const cVector& A, const float& v);

	__forceinline cVector Normal () { return *this / !*this; }
	
	// Vector coordinates
	union
	{
		struct { float x, y, z; };
		float m_v[3];
	};
};

// Vector addition
inline cVector operator+ (const cVector& A, const cVector& B)
{
    return cVector(A.x + B.x, A.y + B.y, A.z + B.z);
}

// Vector subtraction
inline cVector operator- (const cVector& A, const cVector& B)
{
    return cVector(A.x - B.x, A.y - B.y, A.z - B.z);
}

// Vector negation
inline cVector operator - (const cVector& A)
{
	return cVector (-A.x, -A.y, -A.z);
}

// Vector scaling
inline cVector operator* (const cVector& A, const float& v)
{
    return cVector(A.x * v, A.y * v, A.z * v);
}

// Vector division
inline cVector operator/ (const cVector& A, const float& v)
{
    return cVector(A.x / v, A.y / v, A.z / v);
}

// Vector dot product
inline float operator* (const cVector& A, const cVector& B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

// Vector cross product
inline cVector operator% (const cVector& A, const cVector& B)
{
    return cVector(	A.y * B.z - A.z * B.y, 
					A.z * B.x - A.x * B.z, 
					A.x * B.y - A.y * B.x );
}

// Unit length vector
inline float operator ! (const cVector& A)
{
	return ( sqrtf( SQR(A.x) + SQR(A.y) + SQR(A.z) ) );
}

// Specified length vector
inline cVector operator | (const cVector& A, const float& v)
{
	return A * (v / !A);
}

// Equality test
inline bool operator == (const cVector& A, const cVector& B)
{
	return ((A.x == B.x) && (A.y == B.y) && (A.z == B.z));
}

// Not equal test
inline bool operator != (const cVector& A, const cVector& B)
{
	return !((A.x == B.x) && (A.y == B.y) && (A.z == B.z));
}
#endif