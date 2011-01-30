#pragma once

#define MAX_TEXTURES 8

struct cGeometryData 
{
	struct _vertex 
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};

	struct _texcoord
	{
		union
		{
			struct { float s, t; };
			float v[2];
		};
	};

	// Attributes
	unsigned short numVerticies;
	unsigned short numVertexIndecies;
	
	// Strides
	unsigned short vertexStride;
	unsigned short normalStride;
	unsigned short textureStride;
	unsigned short colorStride;

	unsigned short numTextures;

	// Types
	bool hasColor;
	bool hasNormal;
	bool hasTexture;
	bool hasVertexIndex;
	bool hasTextureIndex;

	void			* pVertex;
	void			* pNormal;
	void			* pTexCoord [MAX_TEXTURES];
	unsigned short	* pVertexIndex;
	unsigned short	* pTextureIndex;


};