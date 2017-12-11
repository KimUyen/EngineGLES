#pragma once
#include <vector>

class GLModel
{
protected:
public:
	bool ImportModelFromFile(char * filePath);
protected:
	bool ImportModelFromNFGFile(char* path);
	std::vector<float> _positions;
	std::vector<float> _normals;
	std::vector<float> _texCoords;
	std::vector<float> _sTangents;
	std::vector<float> _colors;

};


//#include "MutualStructs.h"
//
//class Model
//{
//private:
//	// Model
//	NFGVertex * m_pVertices;
//	int         m_nVertices;
//	GLushort  * m_pIndices;
//	int         m_nIndices;
//	GLuint		m_VerticesBufferIdx;
//	GLuint		m_IndicesBufferIdx;
//
//public:
//	Model(char * pathToLoad);
//	void Render(GLuint programId);
//};