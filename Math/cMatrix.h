#pragma once

#include <windows.h>
#include "cVector.h"

class cMatrix
{
public:
	cMatrix(void);
	cMatrix(float *values);
	~cMatrix(void);

	void SetValues (float *values) { memcpy (m, values, sizeof(float) * 16); }
	cMatrix operator * (cMatrix &mat);

	void MakeIdentity ();

	void SetPosition (cVector position);
	float m[16];
};
