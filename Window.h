#pragma once
#include "stdafx.h"
#include "InputManager.h"

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
	HMENU hMenuTray;
	HWND hWnd, hEditInterval, hTextInterval, hCheckRandom, hButtonStart, hTextWarning;

	enum class WINDOW_UI {
		EDIT_INTERVAL = 2001,
		CHECK_RANDOM,
		BUTTON_START
	};

	enum class TRAY_MENU {
		ACTIVATE = 3001,
		SETTING,
		EXIT
	};

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

	void Hide();
	void Activate();
	void Deactivate();

	bool getIsActivate() const;
	bool getIsRandomMode() const;
	int getIntervalSeconds() const;
};