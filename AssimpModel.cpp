#include "AssimpModel.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"

using namespace MNL;
using namespace std;

AssimpModel::AssimpModel()
{
}


AssimpModel::~AssimpModel()
{
}


HRESULT AssimpModel::LoadModelFromFile(const MNL::CPD3DDevice& cpDevice, const std::wstring& modelFileName, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	HRESULT result = _LoadModel(modelFileName);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	result = _InitBuffers(cpDevice, spVertexType);
	if (FAILED(result))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT AssimpModel::_LoadModel(const std::wstring& fileName)
{
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
	if(hasMesh)
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
			_VertexType vertex;
			ZeroMemory(&vertex, sizeof(_VertexType));
			vertex.position.x = position.x;
			vertex.position.y = position.y;
			vertex.position.z = position.z;
			vertex.color.x = 1.0f;
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
HRESULT AssimpModel::_InitBuffers(const MNL::CPD3DDevice& cpDevice, const std::shared_ptr<MNL::MnCustomVertexType>& spVertexType)
{
	m_vertexCount = m_lstMeshVertices.size();
	m_indexCount = m_lstIndices.size();

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = m_lstMeshVertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = m_lstIndices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	HRESULT result = m_vertexBuffer.Init(cpDevice, spVertexType, m_vertexCount, &vertexData, false);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	result = m_indexBuffer.Init(cpDevice, m_indexCount, &indexData);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	return S_OK;
}