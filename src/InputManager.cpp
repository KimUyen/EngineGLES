#include "InputManager.h"
#include "CameraManager.h"
float scale = 0.1f;
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

void InputManager::Touch()
{
}
