#pragma once

#include <windows.h>
#include <gl/gl.h>

#include <vector>
#include <string>

#include "../Core/cSingleton.h"
#include "cTexture.h"

class cTextureManager : public cSingleton <cTextureManager>
{
public:
	cTextureManager(void);
	~cTextureManager(void);

	void ClearAll ();
	void DeleteTexture (int texNum);

	int LoadTexture (std::string filename);
	int LoadTexture (unsigned char *image, unsigned int width, unsigned int height,
						unsigned int bpp);

	inline void BindTexture (int texNum) 
	{
		static currentTex = -1;
		
		if (texNum >= 0 && texNum != currentTex)
				glBindTexture (GL_TEXTURE_2D, m_textures[texNum]->GetTextureNumber());
		currentTex = texNum;
	}

	cTexture *GetTexture (int texNum) { return m_textures[texNum]; }
	int GetFreeTexture ();

protected:
	std::vector <cTexture *> m_textures;

};
