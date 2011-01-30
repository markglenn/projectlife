#include <stdio.h>
#include <ctype.h>
#include "cMd2model.h"
#include "../Core/cRoot.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/////////////////////////////////////////////////////////////////////////////////////
cMD2Model::cMD2Model(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	ZeroMemory (&m_geometry, sizeof (cGeometryData));
}

/////////////////////////////////////////////////////////////////////////////////////
cMD2Model::~cMD2Model(void)
/////////////////////////////////////////////////////////////////////////////////////
{
	TKeyFrames::iterator iter;
	TAnimations::iterator aniIter;
	for (aniIter = m_animations.begin(); aniIter != m_animations.end(); aniIter++)
	{
		for (iter = aniIter->second.begin(); iter < aniIter->second.end(); iter++)
		{
			delete[] (*iter)->pVertex;
			delete (*iter);
		}
	}

	if (m_geometry.numVertexIndecies != 0)
	{
		delete[] m_geometry.pVertexIndex;
		delete[] m_geometry.pTextureIndex;
		delete[] m_geometry.pTexCoord[0];
	}
}

/////////////////////////////////////////////////////////////////////////////////////
bool cMD2Model::LoadModel(char * modelFile, char * skinFile)
/////////////////////////////////////////////////////////////////////////////////////
{
	cFileManager *fmanager = cRoot::Singleton()->GetFileManager();
	cTextureManager *tmanager = cRoot::Singleton()->GetTextureManager();

	sModelHeader modelHeader;
	cIFile *file;
	sFrame frame;
	sFramePoint fpoint;
	sTexCoord texcoord;
	sMeshIndex indexList;
	cGeometryData *mesh;
    
	file = fmanager->OpenFile(modelFile);
	
	// File does not exist
	if (!file)
		return false;

	file->Read (&modelHeader, sizeof(sModelHeader));

	file->Seek (modelHeader.offsetFrames, SEEK_SET);

	for (int currFrame = 0; currFrame < modelHeader.numFrames; currFrame++)
	{
		mesh = new cGeometryData ();

		// Clear out the original mesh
		ZeroMemory (mesh, sizeof (cGeometryData));

		file->Read (&frame, sizeof(sFrame));
	
		// Create the verticies
		mesh->pVertex = new cGeometryData::_vertex [modelHeader.numPoints];
		mesh->numVerticies = modelHeader.numPoints;

		// Load in the vertecies for this frame
		cGeometryData::_vertex *vertex = (cGeometryData::_vertex *)mesh->pVertex;

		for (int i = 0; i < mesh->numVerticies; i++)
		{
			file->Read(&fpoint, sizeof(sFramePoint));
			vertex[i].x = frame.scale[0] * fpoint.v[0] + frame.translate[0];
			vertex[i].y = frame.scale[1] * fpoint.v[1] + frame.translate[1];
			vertex[i].z = frame.scale[2] * fpoint.v[2] + frame.translate[2];
		}
	
		m_geometry.numVerticies = mesh->numVerticies;
		// Add the frame to the animation
		AddFrame (frame.name, mesh);
	}

	// Create the vertex index
	m_geometry.numVertexIndecies = modelHeader.numTris * 3;
	m_geometry.pVertexIndex = new unsigned short [modelHeader.numTris * 3];

	m_geometry.pTextureIndex = new unsigned short [m_geometry.numVertexIndecies];

	// Load in the vertex index buffer
	file->Seek (modelHeader.offsetTris, SEEK_SET);
	for (int i = 0; i < modelHeader.numTris; i++)
	{
		file->Read (&indexList, sizeof(sMeshIndex));

		m_geometry.pVertexIndex[i * 3 + 0] = indexList.meshIndex[0];
		m_geometry.pVertexIndex[i * 3 + 1] = indexList.meshIndex[1];
		m_geometry.pVertexIndex[i * 3 + 2] = indexList.meshIndex[2];

		m_geometry.pTextureIndex[i * 3 + 0] = indexList.stIndex[0];
		m_geometry.pTextureIndex[i * 3 + 1] = indexList.stIndex[1];
		m_geometry.pTextureIndex[i * 3 + 2] = indexList.stIndex[2];
	}

	m_geometry.hasTexture = true;
	m_geometry.numTextures = 1;

	// Load in the texture coordinates
	file->Seek (modelHeader.offsetTexPoints, SEEK_SET);
	cGeometryData::_texcoord *texCoord = new cGeometryData::_texcoord [modelHeader.numTexPoints];

	m_geometry.pTexCoord[0] = new cGeometryData::_texcoord [modelHeader.numTexPoints];
	cGeometryData::_texcoord *tc = (cGeometryData::_texcoord *)m_geometry.pTexCoord[0];

	for (int i = 0; i < modelHeader.numTexPoints; i++)
	{
		file->Read(&texcoord, sizeof(sTexCoord));
		tc[i].s = (float)texcoord.s / (float)modelHeader.skinWidth;
		tc[i].t = (float)texcoord.t / (float)modelHeader.skinHeight;
	}

    fmanager->CloseFile(file);
	m_texture = tmanager->LoadTexture(skinFile);

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
void cMD2Model::DoDraw( float deltaTime )
/////////////////////////////////////////////////////////////////////////////////////
{
	static cTextureManager *tmanager = cRoot::Singleton()->GetTextureManager();
	
	if (!m_currVertex)
		m_currVertex = new cGeometryData::_vertex[m_geometry.numVerticies];
    
	m_t += deltaTime * 5.f;
	if (m_t > 1.0f)
	{
		m_currFrame = (m_currFrame + 1) % m_currKeyFrame->size();
		while (m_t > 1.0f)
			m_t -= 1.0f;
	}

	tmanager->BindTexture(m_texture);

	// Get the geometry data for this and next frame
	cGeometryData::_texcoord *texcoord	= (cGeometryData::_texcoord *)m_geometry.pTexCoord[0];
	cGeometryData::_vertex *vertex1		= (cGeometryData::_vertex *)(*m_currKeyFrame)[m_currFrame]->pVertex;
	cGeometryData::_vertex *vertex2		= (cGeometryData::_vertex *)(*m_currKeyFrame)[(m_currFrame + 1) % m_currKeyFrame->size()]->pVertex;
	
	for (int i = 0; i < m_geometry.numVerticies; i++)
	{
		m_currVertex[i].x = ((1 - m_t) * vertex1[i].x + (m_t) * vertex2[i].x);
		m_currVertex[i].y = ((1 - m_t) * vertex1[i].y + (m_t) * vertex2[i].y);
		m_currVertex[i].z = ((1 - m_t) * vertex1[i].z + (m_t) * vertex2[i].z);
	}

	glBegin (GL_TRIANGLES);
		for (int i = 0; i < m_geometry.numVertexIndecies; i++)
		{
			glTexCoord2fv (texcoord[m_geometry.pTextureIndex[i]].v);
			glVertex3fv (m_currVertex[m_geometry.pVertexIndex[i]].v);
		}
	glEnd();

}

/////////////////////////////////////////////////////////////////////////////////////
void cMD2Model::Animate(int startFrame, int endFrame, float percent)
/////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////
std::string cMD2Model::GetFrameName(std::string framename)
/////////////////////////////////////////////////////////////////////////////////////
{
	int drop = 0;
	
	// Drop the last 2 digits
	for (int i = 0; i < 4; i++)
	{
		if (isdigit(framename[framename.size() - (i + 1)]))
			drop++;
		else
			break;
	}

	return framename.substr(0, framename.size() - drop);
}

/////////////////////////////////////////////////////////////////////////////////////
void cMD2Model::AddFrame(std::string framename, cGeometryData *mesh)
/////////////////////////////////////////////////////////////////////////////////////
{
	m_animations[GetFrameName (framename)].push_back (mesh);
}