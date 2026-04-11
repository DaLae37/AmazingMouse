#pragma once
#include "stdafx.h"
#include "Window.h"

class AmazingScreenSaver {
private :
	HINSTANCE hInstance;
	int nCmdShow;

	std::unique_ptr<Window> window = nullptr;

	LARGE_INTEGER beforeInterval, currentInterval, frequency;
public :
	AmazingScreenSaver() = delete;
	AmazingScreenSaver(HINSTANCE hInstance, int nCmdShow);
	~AmazingScreenSaver();

	HRESULT InitApplication();
	int DoMainLoop();

	void InitDeltaTime();
	double getDeltaTime();
};