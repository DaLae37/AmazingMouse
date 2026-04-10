#include "stdafx.h"
#include "AmazingScreenSaver.h"

AmazingScreenSaver::AmazingScreenSaver(HINSTANCE hInstance, int nCmdShow) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
}

AmazingScreenSaver::~AmazingScreenSaver() {

}

HRESULT AmazingScreenSaver::InitApplication() {
	window = std::make_unique<Window>(hInstance, nCmdShow, 500, 500);

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
	MSG Message = { 0, };

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {

		}
	}
	return static_cast<int>(Message.wParam);
}
