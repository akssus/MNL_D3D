#include "MnResourcePool.h"
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
	
	std::shared_ptr<MnMesh> mesh = std::make_shared<MnMesh>();

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
	const auto meshData = _ReadMeshes(scene, currentNode, nullptr);
	if (meshData != nullptr)
	{
		package.m_lstSpMeshes.push_back(meshData);
	}

	//using BFS add all meshes
	/*
	DO STH
	*/

	//map to table
	m_modelPackages[fileName] = package;

	return S_OK;
}

HRESULT MnResourcePool::_LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName)
{

}
HRESULT MnResourcePool::_ReadFromAssimpScene(const aiScene* scene)
{

}

std::shared_ptr<MnMeshData> MnResourcePool::_ReadMeshes(const aiScene* scene, const aiNode* node, const MnMeshData* pParent)
{
	std::shared_ptr<MnMeshData> retMeshData = nullptr;
	int indexOffset = 0;
	if (node->mMeshes != 0)
	{
		retMeshData = std::make_shared<MnMeshData>();
		retMeshData->SetName(node->mName.C_Str());
		retMeshData->SetParent(pParent);

		//read submeshes
		for (int i = 0; i < node->mNumMeshes; ++i)
		{
			UINT meshIndex = node->mMeshes[i];
			const aiMesh* mesh = scene->mMeshes[meshIndex];

			MnSubMeshData submesh;
			submesh.subMeshName = mesh->mName.C_Str;
			submesh.indexOffset = indexOffset;

			MnGenericVertexStruct vertex;

			//read positions
			int numVerts = mesh->mNumVertices;
			for (int j = 0; j < numVerts; ++j)
			{
				vertex[MN_SEMANTICS_POSITION0].x = mesh->mVertices[j].x;
				vertex[MN_SEMANTICS_POSITION0].y = mesh->mVertices[j].y;
				vertex[MN_SEMANTICS_POSITION0].z = mesh->mVertices[j].z;
			}

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

				for (int j = 0; j < numVerts; ++j)
				{
					vertex[MN_SEMANTICS_TEXCOORD0 + texCoordIndex].x = mesh->mTextureCoords[texCoordIndex][j].x;
					vertex[MN_SEMANTICS_TEXCOORD0 + texCoordIndex].y = mesh->mTextureCoords[texCoordIndex][j].y;
					vertex[MN_SEMANTICS_TEXCOORD0 + texCoordIndex].z = mesh->mTextureCoords[texCoordIndex][j].z;
				}
			}
			//add vertex
			retMeshData->AddVertex(vertex);

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
			retMeshData->AddSubMesh(submesh);
		}
	}



	return retMeshData;
}