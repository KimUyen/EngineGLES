#pragma once
#include <vector>
#include "Object.h"
#include "CameraManager.h"
#include "ResourceManager.h"
#include "FileSystem.h"

class Application
{
private:
	std::vector<Object*> _objects;
public:
	void Initialize();
	void Update(long time);
	~Application();
};

