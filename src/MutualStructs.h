#pragma once
#include <stdio.h>
#include "ogles_sys.h"
#include "glm.hpp"


struct TGAInfo
{
	int		m_height, m_width, m_bpp;
	char *	m_data;
};

struct NFGVertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 binorm;
	glm::vec3 tgt;
	glm::vec2 uv;
};

enum DirectMove
{
	DM_BACKWARD,
	DM_FORWARD,
	DM_LEFT,
	DM_RIGHT,
	DM_UP,
	DM_DOWN
};

enum DirectRotate
{
	DR_UParoundX,
	DR_DOWNaroundX,
	DR_LEFTaroundY,
	DR_RIGHTaroundY,
	DR_LEFTaroundZ,
	DR_RIGHTaroundZ
};

enum TypeTexture
{
	TEX_2D,
	TEX_CUBE
};