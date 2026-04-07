#pragma once
#include "stdafx.h"

class Window {
private :
	int width;
	int height;

	std::unique_ptr<HWND> hWnd;
	HINSTANCE hInstance;
	int nCmdShow;
public :
	Window() = delete;
	Window(HINSTANCE hInstance, int nCmdShow, const int width, const int height);
	~Window();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT InitWindow();
	HRESULT FloatWindow();
};