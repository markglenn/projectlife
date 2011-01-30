#include <windows.h>
#include <gl/gl.h>

#include "cQuake3BSPFile.h"
#include "../File/cFileManager.h"
#include "../Core/cLog.h"
#include "../Geometry/cBezier.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cQuake3BSPFile::cQuake3BSPFile(void)
	: m_numVertex(0),	m_vertex(0),
	  m_numFace(0),		m_face(0),
	  m_numModel(0),	m_model(0),
	  m_numMeshVert(0),	m_meshVert(0),
	  m_drawn(0)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
cQuake3BSPFile::~cQuake3BSPFile(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	if (m_vertex)
		delete[] (void*)m_vertex;

	if (m_face)
		delete[] (void*)m_face;

	if (m_model)
		delete[] (void*)m_model;

	if (m_meshVert)
		delete[] (void*)m_meshVert;

	if (m_drawn)
		delete[] m_drawn;
}

/////////////////////////////////////////////////////////////////////////////////////
bool cQuake3BSPFile::LoadMap(std::string filename)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_file = cFileManager::Singleton()->OpenFile(filename);
	sHeader header;
	
	cPlane *planes;
	sNode *nodes;
	int numNodes;

	sLeaf *leaves;
	int numLeaves;

	// Check if the file was loaded correctly
	if (!m_file)
	{
		LOG()->Print ("Couldn't open Q3 Map file %s.", filename.c_str());	
		return false;
	}

	// Read in the header
	m_file->Read (&header, sizeof(sHeader));

	// Check the type of file
	if (header.magic != MAGIC_NUMBER || header.version != Q3BSP_VERSION)
	{
		LOG()->Print ("Invalid Q3 Map file %s.", filename.c_str());
		cFileManager::Singleton()->CloseFile (m_file);

		return false;
	}

	// Load in the vertex lump
	m_numVertex = GetNumber(sizeof(cVertex), header.directory[q3VERTECIES]);
	m_vertex = (cVertex*)(LoadLump (header.directory[q3VERTECIES]));

	// Load in the face lump
	m_numFace = GetNumber (sizeof(sFace), header.directory[q3FACES]);
	m_face = (sFace*)(LoadLump (header.directory[q3FACES]));
	
	m_drawn = new bool[m_numFace];

	// Load in the model lump
	m_numModel = GetNumber (sizeof(sModel), header.directory[q3MODELS]);
	m_model = (sModel*)(LoadLump (header.directory[q3MODELS]));

	// Load mesh vert lump
	m_numMeshVert = GetNumber (sizeof(sMeshVert), header.directory[q3MESHVERTS]);
	m_meshVert = (sMeshVert*)(LoadLump (header.directory[q3MESHVERTS]));

	// Load plane lump
	planes = (cPlane *)(LoadLump (header.directory[q3PLANES]));

	// Load node lump
	numNodes = GetNumber (sizeof(sNode), header.directory[q3NODES]);
	nodes = (sNode *)(LoadLump(header.directory[q3NODES]));

	// Load leaf lump
	numLeaves = GetNumber (sizeof(sLeaf), header.directory[q3LEAVES]);
	leaves = (sLeaf *)(LoadLump(header.directory[q3LEAVES]));

	// Load leafface
	m_numLeafFace = GetNumber (sizeof(int), header.directory[q3LEAFFACES]);
	m_leafFace = (int *)(LoadLump(header.directory[q3LEAFFACES]));
    
	// Convert the tree to our format
	ConvertTree (nodes, numNodes, planes, leaves, numLeaves);

	cFileManager::Singleton()->CloseFile (m_file);

	delete[] (void*)nodes;
	delete[] (void*)planes;
	delete[] (void*)leaves;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake3BSPFile::ConvertTree(sNode *nodes, int numNodes, cPlane *planes,
								 sLeaf *leaves, int numLeaves)
/////////////////////////////////////////////////////////////////////////////////////
{
	// Create our tree
	m_tree = new cNode [numNodes + numLeaves];

	ZeroMemory (m_tree, sizeof(cNode) * (numNodes + numLeaves));
	m_treeSize = numNodes + numLeaves;

	for (int i = 0; i < numNodes; i++)
	{
		// Set the plane
		m_tree[i].splitter = planes[nodes[i].plane];

		// Set the nodes
		if (nodes[i].children[0] < 0)
            m_tree[i].backNode	= &m_tree[numNodes - (nodes[i].children[0] + 1)];
		else
			m_tree[i].backNode	= &m_tree[nodes[i].children[0]];

		if (nodes[i].children[1] < 0)
            m_tree[i].frontNode	= &m_tree[numNodes - (nodes[i].children[1] + 1)];
		else
			m_tree[i].frontNode	= &m_tree[nodes[i].children[1]];

		// Set the bounding box
		for (int j = 0; j < 3; j++)
		{
			m_tree[i].minBoundingBox[j] = nodes[i].mins[j];
			m_tree[i].maxBoundingBox[j] = nodes[i].maxs[j];
		}
	}

	for (int i = numNodes; i < numNodes + numLeaves; i++)
	{
		int p = i - numNodes;
		m_tree[i].isLeaf = true;

		m_tree[i].cluster = leaves[p].cluster;
		m_tree[i].leafFace = leaves[p].leafFace;

		// Set the bounding box
		for (int j = 0; j < 3; j++)
		{
			m_tree[i].minBoundingBox[j] = leaves[p].mins[j];
			m_tree[i].maxBoundingBox[j] = leaves[p].maxs[j];
		}

		m_tree[i].leafFace = leaves[p].leafFace;
		m_tree[i].numLeafFace = leaves[p].numLeafFace;
	}

}

