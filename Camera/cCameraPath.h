#pragma once

#include <vector>
#include "../Math/cCatmullRomSpline.h"
#include "../Math/cQuaternion.h"

class cCameraPath
{
public:
	cCameraPath(void);
	~cCameraPath(void);

private:
	cCatmullRomSpline m_spline;
	std::vector <cQuaternion> m_rotation;	
};
