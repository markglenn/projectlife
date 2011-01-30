#pragma once

#include <string>
#include <vector>

#include "../File/cFileManager.h"
#include "../Geometry/cVertex.h"
#include "../Geometry/cBezier.h"

#include "cBSP.h"

#define MAGIC_NUMBER ('I' + ('B'<<8) + ('S'<<16) + ('P'<<24))
#define Q3BSP_VERSION 46

class cQuake3BSPFile : public cBSP
{
public:
	cQuake3BSPFile(void);
	~cQuake3BSPFile(void);

	bool LoadMap (std::string filename);

	int Draw (cVector *position);
	
private:

	enum eq3Lumps
	{
		q3ENTITIES,		q3TEXTURES,		q3PLANES, 
		q3NODES,		q3LEAVES,		q3LEAFFACES,
		q3LEAFBRUSHES,	q3MODELS,		q3BRUSHES,
		q3BRUSHSIDES,	q3VERTECIES,	q3MESHVERTS,
		q3EFFECTS,		q3FACES,		q3LIGHTMAPS,
		q3LIGHTVOLS,	q3VISDATA,		q3NUM_LUMPS
	};

	struct sDirectory
	{
		int	offset;			// Offset in file
		int	length;			// Length of lump
	};
	
	struct sHeader
	{
		int			magic;					// 'IBSP' 
		int			version;				// BSP version (Always 46)
		sDirectory	directory[q3NUM_LUMPS];	// Directory
	};

	struct sFace
	{
		int		texture;
		int		effect;
		int		type;
		int		vertex;
		int		numVertex;
		int		meshVert;
		int		numMeshVert;
		int		lmIndex;
		int		lmStart[2];
		int		lmSize[2];
		float	lmOrigin[3];
		float	lmVecs[2][3];
		float	normal[3];
		int		size[2];
	};

	struct sModel
	{
		float	mins[3];
		float	max[3];
		int		face;
		int		numFace;
		int		brush;
		int		numBrushes;
	};

	struct sMeshVert
	{
		int offset;
	};

	struct sNode
	{
		int plane;
		int children[2];
		int mins[3];
		int maxs[3];
	};

	struct sLeaf
	{
		int cluster;
		int area;
		int mins[3];
		int maxs[3];
		int leafFace;
		int numLeafFace;
		int leafBrush;
		int numLeafBrush;
	};

	cVertex *m_vertex;
	int		 m_numVertex;

	sFace	*m_face;
	int		 m_numFace;

	bool	*m_drawn;

	sModel	*m_model;
	int		 m_numModel;

	sMeshVert	*m_meshVert;
	int			 m_numMeshVert;

	int		*m_leafFace;
	int		 m_numLeafFace;

	std::vector <cBezier *> m_curves;
protected:

	unsigned char * LoadLump (sDirectory directory);
	int				GetNumber (int size, sDirectory directory)
		{ return directory.length / size; }

	void ConvertTree (sNode *nodes, int numNodes, cPlane *planes,
						sLeaf *leaves, int numLeaves);

	cIFile *m_file;

	void DrawFace (int face);
	cVector lastPos;
	
};
