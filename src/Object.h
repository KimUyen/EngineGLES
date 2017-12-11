#pragma once
#include "ogles_sys.h"
#include "MutualStructs.h"
#include "Texture.h"
#include "Shader.h"

	class Object
	{
	private:
		//Need for init
		int			m_TypeTex;
		//For Shader
		Shader *	m_shader;

		glm::mat4x4 m_ModelMatrix;
		glm::mat4x4 m_MVP;
		glm::vec3 m_vecTrans;
		glm::vec3 m_vecScale;
		float m_angle;
		glm::vec3 m_vecRot;


		void		CalModelMatrix();
	public:

		Object(int id, char * pathShader, char *pathModel, int numTex, char ** varNameTex, int numPath, char ** pathTex);
		~Object();

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
