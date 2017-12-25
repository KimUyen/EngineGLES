#pragma once
class InputManager
{
public:
	static void Keyboard(unsigned char key, bool bIsPressed);
	static void Touch();
	InputManager();
	~InputManager();
};

