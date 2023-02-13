#include <Windows.h>
#include "Window.h"
#include "D3D.h"
#include "Time.h"
#include "Camera.h"
#include"Utilities.h"
#include "LightBuffer.h"
#include "Material.h"
#include "Mesh.h"
#include <DirectXMath.h>


int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow) {

	INT error = 0;
	UINT width = 1280;
	UINT height = 720;
	BOOL isFullscreen = FALSE;

	// 1. Window
	Window window = {};
	window.init(hInstance, width, height);
	//CheckError(error);

	 //2. D3D
	D3D d3d = {};
	d3d.init(window.GetWindowHandle(), width, height, isFullscreen);

	//3. TIME
	Time time = {};
	time.init();
	


	//4. Mesh
	Mesh cubeMesh = { };




	//5.Camera
	Camera camera = {};
    camera.init(width, height);
	CheckError(error);




	//6. Material








  //7. Light

	LightBuffer light = {};
	light.ambientColor = { 0.2f, 0.15f, 0.1f, 1.0f };
	light.lightDirection = { -0.5f, 0.5f, -1.0f };
	light.diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	light.specularPower = 32;
	light.specularColor = { 0.0f, 0.0f, 0.0f, 1.0f };




	while (true)
	{
		if (!window.run())
			break;

		FLOAT rotSpeed = 1.0f * time.getDeltaTime();

		// Update
		time.update();
		camera.update(time.getDeltaTime());
	


		d3d.endScene();
	}






	// Clean up




	time.deInit();
	camera.deInit();
	d3d.deInit();

}







