#define ID_OPEN         1001
#define ID_SAVE         1002
#define ID_EXIT         1003
#define ID_LOAD_OBJECT  1004


#pragma once
#include <Windows.h>

class Menu
{
public:
   INT init(HWND hWnd);
    void deinit();
    void addMenuItems();

    void update();
    //void render();

private:
    HWND _hWnd = nullptr;
    HMENU _hMenu = nullptr;
};
