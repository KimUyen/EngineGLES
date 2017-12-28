#pragma once
#include "ogles_sys.h"
#include "MutualStructs.h"

enum TypeTexture
{
	TEX_2D,
	TEX_CUBE
};

class Object;
class Texture
{
protected:
	GLuint	    m_texIdx;
	char *		m_varNameTex;
	TypeTexture m_type;

	Texture() {};

public:
	Texture(char* pathToLoad, char* nameTex);
	//bool LoadTexture();
	~Texture();

	virtual void	Render(GLuint programIdx, int idx);

};

