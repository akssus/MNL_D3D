#include "MnResourcePool.h"
#include <algorithm>
#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"

using namespace MNL;

MnResourcePool::MnResourcePool()
{
}

MnResourcePool::~MnResourcePool()
{
}

HRESULT MnResourcePool::LoadModelFromFile(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		//error log
		return E_FAIL;
	}
	_ModelPackage package;
	package.m_packageName = fileName;

	//first node is root node
	const aiNode* currentNode = scene->mRootNode;
	HRESULT result = _ReadMeshes(scene, currentNode, 0, package);
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

HRESULT MnResourcePool::_LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName)
{
	return S_OK;
}
HRESULT MnResourcePool::_ReadFromAssimpScene(const aiScene* scene)
{
	return S_OK;
}

HRESULT MnResourcePool::_ReadMeshes(const aiScene* scene, const aiNode* node, UINT parentIndex, _ModelPackage& modelPackage)
{
	std::shared_ptr<MnMeshData> meshData = nullptr;

	//get current Mesh data's index to set as parent index
	UINT currentMeshIndex = modelPackage.m_lstSpMeshes.size();

	//read only if node has meshes
	if (node->mNumMeshes != 0)
	{
		//set mesh name
		meshData = std::make_shared<MnMeshData>();
		meshData->SetName(node->mName.C_Str());

		//root mesh's parent index is nullptr
		if (modelPackage.m_lstSpMeshes.size() > 0)
		{
			meshData->SetParentIndex(parentIndex);
		}
		
		//get current Mesh data's index to set as parent index
		UINT currentMeshIndex = modelPackage.m_lstSpMeshes.size()-1;

		//read submeshes
		int indexOffset = 0;
		for (int i = 0; i < node->mNumMeshes; ++i)
		{
			UINT meshIndex = node->mMeshes[i];
			const aiMesh* mesh = scene->mMeshes[meshIndex];

			MnSubMeshData submesh;
			//set submesh name and offset
			submesh.subMeshName = mesh->mName.C_Str();
			submesh.indexOffset = indexOffset;

			MnGenericVertexStruct vertex;


			int numVerts = mesh->mNumVertices;
			for (int j = 0; j < numVerts; ++j)
			{
				//read positions
				vertex[MN_SEMANTICS_POSITION0].x = mesh->mVertices[j].x;
				vertex[MN_SEMANTICS_POSITION0].y = mesh->mVertices[j].y;
				vertex[MN_SEMANTICS_POSITION0].z = mesh->mVertices[j].z;

				//read normals
				if (mesh->HasNormals())
				{
					for (int j = 0; j < numVerts; ++j)
					{
						vertex[MN_SEMANTICS_NORMAL0].x = mesh->mNormals[j].x;
						vertex[MN_SEMANTICS_NORMAL0].y = mesh->mNormals[j].y;
						vertex[MN_SEMANTICS_NORMAL0].z = mesh->mNormals[j].z;
					}
				}

				//read texcoords
				int texCoordIndex = 0;
				while (mesh->mTextureCoords[texCoordIndex] != nullptr)
				{
					//not allowed to read more than 2 tex coords for now
					if (texCoordIndex >= 2) break;
						vertex[MN_SEMANTICS(MN_SEMANTICS_TEXCOORD0 + texCoordIndex)].x = mesh->mTextureCoords[texCoordIndex][j].x;
						vertex[MN_SEMANTICS(MN_SEMANTICS_TEXCOORD0 + texCoordIndex)].y = mesh->mTextureCoords[texCoordIndex][j].y;
						vertex[MN_SEMANTICS(MN_SEMANTICS_TEXCOORD0 + texCoordIndex)].z = mesh->mTextureCoords[texCoordIndex][j].z;
				}
				//add vertex
				meshData->AddVertex(vertex);
			}
			//read indices;
			int numFaces = mesh->mNumFaces;
			for (int j = 0; j < numFaces; ++j)
			{
				aiFace& face = mesh->mFaces[j];
				for (int faceIndex = 0; faceIndex < face.mNumIndices; ++faceIndex)
				{
					submesh.lstIndices.push_back(face.mIndices[faceIndex]);
				}
			}
			//update base offset of submesh indices
			indexOffset += submesh.lstIndices.size();

			//read material name
			if (scene->HasMaterials())
			{
				const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				aiString materialName;
				material->Get(AI_MATKEY_NAME, materialName);
				submesh.materialName = materialName.C_Str();
			}
			//add to mesh data
			meshData->AddSubMesh(submesh);
		}

		//add to package
		modelPackage.m_lstSpMeshes.push_back(meshData);
	}
	//recursively read mesh data;
	for (int i = 0; i < node->mNumChildren; ++i)
	{
		HRESULT result = _ReadMeshes(scene, node->mChildren[i], currentMeshIndex, modelPackage);
		if (FAILED(result))
		{
			//error log
			return E_FAIL;
		}
	}
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