#include "MnStaticMesh.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnStaticMesh::MnStaticMesh()
{
}


MnStaticMesh::~MnStaticMesh()
{
}

HRESULT MnStaticMesh::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	if (spMeshData == nullptr)
	{
		return E_FAIL;
	}

	m_name = spMeshData->GetName();
	UINT numVertices = spMeshData->GetNumVertices();

	//make vertex array
	std::vector<MnStaticMeshVertex> lstVertices;
	for (int i = 0; i < numVertices; ++i)
	{
		auto& vertex = _CreateVertex(spMeshData->GetVertex(i));
		lstVertices.push_back(vertex);
	}

	UINT numSubMeshes = spMeshData->GetNumSubMeshes();
	//add sub meshes
	for (int i = 0; i < numSubMeshes; ++i)
	{
		MnSubMesh subMesh = _CreateSubMesh(spMeshData->GetSubMesh(i));
		m_subMeshes.push_back(subMesh);
	}

	//serialize indices
	std::vector<UINT> lstIndices;
	for (int i = 0; i < numSubMeshes; ++i)
	{
		auto& lstSubMeshIndices = spMeshData->GetSubMesh(i).lstIndices;
		lstIndices.insert(lstIndices.end(), lstSubMeshIndices.begin(), lstSubMeshIndices.end());
	}
	UINT numIndices = lstIndices.size();

	//actually create buffers
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = lstVertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = lstIndices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	HRESULT result = m_vertexBuffer.Init(cpDevice, spVertexType, numVertices, &vertexData, false);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	result = m_indexBuffer.Init(cpDevice, numIndices, &indexData);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	return S_OK;
}

MnStaticMeshVertex MnStaticMesh::_CreateVertex(const MnGenericVertexStruct& vertexStruct)
{
	MnStaticMeshVertex vertex;
	vertex.position = Vector3(vertexStruct[MN_SEMANTICS_POSITION0].x, vertexStruct[MN_SEMANTICS_POSITION0].y, vertexStruct[MN_SEMANTICS_POSITION0].z);
	vertex.normal = Vector3(vertexStruct[MN_SEMANTICS_NORMAL0].x, vertexStruct[MN_SEMANTICS_NORMAL0].y, vertexStruct[MN_SEMANTICS_NORMAL0].z);
	vertex.texCoord = Vector2(vertexStruct[MN_SEMANTICS_TEXCOORD0].x, vertexStruct[MN_SEMANTICS_TEXCOORD0].y);
	return vertex;
}
MnSubMesh MnStaticMesh::_CreateSubMesh(const MnSubMeshData& subMeshData)
{
	MnSubMesh subMesh;
	subMesh.indexCount = subMeshData.lstIndices.size();
	subMesh.indexOffset = subMeshData.indexOffset;
	subMesh.materialName = subMeshData.materialName;
	subMesh.subMeshName = subMeshData.subMeshName;
	return subMesh;
}