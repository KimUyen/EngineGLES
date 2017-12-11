#include "GLProgram.h"
#include "ogles_sys.h"
#include <stdio.h>
#include "glm.hpp"
#include "CubeTex.h"
#include "CameraManager.h"
#include "Log.h"

namespace opengl
{
	GLuint CompileShader(GLenum type, const char* filename)
	{
		FILE * file;
		if (fopen_s(&file, filename, "rb") != 0)
		{
			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			fseek(file, 0, SEEK_SET);
			char * shaderSrc = new char[size + 1];
			fread(shaderSrc, sizeof(char), size, file);
			shaderSrc[size] = '\0';
			fclose(file);

			// create a shader and get his handle.
			// The type can be either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
			GLuint shader = glCreateShader(type);
			GLint compiled = 0;

			if (shader != 0)
			{
				// send the shader source code to be compiled - shadersrc
				glShaderSource(shader, 1, (const char **)&shaderSrc, NULL);
				delete[] shaderSrc;

				// Compile the shader
				glCompileShader(shader);
				// Check the compile status
				glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

				// Compilation has failed
				if (!compiled)
				{
					GLint infoLen = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

					if (infoLen)
					{
						char* infoLog = new char[infoLen];
						glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
						LOGE("GLProgram", "Error compiling shader:\n%s\n", infoLog);
						delete[] infoLog;
					}

					glDeleteShader(shader);
					return 0;
				}

				return shader;
			}

			delete[] shaderSrc;
			LOGE("GLProgram", "Can't create shader\n");
			return 0;
		}

		LOGE("GLProgram", "Fail to find %s\n", filename);
		return 0;
	}

	GLuint GLProgram::CompileProgram(const char * vertexSrc, const char * pixelSrc)
	{
		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		GLuint pixelShader = CompileShader(GL_FRAGMENT_SHADER, pixelSrc);
		if (vertexShader == 0 || pixelShader == 0)
		{
			LOGE("GLProgram", "Could not load vertexShader file %s\n", (vertexSrc) ? vertexSrc : "null");
			LOGE("GLProgram", "Could not load pixelShader file %s\n", (pixelSrc) ? pixelSrc : "null");
			return 0;
		}

		// Create the program object
		GLuint program = glCreateProgram();
		if (program)
		{
			// Attach shader to program
			glAttachShader(program, vertexShader);
			glAttachShader(program, pixelShader);
			// can be deleted since the program will keep a reference
			glDeleteShader(vertexShader);
			glDeleteShader(pixelShader);
			// Link the program
			glLinkProgram(program);

			// Check the link status
			GLint linkStatus = GL_FALSE;
			glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

			if (!linkStatus)
			{
				GLint bufLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
				if (bufLength) {
					char* buf = new char[bufLength];
					if (buf) {
						glGetProgramInfoLog(program, bufLength, NULL, buf);
						LOGE("GLProgram", "Could not link program:\n%s\n", buf);
						delete[] buf;
					}
				}
				glDeleteProgram(program);
				program = 0;
			}

			return program;
		}

		LOGE("GLProgram", "Could not create program:\n");
		return 0;
	}


	void GLProgram::enable()
	{
		glUseProgram(m_program);
	}

	void GLProgram::disable()
	{
		glUseProgram(0);
	}

	//void Shader::SetModelMatrix(glm::mat4x4 mat)
	//{
	//	m_ModelMatrix = mat;
	//}
	//
	//void Shader::SetMatrixMVP(glm::mat4x4 mat)
	//{
	//	m_MVPMatrix = mat;
	//}
	//
	//void Shader::Render()
	//{
	//	glUseProgram(m_programIdx);
	//
	//	for (int i = 0; i < m_numTex; i++)
	//	{
	//		m_texture[i]->Render(m_programIdx, i);
	//	}
	//
	//	GLint mvpUniform = glGetUniformLocation(m_programIdx, "u_mvp");
	//	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, (GLfloat*)&m_MVPMatrix);
	//
	//	GLint modelUniform = glGetUniformLocation(m_programIdx, "u_model");
	//	if (modelUniform != -1)
	//	{
	//		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, (GLfloat*)&m_ModelMatrix);
	//	}
	//
	//	GLint transInvModelUniform = glGetUniformLocation(m_programIdx, "u_TransInvModel");
	//	if (transInvModelUniform != -1)
	//	{
	//		glUniformMatrix4fv(transInvModelUniform, 1, GL_FALSE, (GLfloat*)&glm::transpose(glm::inverse(m_ModelMatrix)));
	//	}
	//
	//	GLint posCamUniform = glGetUniformLocation(m_programIdx, "u_camPosition");
	//	if (posCamUniform != -1)
	//	{
	//		glUniform3fv(posCamUniform, 1, (GLfloat*)&CameraManager::GetInstance()->GetCurrentCamera()->GetPosCamera());
	//	}
	//
	//	m_model->Render(m_programIdx);
	//}
	//
	//Shader::Shader(char* pathShader, char* pathModel, int numTex, char ** varNameTex, int numPath, char ** pathTex, TypeTexture type)
	//{
	//	char * pathVertex = new char[strlen(pathShader)];
	//	char * pathFragment = new char[strlen(pathShader)];
	//	strcpy(pathVertex, pathShader);
	//	strcpy(pathFragment, pathShader);
	//	strcat(pathFragment, ".fs");
	//	strcat(pathVertex, ".vs");
	//
	//
	//	LoadShader(GL_VERTEX_SHADER, pathVertex);
	//	LoadShader(GL_FRAGMENT_SHADER, pathFragment);
	//
	//	LoadProgram();
	//
	//	// Texture
	//	m_numTex = numTex;
	//
	//	switch (type)
	//	{
	//	case TypeTexture::TEX_2D:
	//		m_texture = new Texture *[m_numTex];
	//		for (int i = 0; i < m_numTex; i++)
	//		{
	//			m_texture[i] = new Texture(pathTex[i], varNameTex[i]);
	//		}
	//		break;
	//
	//	case TypeTexture::TEX_CUBE:
	//		m_texture = new Texture *[1];
	//		m_texture[0] = (Texture*)(new CubeTex(pathTex, numPath, varNameTex[0]));
	//		break;
	//
	//	default:
	//		break;
	//
	//	}
	//
	//
	//	// Model
	//	m_model = new Model(pathModel);
	//
	//	// VP_Matrix, changePos
	//	m_MVPMatrix = glm::mat4x4(1);
	//}
	//
	//Shader::~Shader()
	//{
	//}
}