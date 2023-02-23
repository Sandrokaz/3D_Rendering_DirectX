#include "MenuHandler.h"

INT Menu::init(HWND hWnd)
{
    _hMenu = CreateMenu();
    if (!_hMenu)
        return false;
    
    _hWnd = hWnd;

    SetMenu(_hWnd, _hMenu);
    addMenuItems();
    return true;
}

void Menu::update()
{
    // Handle any menu commands
    MSG msg = { 0 };
    while (PeekMessage(&msg, _hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Menu::deinit()
{
    // Clean up menu items and handle

    DestroyMenu(_hMenu);
    _hMenu = nullptr;
}


void Menu::addMenuItems()
{
    HMENU hFileMenu = CreateMenu();

    AppendMenu(hFileMenu, MF_STRING, ID_OPEN, L"&Open");
    AppendMenu(hFileMenu, MF_STRING, ID_SAVE, L"&Save");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, ID_EXIT, L"&Exit");

    AppendMenu(_hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");

    /*HMENU hObjectMenu = CreatePopupMenu();

    AppendMenu(hObjectMenu, MF_STRING, ID_LOAD_OBJECT, L"&Load Object");

    AppendMenu(_hMenu, MF_POPUP, (UINT_PTR)hObjectMenu, L"&Object");*/
}

//void Menu::HandleCommand(WPARAM wParam)
//{
//    switch (LOWORD(wParam))
//    {
//    case ID_OPEN:
//        // Handle open command
//        break;
//
//    case ID_SAVE:
//        // Handle save command
//        break;
//
//    case ID_EXIT:
//        // Handle exit command
//        break;
//
//    case ID_LOAD_OBJECT:
//        // Handle load object command
//        break;
//
//    default:
//        break;
//    }
//}


