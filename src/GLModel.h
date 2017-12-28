#pragma once
#include <vector>
#include <windows.h>
#include <gl\GLU.h>
#include "MutualStructs.h"
class GLModel
{
protected:
public:
	bool ImportModelFromFile(char * filePath);
	void Render(GLuint programIdx);
protected:
	bool ImportModelFromNFGFile(char* path);
	void InitBuffer();
	//std::vector<float> _positions;
	//std::vector<float> _normals;
	//std::vector<float> _binormals;
	//std::vector<float> _texCoords;
	//std::vector<float> _sTangents;
	//std::vector<float> _colors;
	GLushort *			_pIndices;
	int					 _nIndices;
	NFGVertex *		_pVertices;
	int				_nVertices;

	GLuint		_vboIdx;
	GLuint		_iboIdx;

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