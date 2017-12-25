#include "ogles_sys.h"
#include "Object.h"
#include "glm.hpp"
#include "MutualStructs.h"
#include "Texture.h"
//#include "Shader.h"
#include "gtc\matrix_transform.hpp"
#include "CameraManager.h"
#include <windows.h>
#include <gl\GLU.h>

void Object::CalModelMatrix()
{
	glm::mat4x4 matTrans = glm::translate(glm::mat4x4(1.0f), m_vecTrans);
	glm::mat4x4 matScale = glm::scale(glm::mat4x4(1.0f), m_vecScale);
	glm::mat4x4 matRot = glm::rotate(glm::mat4x4(1.0f), m_angle, m_vecRot);

	m_ModelMatrix = matScale * matRot * matTrans;
}

bool Object::LoadModel(char * path)
{
	return m_model->ImportModelFromFile(path);
}

GLuint Object::CompileProgram(const char * vertexSrc, const char * pixelSrc)
{
	return m_program->CompileProgram(vertexSrc, pixelSrc);
}

//Object::Object(int id, char * pathShader, char *pathModel, int numTex, char ** varNameTex, int numPath, char ** pathTex)
Object::Object(int id)
{
	m_TypeTex = id;
	m_ModelMatrix = glm::mat4x4(1.0f);
	m_vecTrans = glm::vec3(0.0f, 0.0f, 0.0f);
	m_angle = 0.0f;
	m_vecScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_vecRot = glm::vec3(0.0f, 1.0f, 0.0f);

	m_model = new GLModel();
	m_program = new GLProgram();
	// Load Shader
	//m_shader = new Shader(pathShader, pathModel, numTex, varNameTex, numPath, pathTex, (TypeTexture)m_TypeTex);
}

Object::~Object()
{
}

void Object::Render()
{
	//m_shader->SetModelMatrix(m_ModelMatrix);
	SetValueForUniformMatrix4FV("u_model", (GLfloat*)&m_ModelMatrix);
	SetValueForUniformMatrix4FV("u_mvp", (GLfloat*)&(CameraManager::GetCurrentCamera()->GetVPMatrix() * m_ModelMatrix));
	//m_shader->SetMatrixMVP(glm::mat4x4(1));
	//m_shader->Render();
}


void Object::SetScale(glm::vec3 scale)
{
	m_vecScale *= scale;
	CalModelMatrix();
}

void Object::SetTranslate(glm::vec3 trans)
{
	m_vecTrans += trans;
	CalModelMatrix();
}

void Object::SetRotate(float angle, glm::vec3 vecRot)
{
	m_angle += angle;
	m_vecRot = vecRot;
	CalModelMatrix();
}

void Object::SetValueForUniformMatrix4FV(char * nameVar, const GLfloat * value)
{
	glUseProgram(m_program->getProgram());
	GLint idUniform = glGetUniformLocation(m_program->getProgram(), nameVar);
	if (idUniform != -1)
	{
		glUniformMatrix4fv(idUniform, 1, GL_FALSE, value);
	}
}

void Object::SetValueForUniform1F(char * nameVar, GLfloat value)
{
	glUseProgram(m_program->getProgram());
	GLint idUniform = glGetUniformLocation(m_program->getProgram(), nameVar);
	if (idUniform != -1)
	{
		glUniform1f(idUniform, value);
	}
}

void Object::SetValueForUniform3FV(char * nameVar, const GLfloat * value)
{
	glUseProgram(m_program->getProgram());
	GLint idUniform = glGetUniformLocation(m_program->getProgram(), nameVar);
	if (idUniform != -1)
	{
		glUniform3fv(idUniform, 1, value);
	}
}

void Object::SetValueForUniform4FV(char * nameVar, const GLfloat * value)
{
	glUseProgram(m_program->getProgram());
	GLint idUniform = glGetUniformLocation(m_program->getProgram(), nameVar);
	if (idUniform != -1)
	{
		glUniform4fv(idUniform, 1, value);
	}
}
