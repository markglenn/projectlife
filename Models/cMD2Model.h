#pragma once

#include <windows.h>
#include "../Math/cVector.h"
#include "cKeyFrameModel.h"

class cMD2Model : public cKeyFrameModel
{
public:
	cMD2Model(void);
	~cMD2Model(void);

	//void ChangeState ( int state ) { m_state = state; }
	bool LoadModel(char * modelFile, char * skinFile);

	virtual void DoDraw(float deltaTime);

protected:
	struct sModelHeader
	{
		int		ident;
		int		version;
		int		skinWidth;
		int		skinHeight;
		int		framesize;
		int		numSkins;
		int		numPoints;
		int		numTexPoints;
		int		numTris;
		int		numGLCommands;
		int		numFrames;
		int		offsetSkins;
		int		offsetTexPoints;
		int		offsetTris;
		int		offsetFrames;
		int		offsetGLcmds;
		int		offsetEnd;
	};

	struct sFrame
	{
		float scale[3];
		float translate[3];
		char name[16];
	};

	struct sFramePoint 
	{
		unsigned char v[3];
		unsigned char normalIndex;
	};
	struct sMeshIndex
	{
		unsigned short meshIndex[3];
		unsigned short stIndex[3];
	};
	struct sTexCoord
	{
		short s, t;
	};

	void Animate(int startFrame, int endFrame, float percent);
	void AddFrame (std::string framename, cGeometryData *mesh);
	std::string GetFrameName (std::string framename);
};
