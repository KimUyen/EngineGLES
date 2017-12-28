#include "ResourceManager.h"
#include <stdio.h>
#include "Object.h"
#include <vector>

//ResourceManager * ResourceManager::m_instance = nullptr;
//
//ResourceManager * ResourceManager::GetInstance()
//{
//	if (m_instance == nullptr)
//	{
//		m_instance = new ResourceManager();
//	}
//
//	return m_instance;
//}

vector<Object*> ResourceManager::LoadFrom(char * path)
{
	vector<Object*> ListObj;
	int numObjs;
	////////
	// load NFG file and put it into buffer
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		printf("Load ResourceManager failed: %s", path);
		return ListObj;
	}

	// Read NumObjs:
	fscanf(f, "NumObjs: %d\r\n", &numObjs);
	
	int index = 0;
	while (index < numObjs)
	{
		int typeTex;
		float scale;
		glm::vec3 trans;
		char pathModel[30];
		char VShader[30];
		char FShader[30];

		int numPath;
		char** pathTex;
		int numTex;
		char ** varTex;

		fscanf(f, "TypeTex: %d\r\n", &typeTex);
		// shader path
		fscanf(f, "VShader: %s FShader: %s\r\n", VShader, FShader);
		// model path
		fscanf(f, "Model: %s\r\n", pathModel);
		// Scale
		fscanf(f, "Scale: %f\r\n", &scale);
		// Trans
		fscanf(f, "Trans: %f %f %f\r\n", &trans.x, &trans.y, &trans.z);
		// Numpath
		fscanf(f, "Numpath: %d\r\n", &numPath);

		// texture path
		int i = 0;
		pathTex = new char*[numPath];
		char strTemp[30];

		fscanf(f, "Texture:", strTemp);
		while (i < numPath)
		{
			fscanf(f, " %s", strTemp);
			pathTex[i] = new char[strlen(strTemp)];
			strcpy(pathTex[i], strTemp);
			i++;
		}

		fscanf(f, "\r\n");

		// Numtex
		fscanf(f, "NumTex: %d\r\n", &numTex);

		// var name
		i = 0;
		varTex = new char*[numTex];

		fscanf(f, "VarName:", strTemp);
		while (i < numTex)
		{
			fscanf(f, " %s", strTemp);
			varTex[i] = new char[strlen(strTemp)];
			strcpy(varTex[i], strTemp);
			i++;
		}

		fscanf(f, "\r\n");

		// Add object to list
		//Object * newObj = new Object(id, pathShader, pathModel, numTex, varTex, numPath, pathTex);


		Object * obj = new Object(index);
		obj->LoadModel(pathModel);
		obj->LoadTexture(typeTex, varTex, pathTex, numTex);
		obj->CreateProgram(VShader, FShader);
		obj->SetScale(glm::vec3(scale, scale, scale));
		obj->SetTranslate(trans);
		ListObj.push_back(obj);
		index++;
	}

	return ListObj;
}

ResourceManager::~ResourceManager()
{
}
