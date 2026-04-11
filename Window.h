#pragma once
#include "stdafx.h"

class Window {
private :
	inline static NOTIFYICONDATA notifyData;

	int width;
	int height;

	HWND hWnd;
	WNDCLASSEX wndClass;

	HINSTANCE hInstance;
	int nCmdShow;
public :
	Window() = delete;
	Window(HINSTANCE hInstance, int nCmdShow, const int width, const int height);
	~Window();

	inline static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT InitWindow();
	HRESULT FloatWindow();
};