#include "CubeTex.h"
#include "TGA.h"

CubeTex::CubeTex(char ** pathToLoad, int size, char * nameTex)
{
	TGAInfo tgaInfor;
	m_varNameTex = nameTex;

	// texIdx
	glGenTextures(1, &m_texIdx);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texIdx);

	for (int i = 0; i < size; i++)
	{
		tgaInfor.m_data = LoadTGA(pathToLoad[i], &tgaInfor.m_width, &tgaInfor.m_height, &tgaInfor.m_bpp);
		GLuint format;
		if (tgaInfor.m_bpp == 24)
		{
			format = GL_RGB;
		}
		else if (tgaInfor.m_bpp == 32)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, tgaInfor.m_width, tgaInfor.m_height, 0, format, GL_UNSIGNED_BYTE, tgaInfor.m_data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeTex::Render(GLuint programIdx, int idx)
{
	// Active Texture
	glActiveTexture(GL_TEXTURE0 + idx);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texIdx);
	GLint texUniform = glGetUniformLocation(programIdx, m_varNameTex);
	glUniform1i(texUniform, idx);
}

CubeTex::~CubeTex()
{
}
