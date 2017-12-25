#include "CameraManager.h"
std::vector<Camera *> CameraManager::m_listCamera = std::vector<Camera *>();
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
		return m_listCamera.back();
	}

	return nullptr;
}

void CameraManager::AddCamera(Camera * cam)
{
	m_listCamera.push_back(cam);
}
