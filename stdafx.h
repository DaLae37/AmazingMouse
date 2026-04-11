#pragma once
#define PROGRAM_NAME L"Amazing Screen Saver"
#define WM_APP 0x8000
#define WM_APP_TRAYMSG (WM_APP + 1)

// Windows 헤더 파일
#include <windows.h>
#include <shellapi.h>

#include <stdexcept>
#include <memory>
#include <string>

// 리소스 헤더 파일
#include "Resources/resource.h"