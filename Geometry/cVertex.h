#pragma once

class cVertex
{
public:
	float			position[3];		// Vertex position
	float			texcoord[2][2];		// Texture coordinates (0 = surface, 1=lightmap)
	float			normal[3];			// Vertex normal
	unsigned char	color[4];			// Vertex color (RGBA)
};