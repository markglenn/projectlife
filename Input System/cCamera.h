#pragma once

#include <windows.h>
#include "../Math/cVector.h"
#include "../Entity/cEntity.h"

class cCamera
{
public:
	enum FrustumSide
	{
		RIGHT	= 0,		// The RIGHT side of the frustum
		LEFT	= 1,		// The LEFT	 side of the frustum
		BOTTOM	= 2,		// The BOTTOM side of the frustum
		TOP		= 3,		// The TOP side of the frustum
		BACK	= 4,		// The BACK	side of the frustum
		FRONT	= 5			// The FRONT side of the frustum
	}; 

	enum PlaneData
	{
		A = 0,				// The X value of the plane's normal
		B = 1,				// The Y value of the plane's normal
		C = 2,				// The Z value of the plane's normal
		D = 3				// The distance the plane is from the origin
	};

	// Positioning vectors
	/*cVector position, lastPosition;
	cVector lookAt, lastLookAt;
	cVector up, lastUp;*/

	cVector position;
	cQuaternion rotation;

	cCamera(void);
	~cCamera(void);

	void Animate(DWORD timeDelta);

	void LookAt(cEntity * entity);
	void Attach (cEntity * entity);

	bool RightParallelepipedInFrustum(float fMin[3], float fMax[3]);

	void CalculateFrustum(void);

	cQuaternion GetRotation () { return rotation; }
protected:

	// Frustum planes for each side of the view frustum
	float m_frustum[6][4];
	void NormalizePlane(float frustum[6][4], int side);
};
