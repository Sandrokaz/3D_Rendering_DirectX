//#define NOMINMAX //  for preventing conflicts with the 'min' and 'max' macros defined in the Windows header
#include <Windows.h>		
#include "Framework/MenuHandler.h"
#include "Framework/Window.h"
#include "Framework/D3D.h"
#include "Framework/Time.h"
#include "Framework/Camera.h"
#include "Framework/Utilities.h"
#include "Framework/LightBuffer.h"
#include "Framework/Material.h"
#include "Framework/Mesh.h"
#include <DirectXMath.h>


int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow) {

	INT error = 0;
	UINT width = 1280;
	UINT height = 800;
	BOOL isFullscreen = FALSE;

	// 1. Window												
	Window window = {};
	error = window.init(hInstance, width, height);
	CheckError(error);


	
	 //2. D3D
	D3D d3d = {};
	error = d3d.init(window.GetWindowHandle(), width, height, isFullscreen);
	CheckError(error);
	


	//4. Mesh
	Mesh cube = {};
	XMFLOAT3 cubePos = { 0.0f, 0, 0};
	XMFLOAT3 cubeRot = { 0, 0, 0 };
	XMFLOAT3 cubeScale = { 1, 1, 1 };
	error = cube.init(d3d.getDevice(), "Shapes/cube.obj", cubePos, cubeRot, cubeScale);
	CheckError(error);
												   

	//4. Mesh
	Mesh prism = {};
	XMFLOAT3 prismPos = { 3.0f, 0, 0};
	XMFLOAT3 prismRot = { 0,0, 0 };
	XMFLOAT3 prismScale = { 1, 1, 1 };
	error = prism.init(d3d.getDevice(), "Shapes/prism.obj", prismPos, prismRot, prismScale);
	CheckError(error);



	//4. Mesh
	Mesh hedra = {};
	XMFLOAT3 hedraPos = { 0.0f, 0, -1.0f };
	XMFLOAT3 hedraRot = { 0, 0, 0 };
	XMFLOAT3 hedraScale = { 1, 1, 1 };
	error = hedra.init(d3d.getDevice(), "Shapes/hedra.obj", hedraPos, hedraRot, hedraScale);
	CheckError(error);



	// Create Camera
	Camera camera = {};
	camera.setPosition(0.0f, 0.0f, -9.0f);
	camera.setProjectionValues(60.0f, width, height, 0.1f, 1000.0f);



	//3. TIME
	Time time = {};
	error = time.init();
	CheckError(error);




	//6. Material

	Material cubeMaterial = {};
	error = cubeMaterial.init(d3d.getDevice(), TEXT("Textures/woodtex.jpg"), TEXT("Shaders/GlossyVertexShader.cso"), TEXT("Shaders/GlossyPixelShader.cso"));
	CheckError(error);


	Material prismMaterial = {};
	error = prismMaterial.init(d3d.getDevice(), TEXT("Textures/metaltex.jpg"), TEXT("Shaders/GlossyVertexShader.cso"), TEXT("Shaders/GlossyPixelShader.cso"));
	CheckError(error);

	Material hedraMaterial = {};
	error = hedraMaterial.init(d3d.getDevice(), TEXT("Textures/stonetex.jpg"), TEXT("Shaders/MattVertexShader.cso"), TEXT("Shaders/MattPixelShader.cso"));
	CheckError(error);



	
  //7. Light

	LightBuffer light = {};
	light.ambientColor = { 0.2f, 0.15f, 0.1f, 1.0f };
	light.lightDirection = { -0.5f, 0.5f, -1.0f };
	light.diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	light.specularPower = 32;
	light.specularColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	light.roughness = 500;
	 

	cubeMaterial.setLight(d3d.getDeviceContext(), light);
	prismMaterial.setLight(d3d.getDeviceContext(), light);
	hedraMaterial.setLight(d3d.getDeviceContext(), light);
	
	while (true)
	{
		if (!window.run())
			break;

		FLOAT rotSpeed = 0.5f * time.getDeltaTime();

		//// Update camera movement
		//inputManager.Update();
		//if (inputManager.IsKeyDown('W'))
		//{
		//	camera.MoveForward(time.getDeltaTime());
		//}
		//if (inputManager.IsKeyDown('S'))
		//{
		//	camera.MoveBackward(time.getDeltaTime());
		//}
		//if (inputManager.IsKeyDown('A'))
		//{
		//	camera.MoveLeft(time.getDeltaTime());
		//}
		//if (inputManager.IsKeyDown('D'))
		//{
		//	camera.MoveRight(time.getDeltaTime());
		//}




		 // Update 
		time.update();
		camera.update(time.getDeltaTime());

		cube.update(time.getDeltaTime());
		cube.adjustRotation(rotSpeed, 0, 0);
	
		prism.update(time.getDeltaTime());
		prism.adjustRotation(0, 0, 0);

		hedra.update(time.getDeltaTime());
		hedra.adjustRotation(0, 0, 0);


		// Draw

		d3d.beginScene(0.0f, 0.0f, 1.0f);


		// Render
	
		cubeMaterial.render(d3d.getDeviceContext());
		cubeMaterial.setMatrices(d3d.getDeviceContext(), cube.getWorldMatrix4x4(),camera.getViewMatrix4x4(), camera.getProjectionMatrix4x4(), camera.getPositionFloat3());
		cube.render(d3d.getDeviceContext());

		prismMaterial.render(d3d.getDeviceContext());
		prismMaterial.setMatrices(d3d.getDeviceContext(), prism.getWorldMatrix4x4(), camera.getViewMatrix4x4(), camera.getProjectionMatrix4x4(), camera.getPositionFloat3());
		prism.render(d3d.getDeviceContext());
		
		hedraMaterial.render(d3d.getDeviceContext());
		hedraMaterial.setMatrices(d3d.getDeviceContext(), hedra.getWorldMatrix4x4(), camera.getViewMatrix4x4(), camera.getProjectionMatrix4x4(), camera.getPositionFloat3());
		hedra.render(d3d.getDeviceContext());



		d3d.endScene();
	}






	// Clean up

	cube.deInit();
	prism.deInit();
	hedra.deInit();
	cubeMaterial.deInit();
	prismMaterial.deInit();
	hedraMaterial.deInit();
	time.deInit();
	camera.deInit();
	d3d.deInit();




	return  0;
}







