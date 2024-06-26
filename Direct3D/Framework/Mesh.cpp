#include <iostream>
#include "Mesh.h"
#include "Utilities.h"
#include "../assimp/include/Importer.hpp"
#include "../assimp/include/scene.h"
#include "../assimp/include/cimport.h"
#include "../assimp/include/postprocess.h"
#include "../assimp/include/vector3.h"






Mesh::Mesh()
{
	_positionFloat3 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_rotationFloat3 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_scaleFloat3 = XMFLOAT3(1.0f, 1.0f, 1.0f);



	_positionVector = XMLoadFloat3(&_positionFloat3);
	_rotationVector = XMLoadFloat3(&_rotationFloat3);
	_scaleVector = XMLoadFloat3(&_scaleFloat3);


}


INT Mesh::init(ID3D11Device* pD3DDevice, const CHAR* filename, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
{
	
	Assimp::Importer importer;

	importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, true); // Normalize position, tangent, and bitangent vectors
	importer.SetPropertyInteger(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80); // Set the maximum smoothing angle for normals
	importer.SetPropertyInteger(AI_CONFIG_PP_CT_MAX_SMOOTHING_ANGLE, 80); // Set the maximum smoothing angle for tangents and bitangents

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace |aiProcess_FlipUVs | aiProcess_FixInfacingNormals);



	if (!scene)
	{
		cout << "Failed to load Mesh file correctly!" << endl;
		return -1;
	}																		

	if (!scene->HasMeshes())
	{
		cout << "Scene has no mesh" << endl;
		return -1;
	}

	aiMesh* mesh = scene->mMeshes[0];
	vector<Vertex> vertices;
	vertices.resize(mesh->mNumVertices);

	// Calculate Vertices
	for (int v = 0; v < mesh->mNumVertices; v++)
	{
		// Position
		vertices[v].position = XMFLOAT3(
			mesh->mVertices[v].x,
			mesh->mVertices[v].y,
			mesh->mVertices[v].z
		);
		// UV
		vertices[v].uv = XMFLOAT2(
			mesh->mTextureCoords[0][v].x,
			mesh->mTextureCoords[0][v].y
		);

		// Normal
		vertices[v].normal = XMFLOAT3(
			mesh->mNormals[v].x,
			mesh->mNormals[v].y,
			mesh->mNormals[v].z
		);

		//Tangent 
		vertices[v].tangent = XMFLOAT3(
			mesh->mTangents[v].x,
			mesh->mTangents[v].y,
			mesh->mTangents[v].z
		);


	}
	_vertexStride = sizeof(Vertex);
	_vertexCount = vertices.size();


	vector<WORD> indices;
	indices.resize(mesh->mNumFaces * 3);
	_indexCount = indices.size();

	// Calculate Indices
	for (int f = 0; f < mesh->mNumFaces; f++)
	{
		aiFace* face = mesh->mFaces + f;

		for (int i = 0; i < face->mNumIndices; i++)
		{
			indices[(3 * f) + i] = *(face->mIndices + i);
		}
	}

		 ////// Calculation von tangenten im Mesh ////////////////

		if (mesh->HasTangentsAndBitangents())
		{
			for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
			{
				const aiFace& face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; ++j)
				{
					unsigned int index = face.mIndices[j];
		
					Vertex& vertex = vertices[index];
		
					// Get the tangent vector
					const aiVector3D& tang = mesh->mTangents[index];
					XMFLOAT3 tangent(tang.x, tang.y, tang.z);
		
		
		
		
		
					// Calculate the normal vector
					XMFLOAT3 normal(vertex.normal.x, vertex.normal.y, vertex.normal.z);
		
					// Calculate the orthogonal projection of the tangent vector onto the plane defined by the normal vector
					XMVECTOR t = XMLoadFloat3(&tangent);
					XMVECTOR n = XMLoadFloat3(&normal);
					t = XMVector3Normalize(t - n * XMVector3Dot(t, n));
					XMStoreFloat3(&tangent, t);
		
					// Add the tangent vector to the vertex
					vertex.tangent = tangent;
				}
			}
		}




	// Initialize Vertex and Index Buffers
	 initVertexBuffer(vertices.data(),pD3DDevice);	
	 initIndexBuffer(indices.data(),pD3DDevice);
	
	
	 // Set mesh position
	setPos(pos.x, pos.y, pos.z);
	setRot(rot.x, rot.y, rot.z);
	setScale(scale.x, scale.y, scale.z);

				   
	
	
	return 0;
}

