#include "DispTex.h"
#include "MutualStructs.h"
#include "TGA.h"


DispTex::DispTex(char ** pathToLoad, int size)
{
	m_nTGA = size;
	m_TGA = new TGAInfo[m_nTGA];

	// texIdx
	glGenTextures(m_nTGA, &m_texIdx);
	glBindTexture(GL_TEXTURE_2D, m_texIdx);

	for (int i = 0; i < m_nTGA; i++)
	{
		m_TGA[i].m_data = LoadTGA(pathToLoad[i], &m_TGA[i].m_width, &m_TGA[i].m_height, &m_TGA[i].m_bpp);
		GLuint format;
		if (m_TGA[i].m_bpp == 24)
		{
			format = GL_RGB;
		}
		else if (m_TGA[i].m_bpp == 32)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_TGA[i].m_width, m_TGA[i].m_height, 0, format, GL_UNSIGNED_BYTE, m_TGA[i].m_data);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DispTex::Render(GLuint programIdx)
{
	// Active Texture

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texIdx);
	GLint texUniform = glGetUniformLocation(programIdx, "u_cube_tex");
	glUniform1i(texUniform, 0);
}

DispTex::~DispTex()
{
}
