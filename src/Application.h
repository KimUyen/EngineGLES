#pragma once
#include <vector>
#include "Object.h"
#include "CameraManager.h"
#include "ResourceManager.h"
#include "FileSystem.h"

class Application
{
private:
	static std::vector<Object*> _objects;
public:
	static void Render();
	static void Initialize();
	static void Update(float time);
	~Application();
};

