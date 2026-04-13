# AmazingScreenSaver

윈도우 절전 모드, 화면 잠금, 그리고 메신저 등에서 '**자리 비움**'으로 변경되는 것을 방지하기 위해 만들어진 유틸리티

![Windows](https://img.shields.io/badge/OS-Windows_10%20%7C%2011-blue?logo=windows)
![C++](https://img.shields.io/badge/Language-C++-00599C?logo=c%2B%2B)
![Win32 API](https://img.shields.io/badge/Framework-Win32_API-lightgrey)

## 다운로드

Standalone : [실행파일 다운로드 (GitHub Releases)](https://github.com/DaLae37/AmazingScreenSaver/releases/latest)
> **주의사항** :**'Windows PC 보호(SmartScreen)'** 경고창이 나타날 수 있음, `[추가 정보]` -> `[실행]`을 클릭해 실행

## 주요 기능

* **시스템 제어**
  * **윈도우 API** 작동 중일 때 `SetThreadExecutionState`를 이용해 화면 꺼짐 및 PC 절전 모드 진입 차단

* **마우스 제어** - 마우스 신호(`SendInput`)를 이용해 제어
  * **고정 모드 (기본):** 왼쪽으로 1px 움직였다가 원복
  * **랜덤 모드:** -50px ~ 50px 범위의 임의 값을 이동

## 사용 방법

1. 다운로드한 `AmazingScreenSaver.exe` 파일을 실행
2. 원하는 이동 간격을 **초 단위**로 입력 (기본값 : 60초)
3. 동작 모드(랜덤 또는 고정)를 선택
4. **`시작 (트레이로)`** 버튼을 누르면 트레이 아이콘으로 작동
5. **프로그램 제어 방법:**
   * **트레이 아이콘 우클릭:** 팝업 메뉴를 통해 `상태 전환(ON/OFF)`, `설정 열기`, `종료` 실행
   * **트레이 아이콘 더블 클릭:** 정지하고 설정 창을 띄움
   * **단축키 (NumLock):** `NumLock` 키를 누르면 정지하고 설정 창을 띄움
   * **대기** 사용자가 마우스를 움직이는 동안에는 타이머가 초기화되어 동작하지 않음

## 빌드 정보

이 프로젝트는 다음과 같은 환경에서 빌드되었음
* **IDE:** Visual Studio 2026
* **C++:** ISO C++20
* **Window SDK:** Windows 10.0 SDK
* **플랫폼 도구 집합:** v145 for Microsoft C++ Build Tools

## 라이선스 (License)

[MIT License](LICENSE)
