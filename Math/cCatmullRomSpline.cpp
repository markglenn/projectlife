#include "ccatmullromspline.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

#define CATMULL_STEPS 100.f

/////////////////////////////////////////////////////////////////////////////////////
cCatmullRomSpline::cCatmullRomSpline(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cCatmullRomSpline::~cCatmullRomSpline(void)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cVector cCatmullRomSpline::CalculatePoint ( float t )
/////////////////////////////////////////////////////////////////////////////////////
{
	cVector out;
	float t1, t2, t3;
	int pos = int(t);
	t = t - float(pos);

	t2 = t * t;
	t3 = t * t * t;
	t1 = (1-t) * (1-t);

	out.x = (-t*t1*m_pointList[pos].x + (2-5*t2+3*t3)*m_pointList[pos + 1].x + t*(1+4*t-3*t2)*m_pointList[pos + 2].x - t2*(1-t)*m_pointList[pos + 3].x)/2;
	out.y = (-t*t1*m_pointList[pos].y + (2-5*t2+3*t3)*m_pointList[pos + 1].y + t*(1+4*t-3*t2)*m_pointList[pos + 2].y - t2*(1-t)*m_pointList[pos + 3].y)/2;
	out.z = (-t*t1*m_pointList[pos].z + (2-5*t2+3*t3)*m_pointList[pos + 1].z + t*(1+4*t-3*t2)*m_pointList[pos + 2].z - t2*(1-t)*m_pointList[pos + 3].z)/2;

	return out;
}

/////////////////////////////////////////////////////////////////////////////////////
void cCatmullRomSpline::PrecalculateLength()
/////////////////////////////////////////////////////////////////////////////////////
{
	float length;
	m_lengthList.clear();

	for (float i = 0.f; i < (float)m_pointList.size() - 3; i += 1.f)
	{
		length = 0.f;
		for (float j = 0.f; j < CATMULL_STEPS; j += 1.f)
		{
			cVector first = CalculatePoint	(i + j / CATMULL_STEPS);
			cVector second = CalculatePoint (i + (j + 1) / CATMULL_STEPS);

			length += !(first - second);
		}
		m_lengthList.push_back(length);
	}
}