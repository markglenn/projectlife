#include <windows.h>
#include <gl/gl.h>

#include "cBezier.h"
#include "../Math/MathDefines.h"
#include "../Math/cVector.h"

/////////////////////////////////////////////////////////////////////////////////////
cBezier::cBezier()
	: m_ctrlPoints(NULL), m_last(NULL)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_tess = 5;
	m_last = new cVertex [m_tess + 1];
	m_ctrlPoints = new cVertex[9];
}

/////////////////////////////////////////////////////////////////////////////////////
cBezier::~cBezier(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_ctrlPoints)
		delete[] m_ctrlPoints;
	if (m_last)
		delete[] m_last;
}

/////////////////////////////////////////////////////////////////////////////////////
void cBezier::SetControlPoints (cVertex *ctrlPoints)
/////////////////////////////////////////////////////////////////////////////////////
{
	cVertex temp[3];

	memcpy (m_ctrlPoints, ctrlPoints, 9 * sizeof(cVertex));

	memcpy (&temp[0], &m_ctrlPoints[0], sizeof(cVertex));
	memcpy (&temp[1], &m_ctrlPoints[3], sizeof(cVertex));
	memcpy (&temp[2], &m_ctrlPoints[6], sizeof(cVertex));

	for (int v = 0; v <= m_tess; v++)
	{
		float px = ((float)v)/((float)m_tess);			// percent along y axis
		memcpy(&m_last[v], &GenDegree(px, temp), sizeof(cVertex));
	}
}

/////////////////////////////////////////////////////////////////////////////////////
cVertex cBezier::GenDegree (float u, cVertex *point)
/////////////////////////////////////////////////////////////////////////////////////
{
	float weight1, weight2, weight3;
	cVertex ret;

	weight1 = SQR(1 - u);
	weight2 = 2 * (1 - u) * (u);
	weight3 = SQR(u);

	ret.position[0] = 
		(point[0].position[0] * weight1 + point[1].position[0] * weight2 + point[2].position[0] * weight3);
	ret.position[1] = 
		(point[0].position[1] * weight1 + point[1].position[1] * weight2 + point[2].position[1] * weight3);
	ret.position[2] = 
		(point[0].position[2] * weight1 + point[1].position[2] * weight2 + point[2].position[2] * weight3);

	ret.color[0] = unsigned char(point[0].color[0] * weight1 + point[1].color[0] * weight2 + point[2].color[0] * weight3);
	ret.color[1] = unsigned char(point[0].color[1] * weight1 + point[1].color[1] * weight2 + point[2].color[1] * weight3);
	ret.color[2] = unsigned char(point[0].color[2] * weight1 + point[1].color[2] * weight2 + point[2].color[2] * weight3);
	ret.color[3] = unsigned char(point[0].color[3] * weight1 + point[1].color[3] * weight2 + point[2].color[3] * weight3);

	ret.texcoord[0][0] = (point[0].texcoord[0][0] * weight1 + point[1].texcoord[0][0] * weight2 + 
							point[2].texcoord[0][0] * weight3);
	ret.texcoord[0][1] = (point[0].texcoord[0][1] * weight1 + point[1].texcoord[0][1] * weight2 + 
							point[2].texcoord[0][1] * weight3);
	ret.texcoord[1][0] = (point[0].texcoord[1][0] * weight1 + point[1].texcoord[1][0] * weight2 + 
							point[2].texcoord[1][0] * weight3);
	ret.texcoord[1][1] = (point[0].texcoord[1][1] * weight1 + point[1].texcoord[1][1] * weight2 + 
							point[2].texcoord[1][1] * weight3);

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
void cBezier::Draw ()
/////////////////////////////////////////////////////////////////////////////////////
{
	cVector vPoint = cVector(0.0f, 0.0f, 0.0f);			// Initialize a temp vertex to hold point
	cVertex temp[3];
	
	// Tessellate the mesh
	for (int u = 1; u <= m_tess; u++)
	{
		float percentu = (float)u / (float)m_tess;
		
		memcpy (&temp[0], &GenDegree (percentu, &m_ctrlPoints[0]), sizeof(cVertex));
		memcpy (&temp[1], &GenDegree (percentu, &m_ctrlPoints[3]), sizeof(cVertex));
		memcpy (&temp[2], &GenDegree (percentu, &m_ctrlPoints[6]), sizeof(cVertex));

		glBegin (GL_TRIANGLE_STRIP);

		for (int v = 0; v <= m_tess; v++)
		{
			float percentv = (float)v / (float)m_tess;

			glColor4f (m_last[v].color[0] / 255.f, m_last[v].color[1] / 255.f, m_last[v].color[2] / 255.f,
						m_last[v].color[3] / 255.f);
			glVertex3fv(m_last[v].position);

			memcpy(&m_last[v], &GenDegree(percentv, temp), sizeof(cVertex));

/*			//glTexCoord2fv (m_last[v].texcoord[0]);
			texmanager->glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_last[v].texcoord[0][0],
				m_last[v].texcoord[0][1]);

			texmanager->glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_last[v].texcoord[0][0],
				m_last[v].texcoord[1][1]);*/

			glTexCoord2fv (m_last[v].texcoord[0]);
			glColor4f (m_last[v].color[0] / 255.f, m_last[v].color[1] / 255.f, m_last[v].color[2] / 255.f,
						m_last[v].color[3] / 255.f);
			glVertex3fv(m_last[v].position);
		}

		glEnd();
	}

}