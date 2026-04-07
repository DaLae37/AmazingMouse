#include "stdafx.h"
#include "Window.h"

Window::Window(HINSTANCE hInstance, int nCmdShow, const int width, const int height) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;

	this->width = width;
	this->height = height;
}

Window::~Window() {

}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE: // Click Exit Button
		if (MessageBoxEx(hWnd, L"Exit Program?", PROGRAM_NAME, MB_OKCANCEL, NULL) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HRESULT Window::InitWindow() {
	WNDCLASSEX wndClass = WNDCLASSEX();

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // Re-Draw Entire Window If Size Changed
	wndClass.lpfnWndProc = WndProc; // Window::WndProc
	wndClass.cbClsExtra = 0; // No Additional Memory Required
	wndClass.cbWndExtra = 0; // No Additional Memory Required
	wndClass.hInstance = this->hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1); // Using Default Window Background Color
	wndClass.lpszMenuName = nullptr; // Set Resource Name
	wndClass.lpszClassName = PROGRAM_NAME;

	RegisterClassEx(&wndClass);

	if (GetLastError() != 0) {
		return E_FAIL;
	}
	else {
		return S_OK;
	}
}

HRESULT Window::FloatWindow() {
	this->hWnd = std::make_unique<HWND>(CreateWindowEx(WS_EX_APPWINDOW, // Extension Style
		PROGRAM_NAME, PROGRAM_NAME, WS_OVERLAPPEDWINDOW, // Class Name, Title, Window Style
		CW_USEDEFAULT, CW_USEDEFAULT, // Window Position
		this->width, this->height,
		nullptr, nullptr, this->hInstance, nullptr)); // Parent Handle, Menu Handle, Application Handle, Additional Data

	ShowWindow(*this->hWnd.get(), 0);

	if (GetLastError() != 0) {
		return E_FAIL;
	}
	else {
		return S_OK;
	}
}