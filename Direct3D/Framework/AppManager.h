#pragma once
#include "Material.h"
#include "Time.h"
#include "Camera.h"
#include "Mesh.h"
#include "D3D.h"
#include "Window.h"
#include "Utilities.h"
#include "LightBuffer.h"


class AppManager
{
public:
	//Original FrameWork:
	Window window = {};
	D3D d3d = {};
	Camera camera = {};
	Time time = {};
	Material material = {};
	


	BOOL IsRunning = TRUE;

	
	/// <summary>
	/// Init graphics rendering components for all Objects.
	/// </summary>
	/// <param name="hInstance"></param>
	int InitD3D(HINSTANCE hInstance);

	/// <summary>
	/// Initializes the mesh for each object in our scene.		maybe with click of buttons
	/// </summary>
	bool initMeshes(const char* filename, const XMFLOAT3& pos, const XMFLOAT3& rot, const XMFLOAT3& scale);




	void onMenuCommand(WPARAM wParam);




	/// <summary>
	/// Update graphics rendering components for currently initialized objects.
	/// </summary>
	void UpdateD3D();

	

	/// <summary>
	/// Update scene view at runtime.
	/// </summary>
	/// <returns>
	/// Returns true, except, when the "Back" button has been clicked.
	/// </returns>
	BOOL UpdateSceneView();




	/// <summary>
	/// Deinitializes graphics rendering components, when quitting the application.
	/// </summary>
	void deInit();

private:
	std::vector<Mesh> _meshList;
	void deInitMeshes();

};

