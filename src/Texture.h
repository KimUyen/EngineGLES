#pragma once
#include "ogles_sys.h"
#include "MutualStructs.h"

class Object;
class Texture
{
protected:
	GLuint	    m_texIdx;
	char *		m_varNameTex;

	Texture() {};

public:
	Texture(char* pathToLoad, char* nameTex);
	~Texture();

	virtual void	Render(GLuint programIdx, int idx);

};

