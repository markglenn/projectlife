#pragma once
#include <string>
#include <map>
#include <vector>

#include "cModel.h"
#include "../Geometry/cGeometryData.h"

class cKeyFrameModel : public cModel
{
public:
	cKeyFrameModel(void);
	~cKeyFrameModel(void);

	virtual void Animate (float t) { };
	virtual void Draw () {};
	virtual void ChangeAnimation (unsigned int animation) { };
	virtual void ChangeAnimation (std::string framename)
		{ m_currKeyFrame = &m_animations[framename]; }

protected:
	typedef std::vector < cGeometryData *> TKeyFrames;
	typedef std::map <std::string, TKeyFrames> TAnimations;

	TAnimations m_animations;

	TKeyFrames *m_currKeyFrame;
	cGeometryData m_geometry;
	cGeometryData::_vertex *m_currVertex;

	// Key frame models
	unsigned int m_currFrame;

	/// Position in between frames
	float m_t;
};
