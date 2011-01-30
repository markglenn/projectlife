#pragma once

#include <string>
#include "cbsp.h"
#include "../File/cFileManager.h"
#include "../Texture/cTexture.h"
#include "../Input System/cCamera.h"
#include "../Geometry/cVertex.h"

#define Q2_MAGIC_NUMBER ('I' + ('B'<<8) + ('S'<<16) + ('P'<<24))
#define Q2BSP_VERSION 38

// From qfiles.h
#define	SURF_LIGHT		0x1		// value will hold the light strength

#define	SURF_SLICK		0x2		// effects game physics

#define	SURF_SKY		0x4		// don't draw, but add to skybox
#define	SURF_WARP		0x8		// turbulent water warp
#define	SURF_TRANS33	0x10
#define	SURF_TRANS66	0x20
#define	SURF_FLOWING	0x40	// scroll towards angle
#define	SURF_NODRAW		0x80	// don't bother referencing the texture

#define LIGHTMAP_WIDTH  18
#define LIGHTMAP_HEIGHT 18

class cQuake2BSPFile :
	public cBSP
{
public:
	cQuake2BSPFile(void);
	~cQuake2BSPFile(void);

	bool LoadMap (std::string filename);
	int Draw (cCamera &camera);

private:

	enum eq2Lumps
	{
		q2ENTITIES,		q2PLANES,		q2VERTICIES,
		q2VISIBILITY,	q2NODES,		q2TEXTURE,
		q2FACES,		q2LIGHTMAPS,	q2LEAVES,
		q2LEAFFACES,	q2LEAFBRUSHES,	q2EDGES,
		q2FACEEDGES,	q2MODELS,		q2BRUSHES,
		q2BRUSHSIDES,	q2POP,			q2AREAS,
		q2PORTALS,		q2NUM_LUMPS
	};

	struct sDirectory
	{
		unsigned int	offset;			// Offset in file
		unsigned int	length;			// Length of lump
	};
	
	struct sHeader
	{
		int			magic;					// 'IBSP' 
		int			version;				// BSP version (Always 46)
		sDirectory	directory[q2NUM_LUMPS];	// Directory
	};

	struct sVertex
	{
		float v[3];
	};

	struct sEdge
	{
		unsigned short vertex[2];
	};

	struct sFaceBSP
	{
		unsigned short	plane;
		unsigned short	planeSide;

		unsigned int	firstEdge;
		unsigned short	numEdges;

		unsigned short	textureInfo;

		unsigned char	lightmapStyles[4];
		unsigned int	lightmapOffset;
	};

	struct sFace 
	{
		int			texture;
		int			lightmap;
		cVector		normal;
		int			vertex;
		int			nVertex;
	};

	struct sTextureBSP
	{
		sVertex uAxis;
		float uOffset;

		sVertex vAxis;
		float vOffset;

		unsigned int flags;
		unsigned int values;

		char textureName[32];
		unsigned int nextTexInfo;
	};

	struct sTexture
	{
		sVertex uAxis;
		float uOffset;

		sVertex vAxis;
		float vOffset;

		unsigned int flags;
		int textureNum;
		int nextTexture;
	};

	struct sPlane
	{
		float normal[3];
		float distance;
		unsigned int type;
	};

	struct sNode
	{
		unsigned int	plane;
		int				children[2];

		short			bboxMin[3];
		short			bboxMax[3];

		unsigned short	firstFace;
		unsigned short	nFaces;
	};

	struct sLeaf
	{
		unsigned int	brushOr;
		
		short	cluster;
		unsigned short	area;

		short			bboxMin[3];
		short			bboxMax[3];

		unsigned short	leafFace;
		unsigned short	nLeafFace;

		unsigned short	leafBrush;
		unsigned short	nLeafBrush;
	};

	struct sPvs
	{
		unsigned int pvs;
		unsigned int phs;
	};


protected:
	unsigned char * LoadLump (sDirectory &directory);
	int				GetNumber (int size, sDirectory &directory)
		{ return directory.length / size; }

	inline float ComputeU (int vertex, sTexture *tex, cTexture *currTexture) 
	{
			return ((m_verticies[vertex].v[0] * tex->uAxis.v[0] + 
					 m_verticies[vertex].v[1] * tex->uAxis.v[1] +
					 m_verticies[vertex].v[2] * tex->uAxis.v[2] +
					 tex->uOffset) / float(currTexture->GetWidth()));
	};

	inline float ComputeV (int vertex, sTexture *tex, cTexture *currTexture)
	{
		return ((m_verticies[vertex].v[0] * tex->vAxis.v[0] + 
				 m_verticies[vertex].v[1] * tex->vAxis.v[1] +
				 m_verticies[vertex].v[2] * tex->vAxis.v[2] +
				 tex->vOffset) / float(currTexture->GetHeight()));

	};

	void ConvertTree (sNode *nodes, int numNodes, cPlane *planes,
						sLeaf *leaves, int numLeaves);

	void LoadVisibility ( sDirectory &visDirectory );
	void LoadLightmaps ( sDirectory &lmDirectory ) ;

	cVector AddToLightmapGrid ( unsigned char *lmap, unsigned int width, unsigned int height, unsigned char *cmap, int lnum );

	void ConvertVerticies ();
	void BevelTree ();

	// Temporary member variables
	sVertex *m_verticies;
	int		 m_nVerticies;

	sEdge	*m_edges;
	int		 m_nEdges;

	sFaceBSP	*m_faces;
	int		 m_nFaces;

	int		*m_faceEdges;
	int		 m_nFaceEdges;

	short	*m_leafFace;
	int		 m_nLeafFace;

	sTexture *m_textures;
	int		  m_nTextures;

	cVertex *m_vertex;
	int		 m_nVertex;

	sFace	*m_face;
	int		 m_nFace;

	cPlane	*m_planes;
	int		 m_nPlanes;

	bool	*m_visibility;
	int		 m_nClusters;

	cIFile *m_file;

};
