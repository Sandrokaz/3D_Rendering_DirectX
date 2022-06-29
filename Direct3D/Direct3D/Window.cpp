#include "Window.h"
#include "resource.h"

INT Window::Initialize(HINSTANCE hInstance, UINT width, UINT height)
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

BOOL Window::Run()
{
	static MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message != WM_QUIT;
	
}

void Window::DeInitialize()
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
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			/*	case IDM_MENUITEM1:
					MessageBeep(MB_ICONINFORMATION);
					break;*/

					// Object menu buttons
		case ID_3DOBJECTS_CUBE:
		//	DataExchange::shared_instance().Val = IDC_CUBE;
			break;
		case ID_3DOBJECTS_TETRAHEDRON:
			//DataExchange::shared_instance().Val = IDC_Tetrahedron;
			break;
		case ID_3DOBJECTS_PENTAGONALPRISM:
			//DataExchange::shared_instance().Val = IDC_PentagonalPrism;
			break;
		case ID_3DOBJECTS_LOADALL3OBJECTS:
			break;

			// MATERIAL OPTIONS
		case ID_PHONG_CEMENT:
		//	DataExchange::shared_instance().Val = IDC_PHONG;
			break;
		case ID_GLOSSY_CEMENT:
		//	DataExchange::shared_instance().Val = IDC_GLOSSY;
			break;
		case ID_MATT_CEMENT:
		//	DataExchange::shared_instance().Val = IDC_MATT;
			break;
		case ID_PHONG_COPPER:
		//	DataExchange::shared_instance().Val = IDC_POPCORN;
			break;
		case ID_GLOSSY_COPPER:
			//DataExchange::shared_instance().Val = IDC_CEMENT;
			break;
		case ID_MATT_COPPER:
			//DataExchange::shared_instance().Val = IDC_COPPER;
			break;
			
		case ID_PHONG_WOOD:
			//	DataExchange::shared_instance().Val = IDC_POPCORN;
			break;
		case ID_GLOSSY_WOOD:
			//DataExchange::shared_instance().Val = IDC_CEMENT;
			break;
		case ID_MATT_WOOD:
			//DataExchange::shared_instance().Val = IDC_COPPER;
			break;


			/*case IDC_CANCEL:
				DataExchange::shared_instance().Val = IDC_CANCEL;
				break;*/


				/*case IDM_MENUITEM2:
					MessageBeep(MB_ICONWARNING);
					break;*/
					/*	case IDM_FILE_QUIT:
							SendMessage(hWnd, WM_CLOSE, 0, 0);
							break;*/
		}
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
