#pragma once
#include "MutualStructs.h"
#include "Texture.h"

class CubeTex : public Texture
{
protected:
public:
	CubeTex(char** pathToLoad, int size, char * nameTex);
	void Render(GLuint programIdx, int idx);
	~CubeTex();
};