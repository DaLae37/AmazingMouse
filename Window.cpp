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
	case WM_CREATE: {
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		RECT rect;
		GetWindowRect(hWnd, &rect);
		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		int x = (screenWidth - windowWidth) / 2;
		int y = (screenHeight - windowHeight) / 2;

		MoveWindow(hWnd, x, y, windowWidth, windowHeight, TRUE);
		break;
	}
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED) {
			Shell_NotifyIcon(NIM_ADD, &Window::notifyData);
			ShowWindow(hWnd, SW_HIDE);
		}
		break;

	case WM_APP_TRAYMSG:
		if (lParam == WM_LBUTTONDBLCLK) {
			Shell_NotifyIcon(NIM_DELETE, &Window::notifyData);
			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE: // Click Exit Button
		if (MessageBox(hWnd, L"종료하시겠습니까?", PROGRAM_NAME, MB_OKCANCEL) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HRESULT Window::InitWindow() {
	wndClass = WNDCLASSEX();
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // Re-Draw Entire Window If Size Changed
	wndClass.lpfnWndProc = WndProc; // Window::WndProc
	wndClass.cbClsExtra = 0; // No Additional Memory Required
	wndClass.cbWndExtra = 0; // No Additional Memory Required
	wndClass.hInstance = this->hInstance;
	wndClass.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hIconSm = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_ICON1));
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
	this->hWnd = CreateWindowEx(WS_EX_APPWINDOW, // Extension Style
		PROGRAM_NAME, PROGRAM_NAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Class Name, Title, Window Style
		CW_USEDEFAULT, CW_USEDEFAULT, // Window Position
		this->width, this->height,
		nullptr, nullptr, this->hInstance, nullptr); // Parent Handle, Menu Handle, Application Handle, Additional Data

	notifyData = NOTIFYICONDATA();
	notifyData.cbSize = sizeof(NOTIFYICONDATA);
	notifyData.hWnd = hWnd;
	notifyData.uID = IDI_ICON1;
	notifyData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifyData.uCallbackMessage = WM_APP_TRAYMSG;
	notifyData.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_ICON1));
	lstrcpy(notifyData.szTip, L"더블클릭하면 창이 열립니다.");

	ShowWindow(this->hWnd, nCmdShow);

	if (GetLastError() != 0) {
		return E_FAIL;
	}
	else {
		return S_OK;
	}
}