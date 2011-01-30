#pragma once

#include "../Geometry/cVertex.h"

class cBezier
{
public:
	cBezier();
	~cBezier(void);

	void SetControlPoints (cVertex *ctrlPoints);

	void	Draw();
private:
	
	cVertex GenDegree (float u, cVertex* point);

	cVertex *m_ctrlPoints;
	cVertex *m_last;

	int		 m_tess;

};
