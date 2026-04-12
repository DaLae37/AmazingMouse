#pragma once
#define PROGRAM_NAME L"AmazingScreenSaver"
#define WM_APP 0x8000
#define WM_APP_TRAYMSG (WM_APP + 1)

//Macro Define
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_ON 3

#define SAFE_RELEASE(p) {if(p) {p->Release();} (p) = nullptr;}
#define SAFE_DELETE(p) {if(p) {delete (p);} (p) = nullptr;}
#define SAFE_DELETE_ARRAY(p) {if(p){delete [](p);} (p) = nullptr;}
#define SAFE_SMART_DELETE(p) {if(p) {p.reset();} (p) = nullptr;}
#define SAFE_COMPTR_DELETE(p) {if(p) {p.Reset();} (p) = nullptr;}


// Windows 헤더 파일
#include <windows.h>
#include <shellapi.h>

#include <random>
#include <memory>
#include <string>

// 리소스 헤더 파일
#include "Resources/resource.h"