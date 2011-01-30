#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>

#include "cCamera.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cCamera::cCamera(void)
: position (0)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cCamera::~cCamera(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
void cCamera::Animate(DWORD timeDelta)
/////////////////////////////////////////////////////////////////////////////////////
{
	glLoadIdentity();
	cMatrix m = rotation.GetMatrix();
	cMatrix pos;
	pos.SetPosition(position);

	m = pos * m;

	glLoadMatrixf (m.m);
}

/////////////////////////////////////////////////////////////////////////////////////
void cCamera::LookAt(cEntity * entity)
/////////////////////////////////////////////////////////////////////////////////////
{
	//lookAt = entity->GetPosition() - position;
}

/////////////////////////////////////////////////////////////////////////////////////
void cCamera::Attach (cEntity *entity)
/////////////////////////////////////////////////////////////////////////////////////
{
	position = entity->GetPosition();
	rotation = entity->GetAngle();
}

/////////////////////////////////////////////////////////////////////////////////////
void cCamera::NormalizePlane(float frustum[6][4], int side)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Here we calculate the magnitude of the normal to the plane (point A B C)
	// Remember that (A, B, C) is that same thing as the normal's (X, Y, Z).
	// To calculate magnitude you use the equation:  magnitude = sqrt( x^2 + y^2 + z^2)
	float magnitude = (float)sqrt( frustum[side][A] * frustum[side][A] + 
								   frustum[side][B] * frustum[side][B] + 
								   frustum[side][C] * frustum[side][C] );

	// Then we divide the plane's values by it's magnitude.
	// This makes it easier to work with.
	frustum[side][A] /= magnitude;
	frustum[side][B] /= magnitude;
	frustum[side][C] /= magnitude;
	frustum[side][D] /= magnitude; 
}


/////////////////////////////////////////////////////////////////////////////////////
void cCamera::CalculateFrustum(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Special thanks to DigiBen for this function

	float   proj[16];								// This will hold our projection matrix
	float   modl[16];								// This will hold our modelview matrix
	float   clip[16];								// This will hold the clipping planes

	// glGetFloatv() is used to extract information about our OpenGL world.
	// Below, we pass in GL_PROJECTION_MATRIX to abstract our projection matrix.
	// It then stores the matrix into an array of [16].
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	// By passing in GL_MODELVIEW_MATRIX, we can abstract our model view matrix.
	// This also stores it in an array of [16].
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	// Now that we have our modelview and projection matrix, if we combine these 2 matrices,
	// it will give us our clipping planes.  To combine 2 matrices, we multiply them.

	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];
	
	// Now we actually want to get the sides of the frustum.  To do this we take
	// the clipping planes we received above and extract the sides from them.

	// This will extract the RIGHT side of the frustum
	m_frustum[RIGHT][A] = clip[ 3] - clip[ 0];
	m_frustum[RIGHT][B] = clip[ 7] - clip[ 4];
	m_frustum[RIGHT][C] = clip[11] - clip[ 8];
	m_frustum[RIGHT][D] = clip[15] - clip[12];

	// Now that we have a normal (A,B,C) and a distance (D) to the plane,
	// we want to normalize that normal and distance.

	// Normalize the RIGHT side
	NormalizePlane(m_frustum, RIGHT);

	// This will extract the LEFT side of the frustum
	m_frustum[LEFT][A] = clip[ 3] + clip[ 0];
	m_frustum[LEFT][B] = clip[ 7] + clip[ 4];
	m_frustum[LEFT][C] = clip[11] + clip[ 8];
	m_frustum[LEFT][D] = clip[15] + clip[12];

	// Normalize the LEFT side
	NormalizePlane(m_frustum, LEFT);

	// This will extract the BOTTOM side of the frustum
	m_frustum[BOTTOM][A] = clip[ 3] + clip[ 1];
	m_frustum[BOTTOM][B] = clip[ 7] + clip[ 5];
	m_frustum[BOTTOM][C] = clip[11] + clip[ 9];
	m_frustum[BOTTOM][D] = clip[15] + clip[13];

	// Normalize the BOTTOM side
	NormalizePlane(m_frustum, BOTTOM);

	// This will extract the TOP side of the frustum
	m_frustum[TOP][A] = clip[ 3] - clip[ 1];
	m_frustum[TOP][B] = clip[ 7] - clip[ 5];
	m_frustum[TOP][C] = clip[11] - clip[ 9];
	m_frustum[TOP][D] = clip[15] - clip[13];

	// Normalize the TOP side
	NormalizePlane(m_frustum, TOP);

	// This will extract the BACK side of the frustum
	m_frustum[BACK][A] = clip[ 3] - clip[ 2];
	m_frustum[BACK][B] = clip[ 7] - clip[ 6];
	m_frustum[BACK][C] = clip[11] - clip[10];
	m_frustum[BACK][D] = clip[15] - clip[14];

	// Normalize the BACK side
	NormalizePlane(m_frustum, BACK);

	// This will extract the FRONT side of the frustum
	m_frustum[FRONT][A] = clip[ 3] + clip[ 2];
	m_frustum[FRONT][B] = clip[ 7] + clip[ 6];
	m_frustum[FRONT][C] = clip[11] + clip[10];
	m_frustum[FRONT][D] = clip[15] + clip[14];

	// Normalize the FRONT side
	NormalizePlane(m_frustum, FRONT);

}

/////////////////////////////////////////////////////////////////////////////////////
bool cCamera::RightParallelepipedInFrustum(float fMin[3], float fMax[3])
/////////////////////////////////////////////////////////////////////////////////////
{
	////////////////////////////////////////////////////////////////////////
	// Return true when the right parallelpiped intersects with the view
	// frustum. The parameter fSize has to be the width of the cube divided 
	// by two
	////////////////////////////////////////////////////////////////////////

	unsigned int iCurPlane;
	int x = 0, y = 1, z = 2;

	for (iCurPlane = 0; iCurPlane<6; iCurPlane++)
	{
		if (m_frustum[iCurPlane][0] * fMin[x] + m_frustum[iCurPlane][1] *
			fMax[y] + m_frustum[iCurPlane][2] * fMin[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMin[x] + m_frustum[iCurPlane][1] *
			fMax[y] + m_frustum[iCurPlane][2] * fMax[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMax[x] + m_frustum[iCurPlane][1] *
			fMax[y] + m_frustum[iCurPlane][2] * fMax[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMax[x] + m_frustum[iCurPlane][1] *
			fMax[y] + m_frustum[iCurPlane][2] * fMin[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMax[x] + m_frustum[iCurPlane][1] *
			fMin[y] + m_frustum[iCurPlane][2] * fMin[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMax[x] + m_frustum[iCurPlane][1] *
			fMin[y] + m_frustum[iCurPlane][2] * fMax[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMin[x] + m_frustum[iCurPlane][1] *
			fMin[y] + m_frustum[iCurPlane][2] * fMax[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;
		if (m_frustum[iCurPlane][0] * fMin[x] + m_frustum[iCurPlane][1] *
			fMin[y] + m_frustum[iCurPlane][2] * fMin[z] + 
			m_frustum[iCurPlane][3] > 0)
			continue;

		return false;
	}

	return true;
}