/////////////////////////////////////////////////////////////////////////////////////
unsigned char * cQuake3BSPFile::LoadLump (sDirectory directory)
/////////////////////////////////////////////////////////////////////////////////////
{
	unsigned char *ret = new unsigned char [directory.length];

	m_file->Seek (directory.offset, SEEK_SET);
	m_file->Read (ret, directory.length);

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
int cQuake3BSPFile::Draw (cVector *position)
/////////////////////////////////////////////////////////////////////////////////////
{
	cBezier bezier;
	cVertex points[9];
	static cVector lastPoint = cVector (0, 500, -100);
	int vertex;
	int offset;

	cNode *node;

	ZeroMemory (m_drawn, sizeof(bool) * m_numFace);

	node = m_tree[0].GetNode (*position);
	/*if (node->cluster < 0)
	{
		*position = lastPoint;
		node = m_tree[0].GetNode (*position);
	}

	lastPoint = *position;*/

	for ( int i = 0; i < m_numFace; i++ )
	{
		int face = i;
		if (!m_drawn[face])
		{
			m_drawn[face] = true;
			if (m_face[face].type == 1)
			{
				glBegin (GL_POLYGON);
				for (int j = 0; j < m_face[face].numVertex; j++)
				{
					glColor4ubv (m_vertex[m_face[face].vertex + j].color);
					glVertex3fv (m_vertex[m_face[face].vertex + j].position);
				}
				glEnd ();
			}

			else if (m_face[face].type == 2)
			{
				for (int x = 0; x < (m_face[face].size[0] - 1) / 2; x++)
				{
					for (int y = 0; y < (m_face[face].size[1] - 1) / 2; y++)
					{
						for (int z = 0; z < 9; z++)
						{
							int pos = (y * m_face[face].size[0] * 2 + x * 2) + (z / 3 * m_face[face].size[0]) + z % 3;
							points[z] = m_vertex[pos + m_face[face].vertex];
						}

						bezier.SetControlPoints (points);
						bezier.Draw();
					}
				}
			}
			else if (m_face[face].type == 3)
			{
				glBegin (GL_TRIANGLES);
				for (int j = m_face[face].meshVert; j < m_face[face].meshVert + m_face[face].numMeshVert; j++)
				{				
					vertex = m_meshVert[j].offset + m_face[face].vertex;
					//glTexCoord2fv (m_vertex[vertex].texcoord[0]);
					glColor4ubv (m_vertex[vertex].color);
					glVertex3fv (m_vertex[vertex].position);
				}
				glEnd();

			}
		}
	}
	return node->cluster;

}

/////////////////////////////////////////////////////////////////////////////////////
void cQuake3BSPFile::DrawFace (int face)
/////////////////////////////////////////////////////////////////////////////////////
{
	cBezier bezier;
	cVertex points[9];
	int vertex;
	int offset;

	if (!m_drawn[face])
	{
		m_drawn[face] = true;
		if (m_face[face].type == 1)
		{
			glBegin (GL_POLYGON);
			for (int j = 0; j < m_face[face].numVertex; j++)
			{
				glColor4ubv (m_vertex[m_face[face].vertex + j].color);
				glVertex3fv (m_vertex[m_face[face].vertex + j].position);
			}
			glEnd ();
		}

		else if (m_face[face].type == 2)
		{
			for (int x = 0; x < (m_face[face].size[0] - 1) / 2; x++)
			{
				for (int y = 0; y < (m_face[face].size[1] - 1) / 2; y++)
				{
					for (int z = 0; z < 9; z++)
					{
						int pos = (y * m_face[face].size[0] * 2 + x * 2) + (z / 3 * m_face[face].size[0]) + z % 3;
						points[z] = m_vertex[pos + m_face[face].vertex];
					}

					bezier.SetControlPoints (points);
					bezier.Draw();
				}
			}
		}
		else if (m_face[face].type == 3)
		{
			glBegin (GL_TRIANGLES);
			for (int j = m_face[face].meshVert; j < m_face[face].meshVert + m_face[face].numMeshVert; j++)
			{				
				vertex = m_meshVert[j].offset + m_face[face].vertex;
				//glTexCoord2fv (m_vertex[vertex].texcoord[0]);
				glColor4ubv (m_vertex[vertex].color);
				glVertex3fv (m_vertex[vertex].position);
			}
			glEnd();

		}
	}
}