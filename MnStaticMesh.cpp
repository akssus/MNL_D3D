#include "MnStaticMesh.h"

using namespace MNL;

MnStaticMesh::MnStaticMesh()
{
}


MnStaticMesh::~MnStaticMesh()
{
}

HRESULT MnStaticMesh::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData)
{
	if (spMeshData == nullptr)
	{
		return E_FAIL;
	}
	m_name = spMeshData->GetName();
	m_spVertexBuffer = spMeshData->GetVertexBuffer();
	m_spIndexBuffer = spMeshData->GetIndexBuffer();

	//copy sub meshes
	m_subMeshes.assign(spMeshData->GetSubMeshes().begin(), spMeshData->GetSubMeshes().end());

	return S_OK;
}