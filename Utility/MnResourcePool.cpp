#include "MnResourcePool.h"
#include <algorithm>
#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"

using namespace MNL;

MnResourcePool::MnResourcePool()
{
	m_modelPackages["default"] = _ModelPackage();
}

MnResourcePool::~MnResourcePool()
{
}

HRESULT MnResourcePool::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene)
	{
		//error log
		return E_FAIL;
	}
	_ModelPackage package;
	package.m_packageName = fileName;

	//first node is root node
	const aiNode* currentNode = scene->mRootNode;
	HRESULT result = _ReadMeshes(cpDevice, scene, currentNode, 0, package, vertexType);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	//read materials, lights..

	//mapping to table
	m_modelPackages[fileName] = package;

	return S_OK;
}
HRESULT MnResourcePool::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName)
{
	if (m_modelPackages.count(fileName) == 0)
	{
		m_modelPackages[fileName] = _ModelPackage();
	}
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		//error log
		return E_FAIL;
	}
	
	const aiNode* findingNode = scene->mRootNode->FindNode(meshName.c_str());
	if (findingNode == nullptr)
	{
		//node not found
		return E_FAIL;
	}
	auto meshData = _ReadSingleMesh(cpDevice, scene, findingNode, vertexType);
	m_modelPackages[fileName].m_lstSpMeshes.push_back(meshData);

	return S_OK;
}

HRESULT MnResourcePool::_LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName)
{
	return S_OK;
}
HRESULT MnResourcePool::_ReadFromAssimpScene(const aiScene* scene)
{
	return S_OK;
}

