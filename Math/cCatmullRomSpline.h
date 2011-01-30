#pragma once

#include <vector>
#include "cVector.h"

class cCatmullRomSpline
{
public:
	cCatmullRomSpline(void);
	~cCatmullRomSpline(void);

	cVector CalculatePoint ( float t );

	void ClearPointList () { m_pointList.clear(); }
	void AddPoint (cVector point) { m_pointList.push_back (point); }

	void PrecalculateLength ();

protected:
	std::vector <cVector>	m_pointList;
	std::vector <float>		m_lengthList;
};
