#pragma once
#include <Windows.h>

class Window
{
public:
	INT init(HINSTANCE hInstance, UINT width, UINT height);
	BOOL run();
	//void MenuHandler(HWND hWnd);
	void deInit();

	BOOL IsLoaded = FALSE;
	HWND GetWindowHandle() { return _hWnd; }

private:
	HWND _hWnd = nullptr;
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);