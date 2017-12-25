#pragma once
#include "Object.h"
#include <vector>
using namespace std;

class ResourceManager
{
private:
	ResourceManager() {}
	~ResourceManager();
	static ResourceManager * m_instance;

public:
	
	static vector<Object *> LoadFrom(char * path);
};