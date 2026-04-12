#pragma once
#include "stdafx.h"
#include "Window.h"
#include "InputManager.h"

class AmazingScreenSaver {
private :
	HINSTANCE hInstance;
	int nCmdShow;

	std::unique_ptr<Window> window = nullptr;

	LARGE_INTEGER beforeInterval, currentInterval, frequency;

	double timer;
public :
	AmazingScreenSaver() = delete;
	AmazingScreenSaver(HINSTANCE hInstance, int nCmdShow);
	~AmazingScreenSaver();

	HRESULT InitApplication();
	int DoMainLoop();

	void ProcessAutoMouse(double dt);

	void InitDeltaTime();
	double getDeltaTime();
};