#include "SimpleModel.h"
#include <sstream>
#include <fstream>

using namespace MNL;

SimpleModel::SimpleModel():m_indexCount(0),m_vertexCount(0)
{
}


SimpleModel::~SimpleModel()
{
}

HRESULT SimpleModel::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& modelFileName, const std::shared_ptr<MnCustomVertexType>& spVertexType)
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

HRESULT SimpleModel::_LoadModel(const std::wstring& fileName)
{
	std::ifstream inputStream(fileName);
	if (inputStream.is_open() == false)
	{
		//error log
		return E_FAIL;
	}

	std::string line;
	int numVerts = 0;
	while (std::getline(inputStream, line))
	{
		std::istringstream strStream(line);
		std::string token;
		strStream >> token;
		if (token == "VertexCount:")
		{
			strStream >> numVerts;
		}
		if (token == "Data:")
		{
			std::string vertexData;
			for (int i = 0; i < numVerts; ++i)
			{
				_VertexType vertex;
				ZeroMemory(&vertex, sizeof(_VertexType));
				std::getline(inputStream, vertexData);
				std::istringstream vertexDataStream(vertexData);
				vertexDataStream >> vertex.position.x >> vertex.position.y >> vertex.position.z
					>> vertex.texCoord1.x >> vertex.texCoord1.y p; ['\.``````````````````````````````````````````````````````````````````````````````````
					;l ']
					>> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;

				vertex.color.x = vertex.normal.x;
				vertex.color.y = vertex.normal.y;
				vertex.color.z = vertex.normal.z;
				vertex.color.w = 1.0f;

				m_lstMeshVertices.push_back(vertex);
				m_lstIndices.push_back(i);
			}
		}
	}
	inputStream.close();

	return S_OK;
}
HRESULT SimpleModel::_InitBuffers(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType)
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