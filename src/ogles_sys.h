#pragma once

#include "EGL/egl.h"
#include "GLES2/gl2.h"
enum TOUCH
{
	MOVE,
	DOWN,
	UP
};

struct SysContext
{
	// Windows variables
	HWND				nativeWindow;
	HDC					deviceContext;

	// EGL variables
	EGLDisplay			eglDisplay;
	EGLConfig			eglConfig;
	EGLSurface			eglSurface;
	EGLContext			eglContext;

	// Callback funcs
	void (*renderFunc)	();
	void (*keyFunc)		(unsigned char, bool);
	void(*touchFunc)	(TOUCH, int x, int y);
	void (*updateFunc)	(float deltaTime);
};

void sysInit(SysContext* sysCtx, int screenW, int screenH);

void sysMainLoop(SysContext* sysCtx);

void sysRegisterRenderFunc(SysContext* sysCtx, void (*func)());
void sysRegisterUpdateFunc(SysContext* sysCtx, void (*func)(float));
void sysRegisterKeyFunc(SysContext* sysCtx, void (*func)(unsigned char, bool));
void sysRegisterTouchFunc(SysContext* sysCtx, void(*func)(TOUCH, int x, int y));

void sysCleanUp(SysContext* sysCtx);

void printSystemSpecs();

