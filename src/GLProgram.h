#pragma once
#include "ogles_sys.h"
#include "glm.hpp"
#include "MutualStructs.h"
//#include "Model.h"
#include "Texture.h"

class GLProgram
{
protected:
	GLuint m_program;
	//GLuint m_fragmentShaderIdx;
	//GLuint m_vertexShaderIdx;
	//
	//int			m_numTex;
	//Texture **   m_texture;
	//Model  *    m_model;
	//
	//glm::mat4x4 m_MVPMatrix;
	//glm::mat4x4 m_ModelMatrix;

	
	GLuint CompileProgram(const char * vertexSrc, const char * pixelSrc);

public:
	// Returns the GL program object for the shader
	// \return the GL shader object ID
	GLuint getProgram() { return m_program; }
	// Binds the given shader program as current in the GL context
	void enable();

	// Unbinds the given shader program from the GL context (binds shader 0)
	void disable();

	//GLProgram(char* pathShader, char* pathModel, int numTex, char ** varNameTex, int numPath, char ** pathTex, TypeTexture type);
	~GLProgram() { glDeleteProgram(m_program); }

	//GLuint GetId() { return m_programIdx; }
	//void SetModelMatrix(glm::mat4x4 mat);
	//void SetMatrixMVP(glm::mat4x4 mat);
	//void Render();
};