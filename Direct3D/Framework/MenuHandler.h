#define ID_OPEN         1001
#define ID_SAVE         1002
#define ID_EXIT         1003
#define ID_LOAD_CUBE    1004
#define ID_LOAD_HEDRA    1005
#define ID_LOAD_PRISM    1006
                               


#pragma once
#include <Windows.h>


class Menu
{
public:
    INT init(HWND hWnd);
    void deinit();
    void onMenuCommand(int id);
    void addMenuItems();
    void update();

    //void render();

private:
    HWND _hWnd = nullptr;
    HMENU _hMenu = nullptr;

    RECT clientRect;
    RECT _lastClientSize = {};
};
