#include "InputManager.h"



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
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_LEFT, 0.1f * scale, 2.0f);
		break;
	case 39:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_RIGHT, 0.1f * scale, 2.0f);
		break;
	case 38:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_UP, 0.1f * scale, 2.0f);
		break;
	case 40:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_DOWN, 0.1f * scale, 2.0f);
		break;
	case 'B':
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_BACKWARD, 0.1f * scale, 2.0f);
		break;
	case 'F':
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_FORWARD, 0.1f * scale, 2.0f);
		break;


	case 'A':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_LEFTaroundY, glm::radians(5.0f) * scale);
		break;
	case 'D':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_RIGHTaroundY, glm::radians(5.0f) * scale);
		break;
	case 'S':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_DOWNaroundX, glm::radians(5.0f) * scale);
		break;
	case 'W':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_UParoundX, glm::radians(5.0f) * scale);
		break;

	case 'Q':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_LEFTaroundZ, glm::radians(5.0f) * scale);
		break;
	case 'E':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_RIGHTaroundZ, glm::radians(5.0f) * scale);
		break;
	default:
		break;
	}
}

void InputManager::Touch()
{
}
