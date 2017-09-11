#include "MnMesh.h"

using namespace MNL;

MnMesh::MnMesh()
{
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
}
void MnMesh::SetParent(const std::shared_ptr<MnMesh>& spMesh)
{
	m_spParent = spMesh;
}
std::shared_ptr<MnMesh> MnMesh::GetParent() const
{
	return m_spParent;
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