#include "stdafx.h"
#include "AmazingMouse.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	std::unique_ptr<AmazingMouse> amazingMouse = std::make_unique<AmazingMouse>(hInstance, nCmdShow);

	if (amazingMouse->InitApplication() == S_OK) {
		return amazingMouse->DoMainLoop();
	}
	else {
		return 0;
	}
}