#pragma once
#include "Texture.h"

class DispTex : public Texture
{
public:
	DispTex(char** pathToLoad, int size);
	void Render(GLuint programIdx);
	~DispTex();
};

