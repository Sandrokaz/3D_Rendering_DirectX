#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Time.h"
#include "Camera.h"
#include"Utilities.h"


int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow) {

	INT error = 0;
	UINT width = 1280;
	UINT height = 720;
	BOOL isFullscreen = FALSE;

	// 1. Window
	Window window = {};
	window.Initialize(hInstance, width, height);
	//CheckError(error);

	 //2. D3D
	D3D d3d = {};
	d3d.Initialize(window.GetWindowHandle(), width, height, isFullscreen);

	//3. TIME
	Time time = {};
	time.Initialize();
	


	// 5. set up time


	Camera camera = {};
    camera.Initialize(width, height);
	CheckError(error);

}







