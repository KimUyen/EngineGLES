#pragma once
#include <stack>
#include "Camera.h"

class CameraManager
{
private:
	std::stack<Camera *> m_listCamera;
	static CameraManager * m_instance;
	CameraManager();
	~CameraManager();

public:
	static CameraManager * GetInstance();
	Camera* GetCurrentCamera();
	void AddCamera(Camera * cam);
};