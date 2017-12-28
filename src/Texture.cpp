#include "Texture.h"
#include "TGA.h"
#include "ogles_sys.h"
#include "Object.h"
#include "Log.h"

Texture::Texture(char* pathToLoad, char * nameTex)
{
	TGAInfo tgaInfor;
	m_varNameTex = nameTex;

	// texIdx
	glGenTextures(1, &m_texIdx);
	glBindTexture(GL_TEXTURE_2D, m_texIdx);

	tgaInfor.m_data = LoadTGA(pathToLoad, &tgaInfor.m_width, &tgaInfor.m_height, &tgaInfor.m_bpp);
	GLuint format;
	if (tgaInfor.m_bpp == 24)
	{
		format = GL_RGB;
	}
	else if (tgaInfor.m_bpp == 32)
	{
		format = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, tgaInfor.m_width, tgaInfor.m_height, 0, format, GL_UNSIGNED_BYTE, tgaInfor.m_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Render(GLuint programIdx, int idx)
{
	// Active Texture
	glUseProgram(programIdx);
	glActiveTexture(GL_TEXTURE0 + idx);
	glBindTexture(GL_TEXTURE_2D, m_texIdx);
	GLint texUniform = glGetUniformLocation(programIdx, m_varNameTex);
	if (texUniform != -1)
		glUniform1i(texUniform, idx);
	else
		LOGI("Texture", "Can't glGetUniformLocation");
}


Texture::~Texture()
{
}
