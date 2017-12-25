#include "ogles_sys.h"
#include <stdio.h>
#include "glm.hpp"
#include "TGA.h"
#include "gtx\transform.hpp"
//#include "Shader.h"
#include "Object.h"
#include <vector>
#include "ResourceManager.h"
#include "Camera.h"
#include "CameraManager.h"
#include "FileSystem.h"
#include "Application.h"
#include "InputManager.h"
std::vector <Object *> objList;

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

//void Update(float deltaTime)
//{
//	u_time += deltaTime;
//	glm::vec4 ambLight = { 0.3f, 0.3f, 0.3f, 1.0f };
//	glm::vec4 diffLight = { 0.9f, 0.5f, 0.5f, 1.0f };
//	glm::vec4 specLight = { 0.6f, 0.6f, 0.6f, 1.0f };
//
//	for (int i = 0; i < objList.size(); i++)
//	{
//		objList[i]->SetValueForUniform1F("u_weight", 0.3f);
//		objList[i]->SetValueForUniform3FV("u_lightPos", (GLfloat*)&glm::vec3(0.0f, 100.0f, 100.0f));
//		objList[i]->SetValueForUniform3FV("u_eyePos", (GLfloat*)&CameraManager::GetInstance()->GetCurrentCamera()->GetPosCamera());
//
//		objList[i]->SetValueForUniform1F("u_Time", u_time);
//		objList[i]->SetValueForUniform1F("dMax", dMax);
//
//		objList[i]->SetValueForUniform4FV("u_ambLight", (GLfloat*)&ambLight);
//		objList[i]->SetValueForUniform4FV("u_diffLight", (GLfloat*)&diffLight);
//		objList[i]->SetValueForUniform4FV("u_specLight", (GLfloat*)&specLight);
//	}
//	//objList[0]->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
//}


void main()
{
	SysContext oglSysCtx;
	ZeroMemory(&oglSysCtx, sizeof(SysContext));

	sysInit(&oglSysCtx, 800, 600);

	Application::Initialize();

	sysRegisterKeyFunc(&oglSysCtx, InputManager::Keyboard);
	sysRegisterRenderFunc(&oglSysCtx, Render);
	sysRegisterUpdateFunc(&oglSysCtx, Application::Update);

	sysMainLoop(&oglSysCtx);
}