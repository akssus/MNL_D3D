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

	std::string fileNameA;
	fileNameA.assign(fileName.begin(), fileName.end());
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileNameA, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		//error log
		return E_FAIL;
	}
	const aiNode* rootNode = scene->mRootNode;

	bool hasMesh = scene->HasMeshes();
	if (hasMesh)
	{
		//only read first node of the scene
		for (int meshIndex = 0; meshIndex < rootNode->mNumMeshes; meshIndex++)
		{

		}
		const aiMesh* mesh = scene->mMeshes[0];
		//read vertices
		UINT numVerts = mesh->mNumVertices;
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			const aiVector3D& position = mesh->mVertices[i];
			MnGenericVertexStruct vertex;
			vertex[MN_SEMANTICS_POSITION0].x = position.x;
			vertex[MN_SEMANTICS_POSITION0].y = position.y;
			vertex[MN_SEMANTICS_POSITION0].z = position.z;
			m_lstMeshVertices.push_back(vertex);
		}
		//read indices
		for (int i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace& face = mesh->mFaces[i];
			m_lstIndices.push_back(face.mIndices[0]);
			m_lstIndices.push_back(face.mIndices[1]);
			m_lstIndices.push_back(face.mIndices[2]);
		}
	}
	else
	{
		return E_FAIL;
	}


	return S_OK;
}

HRESULT MnResourcePool::_LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName)
{

}
HRESULT MnResourcePool::_ReadFromAssimpScene(const aiScene* scene)
{

}