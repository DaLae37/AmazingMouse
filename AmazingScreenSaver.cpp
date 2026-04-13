#include "stdafx.h"
#include "AmazingScreenSaver.h"

AmazingScreenSaver::AmazingScreenSaver(HINSTANCE hInstance, int nCmdShow) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;

	timer = 0.0;
	InitDeltaTime();
}

AmazingScreenSaver::~AmazingScreenSaver() {

}

HRESULT AmazingScreenSaver::InitApplication() {
	window = std::make_unique<Window>(hInstance, nCmdShow, 300, 200);

	// Init WindowsAPI
	if (window->InitWindow() != S_OK) {
		std::wstring message = L"Init Window Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}
	if (window->FloatWindow() != S_OK) {
		std::wstring message = L"Float Window Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	return S_OK;
}

int AmazingScreenSaver::DoMainLoop() {
	MSG Message = { 0 };

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {
			InputManagerInstance->UpdateKeyState();
			if (InputManagerInstance->GetKeyState(VK_NUMLOCK) == KEY_DOWN) {
				window->Deactivate();
			}
			ProcessAutoMouse(getDeltaTime());
		}
	}
	return static_cast<int>(Message.wParam);
}

void AmazingScreenSaver::ProcessAutoMouse(double detaTime) {
	if (window->getIsActivate()) {
		timer += detaTime;
		if (timer >= window->getIntervalSeconds()) {
			POINT pos = InputManagerInstance->GetMousePosition();
			if (GetCursorPos(&pos)) {
				if (window->getIsRandomMode()) {
					// 랜덤 설정
					static std::random_device rd;
					static std::mt19937 gen(rd());
					std::uniform_int_distribution<int> dis(-50, 50); // -50 ~ 50px 사이 랜덤

					int nextX = pos.x + dis(gen);
					int nextY = pos.y + dis(gen);

					// 듀얼모니터 고려
					int screenLeft = GetSystemMetrics(SM_XVIRTUALSCREEN);
					int screenTop = GetSystemMetrics(SM_YVIRTUALSCREEN);
					int screenRight = screenLeft + GetSystemMetrics(SM_CXVIRTUALSCREEN);
					int screenButtom = screenTop + GetSystemMetrics(SM_CYVIRTUALSCREEN);

					if (nextX <= screenLeft || nextY <= screenTop || nextX >= screenRight - 1 || nextY >= screenButtom - 1) {
						// 메인모니터 센터로 보내기
						nextX = GetSystemMetrics(SM_CXSCREEN) / 2;
						nextY = GetSystemMetrics(SM_CYSCREEN) / 2;
					}

					SetCursorPos(nextX, nextY);
				}
				else {
					// 고정 모드: 왼쪽으로 1px 이동 후, 원래 자리로 복귀
					SetCursorPos(pos.x - 1, pos.y);
					SetCursorPos(pos.x, pos.y);
				}
			}
			timer = 0.0;
		}
	}
	else {
		timer = 0.0;
	}
}

void AmazingScreenSaver::InitDeltaTime() {
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&frequency);
}

double AmazingScreenSaver::getDeltaTime() {
	QueryPerformanceCounter(&currentInterval);

	LONGLONG interval = (currentInterval.QuadPart - beforeInterval.QuadPart);
	double deltaTime = 0;
	if (frequency.QuadPart > 0) {
		deltaTime = static_cast<double>(interval) / static_cast<double>(frequency.QuadPart);
	}
	else {
		deltaTime = 0;
	}
	beforeInterval = currentInterval;

	return deltaTime;
}