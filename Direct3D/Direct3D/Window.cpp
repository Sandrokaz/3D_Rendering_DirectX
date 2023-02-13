#include "Window.h"
#include "resource.h"

INT Window::init(HINSTANCE hInstance, UINT width, UINT height)
{
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpszClassName = TEXT("Direct3D 11");
	wc.lpfnWndProc = WindowProc;

	if (RegisterClass(&wc) == 0) return 10;

	UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT wr = { (screenWidth - width) / 2, (screenHeight - height) / 2, (screenWidth + width) / 2, (screenHeight + height) / 2 };
	DWORD style = WS_OVERLAPPEDWINDOW;

	IsLoaded = TRUE;
	_hWnd = CreateWindow(wc.lpszClassName, wc.lpszClassName, style, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hInstance, nullptr);

	//CheckNull(_hWnd, 12);

	ShowWindow(_hWnd, SW_SHOW);
	SetFocus(_hWnd);


	return 0;
}

BOOL Window::run()
{
	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message != WM_QUIT;
	
}

void Window::deInit()
{
	IsLoaded = FALSE;
	DestroyWindow(_hWnd);
}

//void Window::MenuHandler(HWND hWnd) 
//{
//	HMENU hMenu = CreateMenu();
//	HMENU shapeMenu = CreateMenu();
//	HMENU materialMenu = CreateMenu();
//
//
//
//	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)shapeMenu, TEXT("&Shapes"));
//	// Adding first Menu Items	
//	AppendMenu(shapeMenu, MF_STRING, 0, TEXT("Cube"));
//	AppendMenu(shapeMenu, MF_STRING, 0, TEXT("Tetrahedron"));
//	AppendMenu(shapeMenu, MF_STRING, 0, TEXT("Pentagonal Prism"));
//	AppendMenu(shapeMenu, MF_SEPARATOR, 0, NULL);						
//	AppendMenu(shapeMenu, MF_STRING, 0, TEXT("Quit"));
//
//	SetMenu(hWnd, hMenu);
//
//
//}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
		//MenuHandler(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
