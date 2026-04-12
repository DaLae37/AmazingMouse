#pragma once
#include "stdafx.h"

class Window {
private:
	int width;
	int height;

	int nCmdShow;
	int intervalSeconds;
	bool isActivate;

	HINSTANCE hInstance;
	WNDCLASSEX wndClass;
	NOTIFYICONDATA notifyData;

	HFONT hFont;
	HWND hWnd, hEditInterval, hTextInterval, hCheckRandom, hButtonStart, hTextWarning;

public:
	Window() = delete;
	Window(HINSTANCE hInstance, int nCmdShow, const int width, const int height);
	~Window();

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT InitWindow();
	HRESULT InitUI();
	HRESULT InitTray();
	HRESULT FloatWindow();

	void Deactivate();

	bool getIsActivate() const;
	bool getIsRandomMode() const;
	int getIntervalSeconds() const;
};