#include "ogles_sys.h"
#include "Model.h"
#include "glm.hpp"
#include "MutualStructs.h"
#include "Texture.h"
#include "Shader.h"
#include <gl\GLU.h>
#include "GLModel.h"




//Model::Model(char * pathToLoad)
//{
//	/////////////////
//	// Load NFG file 
//	/////////////////
//	FILE* f = fopen(pathToLoad, "r");
//	if (f == NULL)
//	{
//		printf("Load NFG failed: %s", pathToLoad);
//		return;
//	}
//
//	// Read vertices
//	fscanf(f, "NrVertices: %d\r\n", &m_nVertices);
//	m_pVertices = new NFGVertex[m_nVertices];
//	int index = 0;
//
//	for (int i = 0; i < m_nVertices; i++)
//	{
//		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
//			&index,
//			&m_pVertices[i].pos.x,
//			&m_pVertices[i].pos.y,
//			&m_pVertices[i].pos.z,
//			&m_pVertices[i].norm.x,
//			&m_pVertices[i].norm.y,
//			&m_pVertices[i].norm.z,
//			&m_pVertices[i].binorm.x,
//			&m_pVertices[i].binorm.y,
//			&m_pVertices[i].binorm.z,
//			&m_pVertices[i].tgt.x,
//			&m_pVertices[i].tgt.y,
//			&m_pVertices[i].tgt.z,
//			&m_pVertices[i].uv.x,
//			&m_pVertices[i].uv.y
//		);
//
//		//m_pVertices[i].pos.y += -0.8;
//	}
//
//	// read indices
//	fscanf(f, "NrIndices: %d\r\n", &m_nIndices);
//	m_pIndices = new GLushort[m_nIndices];
//	int x, y, z;
//
//	for (int i = 0; i < m_nIndices; i += 3)
//	{
//		fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
//		m_pIndices[i] = (GLushort)x;
//		m_pIndices[i + 1] = (GLushort)y;
//		m_pIndices[i + 2] = (GLushort)z;
//	}
//
//	// clean up
//	fclose(f);
//	printf("[LOADED] Model: %s\n", pathToLoad);
//
//	////////////////////////
//	//put it into buffer
//	///////////////////////
//	// vboIdx
//	glGenBuffers(1, &m_VerticesBufferIdx);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VerticesBufferIdx);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(NFGVertex) * m_nVertices, m_pVertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// iboIdx
//	glGenBuffers(1, &m_IndicesBufferIdx);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferIdx);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_nIndices, m_pIndices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//void Model::Render(GLuint programIdx)
//{
//	glUseProgram(programIdx);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VerticesBufferIdx);
//
//	GLint attribPos = glGetAttribLocation(programIdx, "a_posL");
//	glEnableVertexAttribArray(attribPos);
//	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, sizeof(NFGVertex), NULL);
//
//	GLint attribNorm = glGetAttribLocation(programIdx, "a_normL");
//	if (attribNorm != -1)
//	{
//		glEnableVertexAttribArray(attribNorm);
//		glVertexAttribPointer(attribNorm, 3, GL_FLOAT, GL_FALSE, sizeof(NFGVertex), (GLvoid*)offsetof(NFGVertex,norm));
//	}
//
//	GLint attribUV = glGetAttribLocation(programIdx, "a_uvL");
//	if (attribUV != -1)
//	{
//		glEnableVertexAttribArray(attribUV);
//		glVertexAttribPointer(attribUV, 2, GL_FLOAT, GL_FALSE, sizeof(NFGVertex), (GLvoid*)offsetof(NFGVertex, uv));
//	}
//
//	GLint attribTGT = glGetAttribLocation(programIdx, "a_tgtL");
//	if (attribTGT != -1)
//	{
//		glEnableVertexAttribArray(attribTGT);
//		glVertexAttribPointer(attribTGT, 3, GL_FLOAT, GL_FALSE, sizeof(NFGVertex), (GLvoid*)offsetof(NFGVertex, tgt));
//	}
//
//	GLint attribBinorm = glGetAttribLocation(programIdx, "a_binormL");
//	if (attribBinorm != -1)
//	{
//		glEnableVertexAttribArray(attribBinorm);
//		glVertexAttribPointer(attribBinorm, 3, GL_FLOAT, GL_FALSE, sizeof(NFGVertex), (GLvoid*)offsetof(NFGVertex, binorm));
//	}
//	// Begin draw
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferIdx);
//	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_SHORT, NULL);
//}

bool GLModel::ImportModelFromFile(char * filePath)
{
	return false;
}
