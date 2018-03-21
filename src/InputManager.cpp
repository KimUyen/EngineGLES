#include "InputManager.h"
#include "CameraManager.h"
#include "Log.h"
float scale = 0.1f;
bool InputManager::m_isOnTouch = false;
float InputManager::m_distanceMove = 0.0f;
Point2D InputManager::m_touchStart = Point2D(-1.0f, -1.0f);
Point2D InputManager::m_touchEnd = Point2D(-1.0f, -1.0f);

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}


void InputManager::Keyboard(unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 37:
		CameraManager::GetCurrentCamera()->Move(DirectMove::DM_LEFT, 0.1f * scale, 2.0f);
		break;
	case 39:
		CameraManager::GetCurrentCamera()->Move(DirectMove::DM_RIGHT, 0.1f * scale, 2.0f);
		break;
	case 38:
		CameraManager::GetCurrentCamera()->Move(DirectMove::DM_UP, 0.1f * scale, 2.0f);
		break;
	case 40:
		CameraManager::GetCurrentCamera()->Move(DirectMove::DM_DOWN, 0.1f * scale, 2.0f);
		break;
	case 'B':
		CameraManager::GetCurrentCamera()->Move(DirectMove::DM_BACKWARD, 0.1f * scale, 2.0f);
		break;
	case 'F':
		CameraManager::GetCurrentCamera()->Move(DirectMove::DM_FORWARD, 0.1f * scale, 2.0f);
		break;


	case 'A':
		CameraManager::GetCurrentCamera()->Rotate(DirectRotate::DR_LEFTaroundY, glm::radians(5.0f) * scale);
		break;
	case 'D':
		CameraManager::GetCurrentCamera()->Rotate(DirectRotate::DR_RIGHTaroundY, glm::radians(5.0f) * scale);
		break;
	case 'S':
		CameraManager::GetCurrentCamera()->Rotate(DirectRotate::DR_DOWNaroundX, glm::radians(5.0f) * scale);
		break;
	case 'W':
		CameraManager::GetCurrentCamera()->Rotate(DirectRotate::DR_UParoundX, glm::radians(5.0f) * scale);
		break;

	case 'Q':
		CameraManager::GetCurrentCamera()->Rotate(DirectRotate::DR_LEFTaroundZ, glm::radians(5.0f) * scale);
		break;
	case 'E':
		CameraManager::GetCurrentCamera()->Rotate(DirectRotate::DR_RIGHTaroundZ, glm::radians(5.0f) * scale);
		break;
	default:
		break;
	}
}

void InputManager::Touch(TOUCH type, int x, int y)
{
	switch (type)
	{
	case TOUCH::DOWN:
	{
		m_isOnTouch = true;
		m_touchStart = Point2D(x, y);
		LOGI("InputManager", "X ===== %d\n", x);
		LOGI("InputManager", "Y ===== %d\n", y);
	}
	break;
	case TOUCH::UP:
	{
		m_isOnTouch = false;
		m_touchEnd = Point2D(x, y);
	}
	break;
	case TOUCH::MOVE:
	{
		m_touchEnd = Point2D(x, y);
		m_distanceMove = m_touchStart.CalDistanceTo(m_touchEnd);

		if (m_isOnTouch)
		{
			LOGI("InputManager", "IS ON MOVE %f\n", m_distanceMove);
			float angle = 0.45f * m_distanceMove;
			CameraManager::GetCurrentCamera()->RotateAroundObject(DirectRotate::DR_RIGHTaroundY, glm::radians(angle));
		}
	}
	break;

	default:
		break;
	}

}
