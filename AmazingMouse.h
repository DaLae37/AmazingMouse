#pragma once
#include "stdafx.h"
#include "Window.h"

class AmazingMouse {
private :
	HINSTANCE hInstance;
	int nCmdShow;

	std::unique_ptr<Window> window;
public :
	AmazingMouse() = delete;
	AmazingMouse(HINSTANCE hInstance, int nCmdShow);
	~AmazingMouse();

	HRESULT InitApplication();
	int DoMainLoop();
};