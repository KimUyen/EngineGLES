#include "Application.h"
std::vector<Object*> Application::_objects = std::vector<Object*>();
void Application::Initialize()
{
	Camera * camera;
	camera = new Camera(glm::vec3(0.0, 1.0, 2.0), glm::vec3(0.0, 0.0, 1.0f), glm::vec3(0.0, 1.0, 0.0), 45.0f, 800.0f / 600.0f, 0.001f, 100.f);
	CameraManager::AddCamera(camera);

	_objects = ResourceManager::LoadFrom("ResourceManager.txt");
}

void Application::Update(float time)
{
	//u_time += deltaTime;
	glm::vec4 ambLight = { 0.3f, 0.3f, 0.3f, 1.0f };
	glm::vec4 diffLight = { 0.9f, 0.5f, 0.5f, 1.0f };
	glm::vec4 specLight = { 0.6f, 0.6f, 0.6f, 1.0f };

	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->SetValueForUniform1F("u_weight", 0.3f);
		_objects[i]->SetValueForUniform3FV("u_lightPos", (GLfloat*)&glm::vec3(0.0f, 100.0f, 100.0f));
		_objects[i]->SetValueForUniform3FV("u_eyePos", (GLfloat*)&CameraManager::GetCurrentCamera()->GetPosCamera());

		_objects[i]->SetValueForUniform1F("u_Time", time);
		_objects[i]->SetValueForUniform1F("dMax", 1.0f);

		_objects[i]->SetValueForUniform4FV("u_ambLight", (GLfloat*)&ambLight);
		_objects[i]->SetValueForUniform4FV("u_diffLight", (GLfloat*)&diffLight);
		_objects[i]->SetValueForUniform4FV("u_specLight", (GLfloat*)&specLight);
	}
	//objList[0]->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
}

Application::~Application()
{
}
