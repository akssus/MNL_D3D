#include "MnMesh.h"

using namespace MNL;

MnMesh::MnMesh()
{
	m_matTransform = DirectX::SimpleMath::Matrix::Identity;
}


MnMesh::~MnMesh()
{
}


HRESULT MnMesh::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData)
{
	if (spMeshData == nullptr)
	{
		return E_FAIL;
	}
	return S_OK;
}
void MnMesh::SetParent(const std::shared_ptr<MnMesh>& spMesh)
{
	m_spParent = spMesh;
}
std::shared_ptr<MnMesh> MnMesh::GetParent() const
{
	return m_spParent;
}
void MnMesh::SetTransform(const DirectX::SimpleMath::Matrix& matTransform)
{
	m_matTransform = matTransform;
}
const DirectX::SimpleMath::Matrix& MnMesh::GetTransform() const
{
	return m_matTransform;
}
UINT MnMesh::GetNumSubMeshes() const
{
	return m_subMeshes.size();
}
const MnSubMesh& MnMesh::GetSubMesh(UINT index) const
{
	return m_subMeshes[index];
}
const CPD3DBuffer MnMesh::GetVertexBuffer() const
{
	return m_spVertexBuffer->GetBuffer();
}
UINT MnMesh::GetVertexBufferStride() const
{
	return m_spVertexBuffer->GetStride();
}
const CPD3DBuffer MnMesh::GetIndexBuffer() const
{
	return m_spIndexBuffer->GetBuffer();
}
UINT MnMesh::GetIndexCount() const
{
	return m_spIndexBuffer->GetIndexCount();
}
DXGI_FORMAT MnMesh::GetIndexBufferFormat() const
{
	return m_spIndexBuffer->GetFormat();
}