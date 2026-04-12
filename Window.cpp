#include "stdafx.h"
#include "Window.h"

Window::Window(HINSTANCE hInstance, int nCmdShow, const int width, const int height) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
	this->width = width;
	this->height = height;
	this->isActivate = false;
	this->intervalSeconds = 60;
}

Window::~Window() {
	if (hFont != nullptr) {
		DeleteObject(hFont);
	}
}

LRESULT CALLBACK Window::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* pThis = nullptr;

	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else {
		pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pThis != nullptr) {
		return pThis->WndProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
	case WM_CTLCOLORSTATIC: {
		HDC hdcStatic = reinterpret_cast<HDC>(wParam);
		HWND hStatic = reinterpret_cast<HWND>(lParam);

		SetBkMode(hdcStatic, TRANSPARENT); // 배경 투명하게

		// 경고 문구일 경우 빨간색
		if (hStatic == hTextWarning) {
			SetTextColor(hdcStatic, RGB(255, 0, 0)); // 빨간색
		}
		else {
			SetTextColor(hdcStatic, RGB(0, 0, 0));   // 나머지는 검은색
		}

		return reinterpret_cast<LRESULT>(GetSysColorBrush(COLOR_WINDOW));
	}
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED) {
			lstrcpy(notifyData.szTip, L"더블 클릭 시 창이 열립니다");
			Shell_NotifyIcon(NIM_ADD, &notifyData);
			ShowWindow(hWnd, SW_HIDE);
		}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 2003) {
			wchar_t buf[10];
			GetWindowText(hEditInterval, buf, 10);
			int seconds = _wtoi(buf);

			if (seconds <= 0) {
				seconds = 1;
			}

			intervalSeconds = seconds;
			isActivate = true;

			lstrcpy(notifyData.szTip, L"마우스 자동 이동 중");
			Shell_NotifyIcon(NIM_ADD, &notifyData);
			ShowWindow(hWnd, SW_HIDE);
		}
		break;
	case WM_APP_TRAYMSG:
		if (lParam == WM_LBUTTONDBLCLK) {
			isActivate = false;
			Shell_NotifyIcon(NIM_DELETE, &notifyData);
			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		Shell_NotifyIcon(NIM_DELETE, &notifyData);
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
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
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = Window::StaticWndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = this->hInstance;
	wndClass.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hIconSm = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = PROGRAM_NAME;

	if (RegisterClassEx(&wndClass) == 0) {
		return E_FAIL;
	}

	// 폭 300, 높이 250으로 생성
	this->hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		PROGRAM_NAME, PROGRAM_NAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		this->width, this->height,
		nullptr, nullptr, this->hInstance,
		this);

	if (this->hWnd == NULL) {
		return E_FAIL;
	}

	InitUI();
	InitTray();

	return S_OK;
}

HRESULT Window::InitUI() {
	hFont = CreateFont(
		16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

	hTextWarning = CreateWindow(L"STATIC", L"※ 작동 중 NumLock을 누르면 작동이 해제됩니다", WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 15, 284, 20, hWnd, nullptr, hInstance, nullptr);

	hTextInterval = CreateWindow(L"STATIC", L"간격 (초):", WS_CHILD | WS_VISIBLE | SS_RIGHT,
		75, 55, 70, 20, hWnd, nullptr, hInstance, nullptr);

	hEditInterval = CreateWindow(L"EDIT", L"60", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_CENTER,
		150, 52, 60, 25, hWnd, reinterpret_cast<HMENU>(2001), hInstance, nullptr);

	hCheckRandom = CreateWindow(L"BUTTON", L"랜덤 이동 활성화", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		72, 95, 140, 25, hWnd, reinterpret_cast<HMENU>(2002), hInstance, nullptr);

	hButtonStart = CreateWindow(L"BUTTON", L"시작 (트레이로)", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		52, 140, 180, 40, hWnd, reinterpret_cast<HMENU>(2003), hInstance, nullptr);

	SendMessage(hTextInterval, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hEditInterval, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hCheckRandom, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hButtonStart, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hTextWarning, WM_SETFONT, (WPARAM)hFont, TRUE);

	return S_OK;
}

HRESULT Window::InitTray() {
	notifyData = NOTIFYICONDATA();
	notifyData.cbSize = sizeof(NOTIFYICONDATA);
	notifyData.hWnd = hWnd;
	notifyData.uID = IDI_ICON1;
	notifyData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifyData.uCallbackMessage = WM_APP_TRAYMSG;
	notifyData.hIcon = LoadIcon(this->hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return S_OK;
}

HRESULT Window::FloatWindow() {
	ShowWindow(this->hWnd, nCmdShow);
	return S_OK;
}

bool Window::getIsActivate() const {
	return isActivate;
}

bool Window::getIsRandomMode() const {
	return SendMessage(hCheckRandom, BM_GETCHECK, 0, 0) == BST_CHECKED;
}

int Window::getIntervalSeconds() const {
	return this->intervalSeconds;
}

void Window::Deactivate() {
	if (this->isActivate) {
		this->isActivate = false;

		// 트레이 아이콘 지우기
		Shell_NotifyIcon(NIM_DELETE, &notifyData);

		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
	}
}