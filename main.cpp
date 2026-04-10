#include "stdafx.h"
#include "AmazingScreenSaver.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	std::unique_ptr<AmazingScreenSaver> amazingMouse = std::make_unique<AmazingScreenSaver>(hInstance, nCmdShow);

	if (amazingMouse->InitApplication() == S_OK) {
		return amazingMouse->DoMainLoop();
	}
	else {
		return 0;
	}
}