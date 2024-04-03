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



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow) {

	INT error = 0;	   
	UINT width = 1280;
	UINT height = 1080;
	BOOL isFullscreen = FALSE;

	//  Window												
	Window window = {};
	error = window.init(hInstance, width, height);
	CheckError(error);


	
	 // D3D
	D3D d3d = {};
	error = d3d.init(window.getWindowHandle(), width, height, isFullscreen);
	CheckError(error);
	


	
	// Mesh
	Mesh cubeMesh = {};
	XMFLOAT3 cubeMeshPos = { 0.0f, 0, 0 };
	XMFLOAT3 cubeMeshRot = { 0, 0, 0 };
	XMFLOAT3 cubeMeshScale = { 1, 1, 1 };
    error = cubeMesh.init(d3d.getDevice(), "Shapes/ico.obj", cubeMeshPos, cubeMeshRot, cubeMeshScale);
	CheckError(error);
	
								  	

	Mesh prismMesh = {};
	XMFLOAT3 prismMeshPos = { 3, 0, 0 };
	XMFLOAT3 prismMeshRot = { 0,0, 0 };
	XMFLOAT3 prismMeshScale = { 1, 1, 1 };
	error = prismMesh.init(d3d.getDevice(), "Shapes/prism.obj", prismMeshPos, prismMeshRot, prismMeshScale);
	CheckError(error);	
		
	
	Mesh hedraMesh = {};
	XMFLOAT3 hedraMeshPos = { -9.0f, 0, 0 };
	XMFLOAT3 hedraMeshRot = { 0, 0, 0 };
	XMFLOAT3 hedraMeshScale = { 1, 1, 1 };
	error = hedraMesh.init(d3d.getDevice(), "Shapes/hedra.obj", hedraMeshPos, hedraMeshRot, hedraMeshScale);
	CheckError(error);



	// Camera
	Camera camera = {};
	camera.setPosition(0.0f, 0.0f, -4.0f);
	camera.setProjectionValues(60.0f, width, height, 0.1f, 1000.0f);



	// TIME
	Time time = {};
	error = time.init();
	CheckError(error);




	// Material

	Material cubeMaterial = {};
	error = cubeMaterial.init(d3d.getDevice(), TEXT("Textures/tex4.jpg"), NULL, TEXT("Shaders/GlossyVertexShader.cso"), TEXT("Shaders/GlossyPixelShader.cso"));
	CheckError(error);


	Material prismMaterial = {};
	error = prismMaterial.init(d3d.getDevice(), TEXT("Textures/tex1.jpg"), NULL, TEXT("Shaders/MattVertexShader.cso"), TEXT("Shaders/MattPixelShader.cso"));
	CheckError(error);

	Material hedraMaterial = {};
	error = hedraMaterial.init(d3d.getDevice(), TEXT("Textures/tex4.jpg"), NULL, TEXT("Shaders/GlossyVertexShader.cso"), TEXT("Shaders/GlossyPixelShader.cso"));
	CheckError(error);

  // Light

	LightBuffer light = {};
	light.lightDirection = { -0.5f, 1.5f, -1.0f };
	light.lightIntensity = 1.5f;
	light.lightColor = { 1.5f, 1.5f, 1.5f, 1.5f };
	light.ambientColor = { 0.2f, 0.15f, 0.1f, 1.0f };

	light.ambientLightPower = 0.9f;
	light.diffuseColor = { 1.5f, 1.5f, 1.5f, 1.5f };
	light.specularColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	light.specularPower = 32.0f;
	light.glosiness = 0.8f;

	cubeMaterial.setLight(d3d.getDeviceContext(), light);
	prismMaterial.setLight(d3d.getDeviceContext(), light);
	hedraMaterial.setLight(d3d.getDeviceContext(), light);
	
	while (true)
	{
		if (!window.run())
			break;

		FLOAT rotSpeed = 0.5f * time.getDeltaTime();



		 // Update 
		time.update();
		camera.update(time.getDeltaTime());
		
		cubeMesh.update(time.getDeltaTime());
		cubeMesh.adjustRotation(rotSpeed, 0, 0);
		
		prismMesh.update(time.getDeltaTime());
		prismMesh.adjustRotation(0, 0, 0);

		hedraMesh.update(time.getDeltaTime());
		hedraMesh.adjustRotation(0, 0, 0);


		// Draw

		d3d.beginScene(0.0f, 0.0f, 0.0f);


		// Render
		cubeMaterial.render(d3d.getDeviceContext());
		cubeMaterial.setMatrices(d3d.getDeviceContext(), cubeMesh.getWorldMatrix4x4(), camera.getViewMatrix4x4(), camera.getProjectionMatrix4x4(), camera.getPositionFloat3());
		cubeMesh.render(d3d.getDeviceContext());

	
		prismMaterial.render(d3d.getDeviceContext());
		prismMaterial.setMatrices(d3d.getDeviceContext(), prismMesh.getWorldMatrix4x4(), camera.getViewMatrix4x4(), camera.getProjectionMatrix4x4(), camera.getPositionFloat3());
		prismMesh.render(d3d.getDeviceContext());
		
		hedraMaterial.render(d3d.getDeviceContext());
		hedraMaterial.setMatrices(d3d.getDeviceContext(), hedraMesh.getWorldMatrix4x4(), camera.getViewMatrix4x4(), camera.getProjectionMatrix4x4(), camera.getPositionFloat3());
		hedraMesh.render(d3d.getDeviceContext());



		d3d.endScene();
	}






	// Clean up
	
	cubeMesh.deInit();
	prismMesh.deInit();
	hedraMesh.deInit();
	cubeMaterial.deInit();
	prismMaterial.deInit();
	hedraMaterial.deInit();
	camera.deInit();
	time.deInit();
	d3d.deInit();
	window.deInit();
	



	return  0;
}