void Mesh::update(FLOAT deltaTime)
{

}

void Mesh::render(ID3D11DeviceContext* pD3DDeviceContext)
{
	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, offset);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw with index buffer
	pD3DDeviceContext->DrawIndexed(_indexCount, 0, 0);
}

void Mesh::setPos(XMVECTOR _position)
{
	XMStoreFloat3(&_positionFloat3, _position);
	_positionVector = _position;
	updateTransform();
	
}

void Mesh::setPos(FLOAT x, FLOAT y, FLOAT z)
{
	_positionFloat3 = XMFLOAT3(x, y, z);
	_positionVector = XMLoadFloat3(&_positionFloat3);
	updateTransform();
}


void Mesh::setRot(XMVECTOR _rotation)
{
	_rotationVector = _rotation;
	XMStoreFloat3(&_rotationFloat3, _rotationVector);
	updateTransform();
}

void Mesh::setRot(FLOAT x, FLOAT y, FLOAT z)
{
	_rotationFloat3 = XMFLOAT3(x, y, z);
	_rotationVector = XMLoadFloat3(&_rotationFloat3);
	updateTransform();
}

void Mesh::setScale(XMVECTOR _scale)
{
	_scaleVector = _scale;
	XMStoreFloat3(&_scaleFloat3, _scaleVector);
	updateTransform();
}

void Mesh::setScale(FLOAT x, FLOAT y, FLOAT z)
{
	_scaleFloat3 = XMFLOAT3(x, y, z);
	_scaleVector = XMLoadFloat3(&_scaleFloat3);
	updateTransform();
}



void Mesh::adjustPosition(DirectX::XMVECTOR t_position)
{
	_positionVector += t_position;
	XMStoreFloat3(&_positionFloat3, _positionVector);

	updateTransform();
}

void Mesh::adjustPosition(FLOAT x, FLOAT y, FLOAT z)
{
	_positionFloat3.x += x;
	_positionFloat3.y += y;
	_positionFloat3.z += z;

	_positionVector = XMLoadFloat3(&_positionFloat3);

	updateTransform();
}

void Mesh::adjustRotation(DirectX::XMVECTOR t_rotation)
{
	_rotationVector += t_rotation;
	XMStoreFloat3(&_rotationFloat3, _rotationVector);

	updateTransform();
}

void Mesh::adjustRotation(FLOAT x, FLOAT y, FLOAT z)
{
	_rotationFloat3.x += x;
	_rotationFloat3.y += y;
	_rotationFloat3.z += z;

	_rotationVector = XMLoadFloat3(&_rotationFloat3);

	updateTransform();
}

void Mesh::adjustScale(DirectX::XMVECTOR t_scale)
{
	_scaleVector += t_scale;
	XMStoreFloat3(&_rotationFloat3, _scaleVector);

	updateTransform();
}

void Mesh::adjustScale(FLOAT x, FLOAT y, FLOAT z)
{
	_scaleFloat3.x += x;
	_scaleFloat3.y += y;
	_scaleFloat3.z += z;

	_scaleVector = XMLoadFloat3(&_scaleFloat3);

	updateTransform();
}




void Mesh::deInit()
{
	
	safeRelease<ID3D11Buffer>(_pVertexBuffer);
	safeRelease<ID3D11Buffer>(_pIndexBuffer);
	
}

INT Mesh::initVertexBuffer(Vertex vertices[],ID3D11Device* pD3DDevice)
{

	_vertexStride = sizeof(Vertex);




	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _vertexCount * _vertexStride;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has which access

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &vertexData, &_pVertexBuffer);
	CheckFailed(hr, 30);

	//return 0;
}

INT Mesh::initIndexBuffer(WORD indices[], ID3D11Device* pD3DDevice)
{


	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _indexCount * sizeof(WORD);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indices;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &indexData, &_pIndexBuffer);
	CheckFailed(hr, 32);

	//return 0;
}


void Mesh::updateTransform()
{
	XMMATRIX translationMatrix = XMMatrixTranslation(_positionFloat3.x, _positionFloat3.y, _positionFloat3.z);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(_rotationFloat3.x, _rotationFloat3.y, _rotationFloat3.z);
	XMMATRIX scalingMatrix = XMMatrixScaling(_scaleFloat3.x, _scaleFloat3.y, _scaleFloat3.z);

	XMStoreFloat4x4(&_worldMatrix4x4, scalingMatrix * rotationMatrix * translationMatrix);
}









