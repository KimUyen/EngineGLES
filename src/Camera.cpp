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
	////m_worldUp = up;
	m_up = up;
	
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
	////glm::vec3 target;
	////
	////target.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	////target.y = sin(glm::radians(m_pitch));
	////target.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	////m_target = glm::normalize(target);
	////
	////m_right = glm::normalize(glm::cross(m_target, m_worldUp));
	////m_up = glm::normalize(glm::cross(m_right, m_target));

	m_MatrixView = CalViewMatrix();
	m_MatrixProjection = CalProjMatrix();
	CalVPMatrix();
}

glm::mat4x4 Camera::GetRotationMatrix()
{
	glm::vec3 zaxis = glm::normalize(m_position - m_target);
	glm::vec3 xaxis = glm::normalize(glm::cross(m_up, zaxis));
	glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));
	return glm::mat4x4( xaxis.x, xaxis.y, xaxis.z, 0,
						yaxis.x, yaxis.y, yaxis.z, 0, 
						zaxis.x, zaxis.y, zaxis.z, 0, 
						0, 0, 0, 1);
}

glm::mat4x4 Camera::CalViewMatrix()
{
	////m_MatrixView = glm::lookAt(m_position, m_target, m_up);
	//glm::mat4 matT, matRx, matRz, matRy, matR;
	//matT = glm::translate(matT, m_position);
	//
	//matRx = glm::rotate(matRx, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	//matRy = glm::rotate(matRy, m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	//matRz = glm::rotate(matRz, m_roll, glm::vec3(0.0f, 0.0f, 1.0f));
	//
	//matR = matRy * matRx * matRz;
	//m_MatrixView = glm::inverse(matT * matR);
	
	glm::vec3 zaxis = glm::normalize(m_position - m_target);
	glm::vec3 xaxis = glm::normalize(glm::cross(m_up, zaxis));
	glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

	m_MatrixView = glm::mat4x4( xaxis.x, yaxis.x, zaxis.x, 0,
								xaxis.y, yaxis.y, zaxis.y, 0, 
								xaxis.z, yaxis.z, zaxis.z, 0, 
								-glm::dot(m_position, xaxis), -glm::dot(m_position, yaxis), -glm::dot(m_position, zaxis), 1);
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

	//vecMove *= - glm::normalize(m_position - m_target);
	vecMove *= -(m_position - m_target).length();

	m_position += vecMove;
	m_target += vecMove;

	UpdateCameraVetors();
}

void Camera::Rotate(DirectRotate direct, float angle)
{
	glm::vec4 localTarget = glm::vec4(-(m_position - m_target), 1.0f);
	glm::vec4 newlocalTarget;
	glm::mat4x4 matRotate = glm::mat4x4(1.0f);
	//glm::mat4x4 matRotate = GetRotationMatrix();

	switch (direct)
	{
	case DirectRotate::DR_LEFTaroundY:
		//m_yaw -= angle;
		newlocalTarget = localTarget * glm::rotate(matRotate, -angle, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	
	case DirectRotate::DR_RIGHTaroundY:
		//m_yaw += angle;
		newlocalTarget = localTarget * glm::rotate(matRotate, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	
	case DirectRotate::DR_DOWNaroundX:
		//m_pitch -= angle;
		newlocalTarget = localTarget * glm::rotate(matRotate, -angle, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	
	case DirectRotate::DR_UParoundX:
		//m_pitch += angle;
		newlocalTarget = localTarget * glm::rotate(matRotate, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		break;

	case DirectRotate::DR_LEFTaroundZ:
		//m_roll -= angle;
		newlocalTarget = localTarget * glm::rotate(matRotate, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
		break;

	case DirectRotate::DR_RIGHTaroundZ:
		//m_roll += angle;
		newlocalTarget = localTarget * glm::rotate(matRotate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		break;

	default:
		break;
	}

	m_target = m_position + glm::vec3(newlocalTarget.x, newlocalTarget.y, newlocalTarget.z);
	UpdateCameraVetors();
}

void Camera::RotateAroundObject(DirectRotate direct, float angle)
{
	//glm::vec3 pre_pos = m_position;
	//m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	//Rotate(direct, angle);
	//m_position = 
	//UpdateCameraVetors();

	glm::vec4 localPosition = glm::vec4((m_position - m_target), 1.0f);
	glm::vec4 newlocalPosition;
	glm::mat4x4 matRotate = glm::mat4x4(1.0f);
	//glm::mat4x4 matRotate = GetRotationMatrix();

	switch (direct)
	{
	case DirectRotate::DR_LEFTaroundY:
		//m_yaw -= angle;
		newlocalPosition = localPosition * glm::rotate(matRotate, -angle, glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case DirectRotate::DR_RIGHTaroundY:
		//m_yaw += angle;
		newlocalPosition = localPosition * glm::rotate(matRotate, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case DirectRotate::DR_DOWNaroundX:
		//m_pitch -= angle;
		newlocalPosition = localPosition * glm::rotate(matRotate, -angle, glm::vec3(1.0f, 0.0f, 0.0f));
		break;

	case DirectRotate::DR_UParoundX:
		//m_pitch += angle;
		newlocalPosition = localPosition * glm::rotate(matRotate, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		break;

	case DirectRotate::DR_LEFTaroundZ:
		//m_roll -= angle;
		newlocalPosition = localPosition * glm::rotate(matRotate, -angle, glm::vec3(0.0f, 0.0f, 1.0f));
		break;

	case DirectRotate::DR_RIGHTaroundZ:
		//m_roll += angle;
		newlocalPosition = localPosition * glm::rotate(matRotate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		break;

	default:
		break;
	}

	m_position = /*m_position +*/m_target + glm::vec3(newlocalPosition.x, newlocalPosition.y, newlocalPosition.z);
	UpdateCameraVetors();
}

Camera::~Camera()
{
}
