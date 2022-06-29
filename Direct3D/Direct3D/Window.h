#pragma once
#include <Windows.h>

class Window
{
public:
	INT Initialize(HINSTANCE hInstance, UINT width, UINT height);
	BOOL Run();
	void MenuHandler(HWND hWnd);
	void DeInitialize();

	BOOL IsLoaded = FALSE;
	HWND GetWindowHandle() { return _hWnd; }

private:
	HWND _hWnd = nullptr;
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);