#include "CameraManager.h"

CameraManager * CameraManager::m_instance = nullptr;

CameraManager::~CameraManager()
{
}

CameraManager::CameraManager()
{
}

CameraManager * CameraManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CameraManager();
	}
	
	return m_instance;
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
