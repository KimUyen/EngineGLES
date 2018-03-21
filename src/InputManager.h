#pragma once
#include "ogles_sys.h"
#include <cmath>
struct Point2D
{
	Point2D(int x, int y)
	{
		m_x = x;
		m_y = y;
	}
	float CalDistanceTo(Point2D another)
	{
		int minus_x = another.m_x - this->m_x;
		int minus_y = another.m_y - this->m_y;
		return sqrt(minus_x * minus_x + minus_y * minus_y);
	}
	int m_x;
	int m_y;
};

class InputManager
{
private:
	static bool m_isOnTouch;
	static float m_distanceMove;
	static Point2D m_touchStart;
	static Point2D m_touchEnd;
	InputManager();
public:
	static void Keyboard(unsigned char key, bool bIsPressed);
	static void Touch(TOUCH type, int x, int y);

	~InputManager();
};

