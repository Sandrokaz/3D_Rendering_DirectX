#include "MenuHandler.h"
#include "Mesh.h"
#include "D3D.h"
#include "Material.h"


INT Menu::init(HWND hWnd)
{
    _hWnd = hWnd;
    _hMenu = CreateMenu();
    SetMenu(hWnd, _hMenu);


    addMenuItems();
    return 0;
}

void Menu::deinit()
{
    DestroyMenu(_hMenu);
}

void Menu::onMenuCommand(int id)
{


}




void Menu::addMenuItems()
{
    HMENU fileMenu = CreateMenu();
    AppendMenu(_hMenu, MF_POPUP, (UINT_PTR)fileMenu, L"&File");

    AppendMenu(fileMenu, MF_STRING, ID_OPEN, L"&Open");
    AppendMenu(fileMenu, MF_STRING, ID_SAVE, L"&Save");
    AppendMenu(fileMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(fileMenu, MF_STRING, ID_EXIT, L"&Exit");

    HMENU loadMenu = CreateMenu();
    AppendMenu(_hMenu, MF_POPUP, (UINT_PTR)loadMenu, L"&Load");

    AppendMenu(loadMenu, MF_STRING, ID_LOAD_CUBE, L"&Cube");
    AppendMenu(loadMenu, MF_STRING, ID_LOAD_HEDRA, L"&Hedra");
    AppendMenu(loadMenu, MF_STRING, ID_LOAD_PRISM, L"&Prism");
}



void Menu::update()
{
        //// Get the window's client area
        //RECT clientRect;
        //GetClientRect(_hWnd, &clientRect);

        //// Create an off-screen device context and bitmap
        //HDC hdcOffscreen = CreateCompatibleDC(nullptr);
        //HBITMAP hBitmap = CreateCompatibleBitmap(hdcOffscreen, clientRect.right, clientRect.bottom);
        //HGDIOBJ hOldBitmap = SelectObject(hdcOffscreen, hBitmap);

        //// Draw the menu onto the off-screen device context
        //DrawMenuBar(_hWnd);

        //// Copy the off-screen bitmap to the window's device context
        //HDC hdc = GetDC(_hWnd);
        //BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcOffscreen, 0, 0, SRCCOPY);
        //ReleaseDC(_hWnd, hdc);

        //// Clean up
        //SelectObject(hdcOffscreen, hOldBitmap);
        //DeleteObject(hBitmap);
        //DeleteDC(hdcOffscreen);
  
        // Check if the client area size has changed
     
        GetClientRect(_hWnd, &clientRect);
        if (clientRect.right == _lastClientSize.right && clientRect.bottom == _lastClientSize.bottom)
        {
            return; // No need to redraw the menu
        }

        // Update the last client size
        _lastClientSize = clientRect;

        // Create a memory DC and bitmap
        HDC hdcMem = CreateCompatibleDC(nullptr);
        HBITMAP hBitmap = CreateCompatibleBitmap(GetDC(_hWnd), clientRect.right, clientRect.bottom);
        HGDIOBJ hOldBitmap = SelectObject(hdcMem, hBitmap);

        // Draw the menu onto the memory DC
        DrawMenuBar(_hWnd);

        // Copy the memory DC to the screen
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);
        BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcMem, 0, 0, SRCCOPY);
        EndPaint(_hWnd, &ps);

        // Clean up
        SelectObject(hdcMem, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
    


}














