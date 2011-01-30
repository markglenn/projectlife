#include "ckeyframemodel.h"

cKeyFrameModel::cKeyFrameModel(void)
{
	m_t = 0;
	m_currFrame = 0;
	m_currVertex = 0;
}

cKeyFrameModel::~cKeyFrameModel(void)
{
	if (m_currVertex)
		delete[] m_currVertex;
}
