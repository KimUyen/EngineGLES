#include "Camera.h"
#include "MutualStructs.h" 
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtx\rotate_vector.hpp"
#include "ogles_sys.h"


Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float fovy, float aspect, float zNear, float zFar)
{
	m_position = pos;
	m_target = target;
	//m_worldUp = up;
	
	m_fovy = fovy;
	m_aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;

	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;

	UpdateCameraVetors();
}

void Camera::UpdateCameraVetors()
{
	//glm::vec3 target;
	//
	//target.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	//target.y = sin(glm::radians(m_pitch));
	//target.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	//m_target = glm::normalize(target);
	//
	//m_right = glm::normalize(glm::cross(m_target, m_worldUp));
	//m_up = glm::normalize(glm::cross(m_right, m_target));

	m_MatrixView = CalViewMatrix();
	m_MatrixProjection = CalProjMatrix();
	CalVPMatrix();
}

glm::mat4x4 Camera::CalViewMatrix()
{
	//m_MatrixView = glm::lookAt(m_position, m_target, m_up);
	glm::mat4 matT, matRx, matRz, matRy, matR;
	matT = glm::translate(matT, m_position);
	
	matRx = glm::rotate(matRx, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matRy = glm::rotate(matRy, m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	matRz = glm::rotate(matRz, m_roll, glm::vec3(0.0f, 0.0f, 1.0f));

	matR = matRy * matRx * matRz;
	m_MatrixView = glm::inverse(matT * matR);

	return m_MatrixView;
}

glm::mat4x4 Camera::CalProjMatrix()
{
	m_MatrixProjection = glm::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
	return m_MatrixProjection;
}

void Camera::Move(DirectMove direct, float deltaTime, float speed)
{
	glm::vec3 vecMove = glm::vec3(0.0f, 0.0f, 0.0f);

	switch (direct)
	{
	case DirectMove::DM_LEFT:
		vecMove.x -= deltaTime * speed;
		break;
	
	case DirectMove::DM_RIGHT:
		vecMove.x += deltaTime * speed;
		break;
	
	case DirectMove::DM_BACKWARD:
		vecMove.z += deltaTime * speed;
		break;
	
	case DirectMove::DM_FORWARD:
		vecMove.z -= deltaTime * speed;
		break;

	case DirectMove::DM_UP:
		vecMove.y += deltaTime * speed;
		break;

	case DirectMove::DM_DOWN:
		vecMove.y -= deltaTime * speed;
		break;

	default:
		break;
	}

	
	m_position += vecMove;
	m_target += vecMove;

	UpdateCameraVetors();
}

void Camera::Rotate(DirectRotate direct, float angle)
{
	glm::mat4x4 matRotate = glm::mat4x4(1.0f);

	switch (direct)
	{
	case DirectRotate::DR_LEFTaroundY:
		m_yaw -= angle;
		break;
	
	case DirectRotate::DR_RIGHTaroundY:
		m_yaw += angle;
		break;
	
	case DirectRotate::DR_DOWNaroundX:
		m_pitch -= angle;
		break;
	
	case DirectRotate::DR_UParoundX:
		m_pitch += angle;
		break;

	case DirectRotate::DR_LEFTaroundZ:
		m_roll -= angle;
		break;

	case DirectRotate::DR_RIGHTaroundZ:
		m_roll += angle;
		break;

	default:
		break;
	}

	UpdateCameraVetors();
}

Camera::~Camera()
{
}
