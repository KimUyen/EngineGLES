#pragma once
#include "MutualStructs.h" 

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_right;
	glm::vec3 m_up;
	glm::vec3 m_worldUp;

	float m_fovy, m_aspect, m_zNear, m_zFar;
	float m_yaw, m_pitch, m_roll;

	glm::mat4x4 m_MatrixProjection;
	glm::mat4x4 m_MatrixView;
	glm::mat4x4 m_VP;

	void UpdateCameraVetors();
	glm::mat4x4 CalVPMatrix() { m_VP = m_MatrixProjection * m_MatrixView; return m_VP; }
public:

	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 right, float fovy, float aspect, float zNear, float zFar);
	~Camera();

	glm::mat4x4 GetVPMatrix() { return m_VP; }
	glm::vec3   GetPosCamera() { return m_position; }
	glm::mat4x4 CalViewMatrix();
	glm::mat4x4 CalProjMatrix();

	void Move(DirectMove direct, float deltaTime, float speed);
	void Rotate(DirectRotate direct, float angle);

};

