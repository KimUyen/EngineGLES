#include "CameraManager.h"

CameraManager * CameraManager::m_instance = nullptr;

CameraManager::~CameraManager()
{
}

CameraManager::CameraManager()
{
}

Camera * CameraManager::GetCurrentCamera()
{
	if (m_listCamera.size() != 0)
	{
		return m_listCamera.top();
	}

	return nullptr;
}

void CameraManager::AddCamera(Camera * cam)
{
	m_listCamera.push(cam);
}
