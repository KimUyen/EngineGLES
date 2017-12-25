#pragma once
class InputManager
{
public:
	void Keyboard(unsigned char key, bool bIsPressed);
	void Touch();
	InputManager();
	~InputManager();
};

