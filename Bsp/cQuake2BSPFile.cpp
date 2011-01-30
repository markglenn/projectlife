#include <windows.h>
#include <gl/gl.h>

#include "../Rendering System/extgl.h"

#include <math.h>

#include "cQuake2BSPFile.h"

#include "../File/cFileManager.h"
#include "../Texture/cTextureManager.h"
#include "../Core/cLog.h"
#include "../Math/MathDefines.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

#define LIGHTMAP_MULT 4
#define USE_LIGHTMAPS

/////////////////////////////////////////////////////////////////////////////////////
cQuake2BSPFile::cQuake2BSPFile(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_visibility	= NULL;
	m_vertex		= NULL;
	m_face			= NULL;
	m_textures		= NULL;
	m_planes		= NULL;
	m_leafFace		= NULL;

}

/////////////////////////////////////////////////////////////////////////////////////
cQuake2BSPFile::~cQuake2BSPFile(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_visibility)
		delete[] m_visibility;
	if (m_vertex)
		delete[] m_vertex;
	if (m_face)
		delete[] m_face;
	if (m_textures)
		delete[] m_textures;
	if (m_planes)
		delete[] m_planes;
	if (m_leafFace)
		delete[] m_leafFace;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cQuake2BSPFile::LoadMap(std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	cFileManager *fmanager = cFileManager::Singleton();
	m_file = fmanager->OpenFile (filename);
	std::string textureName;

	// Header information
	sHeader header;

	sTextureBSP *texture;

	if (!m_file)
	{
		LOG()->Print ("Couldn't open Q2 Map file %s.", filename.c_str());
		return false;
	}

	m_file->Read (&header, sizeof (sHeader));

	// Check if the file is a valid Q2 BSP File
	if (header.magic != Q2_MAGIC_NUMBER || header.version != Q2BSP_VERSION)
	{
		LOG()->Print ("Invalid Q2 Map file %s.", filename.c_str());
		fmanager->CloseFile(m_file);

		return false;
	}
	
	m_nVerticies = GetNumber (sizeof(sVertex), header.directory[q2VERTICIES]);
	m_verticies = (sVertex *)LoadLump (header.directory[q2VERTICIES]);

	m_nEdges = GetNumber (sizeof(sEdge), header.directory[q2EDGES]);
	m_edges = (sEdge *)LoadLump (header.directory[q2EDGES]);

	m_nFaces = GetNumber (sizeof(sFaceBSP), header.directory[q2FACES]);
	m_faces = (sFaceBSP *)LoadLump (header.directory[q2FACES]);

	m_nFaceEdges = GetNumber (sizeof(int), header.directory[q2FACEEDGES]);
	m_faceEdges = (int*)LoadLump (header.directory[q2FACEEDGES]);

	// Load plane information
	m_nPlanes = GetNumber (sizeof(sPlane), header.directory[q2PLANES]);
	sPlane *planes = (sPlane *)LoadLump (header.directory[q2PLANES]);
	m_planes = new cPlane [m_nPlanes];

	for (int i = 0; i < m_nPlanes; i++)
	{
		m_planes[i].m_normal.x = planes[i].normal[0];
		m_planes[i].m_normal.y = planes[i].normal[1];
		m_planes[i].m_normal.z = planes[i].normal[2];
		m_planes[i].m_d = planes[i].distance;
	}


	m_nTextures = GetNumber (sizeof(sTextureBSP), header.directory[q2TEXTURE]);
	texture = (sTextureBSP*)LoadLump (header.directory[q2TEXTURE]);

	m_textures = new sTexture[m_nTextures];

	// Convert the texture information
	for (int i = 0; i < m_nTextures; i++)
	{
		memcpy (&m_textures[i].uAxis, &texture[i].uAxis, sizeof (sVertex));
		memcpy (&m_textures[i].vAxis, &texture[i].vAxis, sizeof (sVertex));

		m_textures[i].uOffset = texture[i].uOffset;
		m_textures[i].vOffset = texture[i].vOffset;

		// Load in the actual texture
		textureName = "textures/";
		textureName += std::string(texture[i].textureName);
		textureName += std::string (".wal");
		m_textures[i].textureNum = cTextureManager::Singleton()->LoadTexture (textureName);
		m_textures[i].nextTexture = texture[i].nextTexInfo;
		m_textures[i].flags = texture[i].flags;
	}


	// Load nodes
	int numNodes;
	sNode *nodes;
	
	numNodes = GetNumber (sizeof(sNode), header.directory[q2NODES]);
	nodes = (sNode*)LoadLump (header.directory[q2NODES]);

	// Load leaves
	int numLeaves;
	sLeaf *leaves;
	
	numLeaves = GetNumber (sizeof(sLeaf), header.directory[q2LEAVES]);
	leaves = (sLeaf*)LoadLump (header.directory[q2LEAVES]);

	m_nLeafFace = GetNumber (sizeof(short), header.directory[q2LEAFFACES]);
	m_leafFace = (short*)LoadLump (header.directory[q2LEAFFACES]);

	ConvertTree (nodes, numNodes, m_planes, leaves, numLeaves);
    
	m_nVertex = 0;
	
	ConvertVerticies ();
	//BevelTree ();
	LoadVisibility ( header.directory[q2VISIBILITY] );

#ifdef USE_LIGHTMAPS
	LoadLightmaps  ( header.directory[q2LIGHTMAPS] );	
#endif //USE_LIGHTMAPS

	delete[] (unsigned char *)planes;
	delete[] (unsigned char *)nodes;
	delete[] (unsigned char *)leaves;
	delete[] (unsigned char *)texture;
	delete[] (char *)m_faces;
	delete[] (char *)m_verticies;
	delete[] (char *)m_edges;
	delete[] (char *)m_faceEdges;

	fmanager->CloseFile(m_file);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
unsigned char * cQuake2BSPFile::LoadLump (sDirectory &directory)
/////////////////////////////////////////////////////////////////////////////////////
{
	unsigned char *ret = new unsigned char [directory.length];

	m_file->Seek (directory.offset, SEEK_SET);
	m_file->Read (ret, directory.length);

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake2BSPFile::ConvertTree(sNode *nodes, int numNodes, cPlane *planes,
								 sLeaf *leaves, int numLeaves)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Create our tree
	m_tree.reserve(numNodes + numLeaves);
	cNode node;

	for (int i = 0; i < numNodes; i++)
	{
		ZeroMemory (&node, sizeof(cNode));

		// Set the plane
		node.splitter = planes[nodes[i].plane];

		// Set the nodes
		if (nodes[i].children[0] < 0)
            node.backNode	= &m_tree[numNodes - (nodes[i].children[0] + 1)];
		else
			node.backNode	= &m_tree[nodes[i].children[0]];

		if (nodes[i].children[1] < 0)
            node.frontNode	= &m_tree[numNodes - (nodes[i].children[1] + 1)];
		else
			node.frontNode	= &m_tree[nodes[i].children[1]];

		// Set the bounding box
		for (int j = 0; j < 3; j++)
		{
			node.minBoundingBox[j] = nodes[i].bboxMin[j];
			node.maxBoundingBox[j] = nodes[i].bboxMax[j];
		}

		m_tree.push_back (node);
	}

	for (int i = numNodes; i < numNodes + numLeaves; i++)
	{
		ZeroMemory (&node, sizeof(cNode));
		int p = i - numNodes;
		node.isLeaf = true;

		node.cluster = leaves[p].cluster;
		node.leafFace = leaves[p].leafFace;

		// Set the bounding box
		for (int j = 0; j < 3; j++)
		{
			node.minBoundingBox[j] = leaves[p].bboxMin[j];
			node.maxBoundingBox[j] = leaves[p].bboxMax[j];
		}

		node.leafFace = leaves[p].leafFace;
		node.numLeafFace = leaves[p].nLeafFace;

		m_tree.push_back (node);
	}

	m_leaves = numNodes;
	m_nLeaves = numLeaves;

}

/////////////////////////////////////////////////////////////////////////////////////
int cQuake2BSPFile::Draw (cCamera &camera)
/////////////////////////////////////////////////////////////////////////////////////
{
	cTextureManager *tmanager = cTextureManager::Singleton();
	cNode *node = m_tree[0].GetNode (camera.position);

	camera.CalculateFrustum();
	unsigned int flags;
	short face;
	int texturenum;

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable (GL_TEXTURE_2D);
		
#ifdef USE_LIGHTMAPS
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable (GL_TEXTURE_2D);
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
#endif //USE_LIGHTMAPS

	glDisable (GL_BLEND);
	for (int n = m_leaves; n < m_leaves + m_nLeaves; n++)
	{
		if (m_tree[n].isLeaf &&
			node->cluster != -1 &&
			m_visibility[node->cluster * m_nClusters + m_tree[n].cluster] &&
			camera.RightParallelepipedInFrustum(m_tree[n].minBoundingBox, m_tree[n].maxBoundingBox))
		{
			for (int leafface = m_tree[n].leafFace; leafface < m_tree[n].numLeafFace + m_tree[n].leafFace; leafface++)
			{	
				face = m_leafFace[leafface];

				texturenum = m_face[face].texture;
				flags = m_textures[texturenum].flags;
				if (!(flags & SURF_NODRAW) &&
					!(flags & SURF_SKY) &&
					!(flags & SURF_TRANS33) &&
					!(flags & SURF_TRANS66))
				{
					glActiveTextureARB(GL_TEXTURE0_ARB);
					tmanager->BindTexture (m_textures[m_face[face].texture].textureNum);
#ifdef USE_LIGHTMAPS
					glActiveTextureARB (GL_TEXTURE1_ARB);
					tmanager->BindTexture(m_face[face].lightmap);
#endif //USE_LIGHTMAPS
					glBegin (GL_TRIANGLE_FAN);
					for (int vertex = m_face[face].vertex; vertex < m_face[face].vertex + m_face[face].nVertex; vertex++)
					{
						glMultiTexCoord2fvARB (GL_TEXTURE0_ARB, m_vertex[vertex].texcoord[0]);
#ifdef USE_LIGHTMAPS
						glMultiTexCoord2fvARB (GL_TEXTURE1_ARB, m_vertex[vertex].texcoord[1]);
#endif //USE_LIGHTMAPS
						glVertex3fv (m_vertex[vertex].position);
					}
					glEnd();
				}
			}
		}
	}

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
	glEnable (GL_BLEND);
	for (int face = 0; face < m_nFace; face++)
	{
		texturenum = m_face[face].texture;
		flags = m_textures[texturenum].flags;
		if (!(flags & SURF_NODRAW) &&
			!(flags & SURF_SKY) &&
			((flags & SURF_TRANS33) ||
			(flags & SURF_TRANS66)))
		{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			tmanager->BindTexture (m_textures[m_face[face].texture].textureNum);
#ifdef USE_LIGHTMAPS
			glActiveTextureARB (GL_TEXTURE1_ARB);
			tmanager->BindTexture(m_face[face].lightmap);
#endif //USE_LIGHTMAPS
			glBegin (GL_TRIANGLE_FAN);
			for (int vertex = m_face[face].vertex; vertex < m_face[face].vertex + m_face[face].nVertex; vertex++)
			{
				glMultiTexCoord2fvARB (GL_TEXTURE0_ARB, m_vertex[vertex].texcoord[0]);
				glMultiTexCoord2fvARB (GL_TEXTURE1_ARB, m_vertex[vertex].texcoord[1]);
				glVertex3fv (m_vertex[vertex].position);
			}
			glEnd();
		}
	}

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable (GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);

	glDisable (GL_BLEND);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	return node->cluster;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake2BSPFile::ConvertVerticies()
/////////////////////////////////////////////////////////////////////////////////////
{
	int v = 0;
	int faceedge;

	cTextureManager *tmanager = cTextureManager::Singleton();
	sTexture *tex;
	cTexture *currTexture;
	int vertex;

	// Calculate the number of verticies
	for (int i = 0; i < m_nFaces; i++)
		m_nVertex += m_faces[i].numEdges;

	m_vertex = new cVertex [m_nVertex];

	m_nFace = m_nFaces;
	m_face = new sFace [m_nFace];

	for (int face = 0; face < m_nFaces; face++)
	{
		m_face[face].texture = m_faces[face].textureInfo;
		m_face[face].nVertex = m_faces[face].numEdges;
		m_face[face].normal = m_planes[m_faces[face].plane].GetNormal();
		m_face[face].vertex = v;
		
		tex = &m_textures[m_faces[face].textureInfo];
		currTexture = tmanager->GetTexture (tex->textureNum);

		for (int edge = m_faces[face].firstEdge;
				edge < m_faces[face].numEdges + m_faces[face].firstEdge;
				edge++)
		{
			faceedge = m_faceEdges[edge];

			if (faceedge < 0)
				vertex = m_edges[-faceedge].vertex[1];
			else
				vertex = m_edges[ faceedge].vertex[0];

			memcpy (m_vertex[v].position, m_verticies[vertex].v,12);
			
			// Precompute the texture coordinates
			m_vertex[v].texcoord[0][0] = ComputeU(vertex, tex, currTexture);
			m_vertex[v].texcoord[0][1] = ComputeV(vertex, tex, currTexture);

			v++;

		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake2BSPFile::BevelTree()
/////////////////////////////////////////////////////////////////////////////////////
{
	/* DOES NOT WORK */
	cPlane plane;
	bool addedBevel;
	cVector point;
	int face1 = 0, face2 = 0;
	bool found = false;

	for (int edge = 0; edge < m_nEdges; edge++)
	{
		found = false;
		face1 = 0;
		
		// Find first occurence
		while (!found && face1 < m_nFaces)
		{
			for (int fe = m_faces[face1].firstEdge; fe < (m_faces[face1].firstEdge + m_faces[face1].numEdges); fe++)
			{
				if (m_faceEdges[fe] == edge)
					found = true;
			}

			if (!found) face1++;
		}

		found = false;
		face2 = face1 + 1;
		
		// Find second occurence
		while (!found && face2 < m_nFaces)
		{
			for (int fe = m_faces[face2].firstEdge; fe < m_faces[face2].firstEdge + m_faces[face2].numEdges; fe++)
			{
				if (ABS(m_faceEdges[fe]) == edge)
					found = true;
			}

			if (!found) face2++;
		}

		if (found)
		{
			if ((m_face[face1].normal * m_face[face2].normal) < 0)
			{
			
				point = cVector (m_verticies[m_edges[edge].vertex[0]].v[0],
								 m_verticies[m_edges[edge].vertex[0]].v[1],
								 m_verticies[m_edges[edge].vertex[0]].v[2]);

				plane.m_normal = ((m_face[face1].normal + m_face[face2].normal) / 2.0f) | 1.0f;
				plane.m_d = point * plane.m_normal;
				AddEmptyCell(plane, point);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake2BSPFile::LoadVisibility( sDirectory &visDirectory )
/////////////////////////////////////////////////////////////////////////////////////
{
	long offset;
	sPvs *pvsTable;

	int c;
	unsigned char data;

	// Seek to the visibility set and read in the number of clusters
	m_file->Seek (visDirectory.offset, SEEK_SET);
	m_file->Read (&m_nClusters, sizeof(int));

	// Create the visibility data
	m_visibility = new bool[SQR(m_nClusters)];
	ZeroMemory (m_visibility, sizeof(bool) * SQR(m_nClusters));

	// Initialize the visibility table
	pvsTable = new sPvs[m_nClusters];
	m_file->Read (pvsTable, sizeof(sPvs) * m_nClusters);

	for (int i = 0; i < m_nClusters; i++)
	{
		// Move to the visibility offset
		offset = pvsTable[i].pvs + visDirectory.offset;
		m_file->Seek (offset, SEEK_SET);

		c = 0;
		while (c < m_nClusters)
		{
			m_file->Read (&data, 1);

			if (data == 0)
			{
				m_file->Read(&data, 1);
				c += 8 * data;
			}
			else
			{
				for (unsigned char bit = 1; bit != 0; bit *= 2, c++)
				{
					if (data & bit)
						m_visibility[m_nClusters * i + c] = true;
				}
			}
		}
	}

	delete [] pvsTable;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake2BSPFile::LoadLightmaps (sDirectory &lmDirectory)
/////////////////////////////////////////////////////////////////////////////////////
{
	float maxu, minu, maxv, minv;
	int width, height;
	unsigned int textureOffset;
	cVector location;
	int tWidth, tHeight;
	
	// 8 x 8 lightmap grid
	unsigned char lightmap[LIGHTMAP_WIDTH * 8 * LIGHTMAP_HEIGHT * 8 * 3];
	unsigned char cmap[LIGHTMAP_WIDTH * LIGHTMAP_HEIGHT * 3];
	int lnum = 0;
	int face;
	cTextureManager *tm = cTextureManager::Singleton();

	ZeroMemory (lightmap, LIGHTMAP_WIDTH * 8 * LIGHTMAP_HEIGHT * 8 * 3);

	glColor3f (1, 1, 1);
	for (face = 0; face < m_nFace; face++)
	{
		maxu = maxv = -99999.f;
		minu = minv = 99999.f;
		
		textureOffset = lmDirectory.offset + m_faces[face].lightmapOffset;

		tWidth = tm->GetTexture(m_textures[m_face[face].texture].textureNum)->GetWidth();
		tHeight = tm->GetTexture(m_textures[m_face[face].texture].textureNum)->GetHeight();

		for (int vertex = m_face[face].vertex; vertex < m_face[face].vertex + 
				m_face[face].nVertex; vertex++)
		{
			maxu = MAX(m_vertex[vertex].texcoord[0][0] * float(tWidth), maxu);
			maxv = MAX(m_vertex[vertex].texcoord[0][1] * float(tHeight), maxv);

			minu = MIN(m_vertex[vertex].texcoord[0][0] * float(tWidth), minu);
			minv = MIN(m_vertex[vertex].texcoord[0][1] * float(tHeight), minv);
			
		}

		width = ceil (maxu / 16.f) - floor (minu / 16.f) + 1;
		height = ceil (maxv / 16.f) - floor (minv / 16.f) + 1;

		if (width > 16)
			width = 16;
		if (height > 16)
			height = 16;

		m_file->Seek (textureOffset, SEEK_SET);
		m_file->Read (cmap, width * height * 3);

		for (int i = 0; i < width * height * 3; i++)
		{
			unsigned int c = (unsigned int)cmap[i] * LIGHTMAP_MULT;
			if (c > 255) c = 255;
			cmap[i] = (unsigned char)c;
		}
		location = AddToLightmapGrid (lightmap, width, height, cmap, lnum);
		lnum = (lnum + 1 ) % 64;

		m_face[face].lightmap = cTextureManager::Singleton()->GetFreeTexture();

		maxu /= tWidth;
		minu /= tWidth;

		maxv /= tHeight;
		minv /= tHeight;

		for (int vertex = m_face[face].vertex; vertex < m_face[face].vertex + 
				m_face[face].nVertex; vertex++)
		{
			int mapx = location.x + (width - 2) * (m_vertex[vertex].texcoord[0][0] - minu) / (maxu - minu) + 1;
			int mapy = location.y / (LIGHTMAP_HEIGHT * 8) + (height - 2) * (m_vertex[vertex].texcoord[0][1] - minv) / (maxv - minv) + 1;

			m_vertex[vertex].texcoord[1][0] = float(mapx) / float(LIGHTMAP_WIDTH * 8);
			m_vertex[vertex].texcoord[1][1] = float(mapy) / float(LIGHTMAP_WIDTH * 8);
		}

		// We have our 64 lightmaps, load them in now
		if (lnum == 0)
		{
			tm->LoadTexture(lightmap, 8 * LIGHTMAP_WIDTH, 8 * LIGHTMAP_HEIGHT, 24);
			ZeroMemory (lightmap, 8 * LIGHTMAP_WIDTH * 8 * LIGHTMAP_HEIGHT * 3);
		}
	}

	if (lnum != 0)
			tm->LoadTexture(lightmap, 8 * LIGHTMAP_WIDTH, 8 * LIGHTMAP_HEIGHT, 24);
}

/////////////////////////////////////////////////////////////////////////////////////
cVector cQuake2BSPFile::AddToLightmapGrid( unsigned char *lmap, unsigned int width, unsigned int height,
											unsigned char *cmap, int lnum )
/////////////////////////////////////////////////////////////////////////////////////
{
	cVector location;

	// Calculate the location into the lightmap
	location.x = (lnum % 8) * LIGHTMAP_WIDTH;
	location.y = (lnum / 8) * LIGHTMAP_HEIGHT * 8 * LIGHTMAP_HEIGHT;
	location.z = 0;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			int gloc = (location.y + location.x + x + y * LIGHTMAP_HEIGHT * 8) * 3;
			int loc = (x + y * width) * 3;

			lmap[gloc + 0] = cmap[loc + 0];
			lmap[gloc + 1] = cmap[loc + 1];
			lmap[gloc + 2] = cmap[loc + 2];
		}
	return location;
}