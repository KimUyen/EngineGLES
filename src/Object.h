#pragma once
#include "ogles_sys.h"
#include "MutualStructs.h"
#include "Texture.h"
#include "GLModel.h"
#include "GLProgram.h"

class Object
{
private:
	//Need for init
	int			m_id;
	//For Model
	GLModel *	m_model;
	GLProgram * m_program;
	int			m_numTex;
	Texture **   m_texture;

	glm::vec3 m_vecTrans;
	glm::vec3 m_vecScale;

	glm::mat4x4 m_ModelMatrix;
	glm::mat4x4 m_MVP;

	float m_angle;
	glm::vec3 m_vecRot;


	void		CalModelMatrix();
public:

	Object(int id);
	~Object();
	bool		LoadModel(char * path);
	void		LoadTexture(int typeTex, char** varTex, int numTex, char ** allpath, int numPath);
	GLuint		CreateProgram(const char * vertexSrc, const char * pixelSrc);
	void		Render();
	// for call before render.
	void		SetScale(glm::vec3 scale);
	void		SetTranslate(glm::vec3 trans);
	void		SetRotate(float angle, glm::vec3 vecRot);

	void		SetValueForUniformMatrix4FV(char * nameVar, const GLfloat * value);
	void		SetValueForUniform1F(char * nameVar, GLfloat value);
	void        SetValueForUniform3FV(char * nameVar, const GLfloat * value);
	void		SetValueForUniform4FV(char * nameVar, const GLfloat * value);
};
