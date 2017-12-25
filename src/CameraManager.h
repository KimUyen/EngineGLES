#pragma once
#include <vector>
#include "Camera.h"

class CameraManager
{
private:
	static std::vector<Camera *> m_listCamera;
	CameraManager();
	~CameraManager();

public:
	static Camera* GetCurrentCamera();
	static void AddCamera(Camera * cam);
};