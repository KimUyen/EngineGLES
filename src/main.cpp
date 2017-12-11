#include "ogles_sys.h"
#include <stdio.h>
#include "glm.hpp"
#include "TGA.h"
#include "gtx\transform.hpp"
#include "Shader.h"
#include "Object.h"
#include <vector>
#include "ResourceManager.h"
#include "Camera.h"
#include "CameraManager.h"

std::vector <Object *> objList;

float scale = 0.1f;
float u_time = 0.0f;
float dMax = 0.1f;

void Init()
{
	Camera * camera;
	camera = new Camera(glm::vec3(0.0, 1.0, 2.0), glm::vec3(0.0, 0.0, 1.0f), glm::vec3(0.0, 1.0, 0.0), 45.0f, 800.0f / 600.0f, 0.001f, 100.f);
	CameraManager::GetInstance()->AddCamera(camera);

	objList = ResourceManager::GetInstance()->LoadFrom("ResourceManager.txt");

}

void Render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (int i = 0; i < objList.size(); i++)
	{
		objList[i]->Render();
	}
}

void Update(float deltaTime)
{
	u_time += deltaTime;
	glm::vec4 ambLight = { 0.3f, 0.3f, 0.3f, 1.0f };
	glm::vec4 diffLight = { 0.9f, 0.5f, 0.5f, 1.0f };
	glm::vec4 specLight = { 0.6f, 0.6f, 0.6f, 1.0f };

	for (int i = 0; i < objList.size(); i++)
	{
		objList[i]->SetValueForUniform1F("u_weight", 0.3f);
		objList[i]->SetValueForUniform3FV("u_lightPos", (GLfloat*)&glm::vec3(0.0f, 100.0f, 100.0f));
		objList[i]->SetValueForUniform3FV("u_eyePos", (GLfloat*)&CameraManager::GetInstance()->GetCurrentCamera()->GetPosCamera());

		objList[i]->SetValueForUniform1F("u_Time", u_time);
		objList[i]->SetValueForUniform1F("dMax", dMax);

		objList[i]->SetValueForUniform4FV("u_ambLight", (GLfloat*)&ambLight);
		objList[i]->SetValueForUniform4FV("u_diffLight", (GLfloat*)&diffLight);
		objList[i]->SetValueForUniform4FV("u_specLight", (GLfloat*)&specLight);
	}
	//objList[0]->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
}

void Key(unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 37:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_LEFT, 0.1f * scale, 2.0f);
		break;
	case 39:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_RIGHT, 0.1f * scale, 2.0f);
		break;
	case 38:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_UP, 0.1f * scale, 2.0f);
		break;
	case 40:
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_DOWN, 0.1f * scale, 2.0f);
		break;
	case 'B':
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_BACKWARD, 0.1f * scale, 2.0f);
		break;
	case 'F':
		CameraManager::GetInstance()->GetCurrentCamera()->Move(DirectMove::DM_FORWARD, 0.1f * scale, 2.0f);
		break;


	case 'A':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_LEFTaroundY, glm::radians(5.0f) * scale);
		break;
	case 'D':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_RIGHTaroundY, glm::radians(5.0f) * scale);
		break;
	case 'S':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_DOWNaroundX, glm::radians(5.0f) * scale);
		break;
	case 'W':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_UParoundX, glm::radians(5.0f) * scale);
		break;

	case 'Q':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_LEFTaroundZ, glm::radians(5.0f) * scale);
		break;
	case 'E':
		CameraManager::GetInstance()->GetCurrentCamera()->Rotate(DirectRotate::DR_RIGHTaroundZ, glm::radians(5.0f) * scale);
		break;
	default:
		break;
	}
}

void main()
{
	SysContext oglSysCtx;
	ZeroMemory(&oglSysCtx, sizeof(SysContext));

	sysInit(&oglSysCtx, 800, 600);

	Init();

	sysRegisterKeyFunc(&oglSysCtx, Key);
	sysRegisterRenderFunc(&oglSysCtx, Render);
	sysRegisterUpdateFunc(&oglSysCtx, Update);

	sysMainLoop(&oglSysCtx);
}