HRESULT MnResourcePool::_ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, _ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	//ONE NODE ONE MESH
	std::shared_ptr<MnMeshData> meshData = nullptr;

	//get current Mesh data's index to set as parent index
	UINT currentMeshIndex = modelPackage.m_lstSpMeshes.size();

	//read only if node has meshes
	if (node->mNumMeshes != 0)
	{
		meshData = _ReadSingleMesh(cpDevice, scene, node, vertexType);
	}
	//add to package
	if (meshData != nullptr)
	{
		//root mesh's parent index is nullptr
		if (modelPackage.m_lstSpMeshes.size() > 0)
		{
			meshData->SetParentIndex(parentIndex);
		}
		//add to package
		modelPackage.m_lstSpMeshes.push_back(meshData);
	}

	//recursively read mesh data;
	for (int i = 0; i < node->mNumChildren; ++i)
	{
		HRESULT result = _ReadMeshes(cpDevice, scene, node->mChildren[i], currentMeshIndex, modelPackage, vertexType);
		if (FAILED(result))
		{
			//error log
			return E_FAIL;
		}
	}
	return S_OK;
}
std::shared_ptr<MnMeshData> MnResourcePool::_ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType)
{
	//ONE NODE ONE MESH
	std::shared_ptr<MnMeshData> meshData = nullptr;

	//set mesh name
	meshData = std::make_shared<MnMeshData>();
	meshData->SetName(node->mName.C_Str());
	aiMatrix4x4 transform = node->mTransformation;
	meshData->SetTransform(DirectX::SimpleMath::Matrix((float*)&(transform.Transpose())));

	//calculate total number of index and vertex
	UINT totalVertexCount = 0;
	UINT totalIndexCount = 0;
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		UINT numVerts = scene->mMeshes[meshIndex]->mNumVertices;
		totalVertexCount += numVerts;
		int numFaces = scene->mMeshes[meshIndex]->mNumFaces;
		totalIndexCount += numFaces * 3;
	}

	//prepare vertex array
	UINT vertexStride = vertexType->TotalByteSize();
	UINT numFloats = vertexStride / 4;
	std::vector<float> vertexArray;
	vertexArray.resize(totalVertexCount * (numFloats));
	UINT16 flags = vertexType->GetFlags();

	//prepare index array
	std::vector<UINT> indexArray;
	indexArray.resize(totalIndexCount);

	//read submeshes
	UINT vertexBase = 0;
	UINT indexBase = 0;
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		UINT meshIndex = node->mMeshes[i];
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		//read vertices
		UINT numVerts = mesh->mNumVertices;
		for (int j = 0; j < numVerts; ++j)
		{
			UINT vertexOffset = vertexBase + (j * numFloats);
			UINT currentOffset = 0;
			//read positions
			if (flags & MN_CVF_POSITION0)
			{
				vertexArray[vertexOffset + currentOffset++] = mesh->mVertices[j].x;
				vertexArray[vertexOffset + currentOffset++] = mesh->mVertices[j].y;
				vertexArray[vertexOffset + currentOffset++] = mesh->mVertices[j].z;
			}
			//read normals
			if (mesh->HasNormals())
			{
				if (flags & MN_CVF_NORMAL0)
				{
					vertexArray[vertexOffset + currentOffset++] = mesh->mNormals[j].x;
					vertexArray[vertexOffset + currentOffset++] = mesh->mNormals[j].y;
					vertexArray[vertexOffset + currentOffset++] = mesh->mNormals[j].z;
				}
			}

			//read texcoords
			int texCoordIndex = 0;
			if (mesh->mTextureCoords[texCoordIndex] != nullptr)
			{
				if (flags & MN_CVF_TEXCOORD0)
				{
					vertexArray[vertexOffset + currentOffset++] = mesh->mTextureCoords[texCoordIndex][j].x;
					vertexArray[vertexOffset + currentOffset++] = mesh->mTextureCoords[texCoordIndex][j].y;
				}
			}
		}
		//rebase vertex
		vertexBase += numVerts * numFloats;

		//read indices;
		MnSubMesh submesh;
		//set submesh name and offset
		submesh.subMeshName = mesh->mName.C_Str();
		submesh.indexOffset = indexBase;
		int numFaces = mesh->mNumFaces;
		submesh.indexCount = numFaces * 3;

		for (int j = 0; j < numFaces; ++j)
		{
			UINT indexOffset = j * 3;
			aiFace& face = mesh->mFaces[j];
			for (int faceIndex = 0; faceIndex < face.mNumIndices; ++faceIndex)
			{
				indexArray[indexBase + indexOffset + faceIndex] = face.mIndices[faceIndex];
			}
		}
		//update base offset of submesh indices
		indexBase += submesh.indexCount;

		//init vertex and index buffer
		_InitBuffers(cpDevice, meshData, vertexType, vertexArray, totalVertexCount, indexArray, totalIndexCount);

		//add to mesh data
		meshData->AddSubMesh(submesh);
	}

	return meshData;
}
HRESULT MnResourcePool::_InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray,UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount )
{
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertexArray.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indexArray.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//create buffers
	auto vertexBuffer = std::make_shared<MnVertexBuffer>();
	HRESULT result = vertexBuffer->Init(cpDevice, vertexType, vertexCount, &vertexData, false);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	auto indexBuffer = std::make_shared<MnIndexBuffer>();
	result = indexBuffer->Init(cpDevice, indexCount, &indexData);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	meshData->SetVertexBuffer(vertexBuffer);
	meshData->SetIndexBuffer(indexBuffer);

	return S_OK;
}


std::shared_ptr<MnMeshData> MnResourcePool::GetMeshData(const std::string& modelPackageName, const std::string& meshName) const
{
	if (m_modelPackages.count(modelPackageName) == 0)
	{
		//model package not found
		return nullptr;
	}
	auto lstMeshes = m_modelPackages.at(modelPackageName).m_lstSpMeshes;
	//find matched mesh data
	auto it = std::find_if(lstMeshes.begin(),lstMeshes.end(),
		[&](const std::shared_ptr<MnMeshData>& meshData)
	{
		if (meshData->GetName() == meshName) return true;
		return false;
	});
	if (it == lstMeshes.end())
	{
		//find failed
		return nullptr;
	}
	return *it;
}

