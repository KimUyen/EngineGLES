#pragma once
#include <stack>
#include "Camera.h"

class CameraManager
{
private:
	static std::stack<Camera *> m_listCamera;
	static CameraManager * m_instance;
	CameraManager();
	~CameraManager();

public:
	static Camera* GetCurrentCamera();
	static void AddCamera(Camera * cam);
};