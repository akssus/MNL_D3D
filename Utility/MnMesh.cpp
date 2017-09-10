#include "MnMesh.h"

using namespace MNL;

MnMesh::MnMesh()
{
}


MnMesh::~MnMesh()
{
}


HRESULT MnMesh::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData, const std::shared_ptr<MnCustomVertexType>& spVertexType)
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
	return m_vertexBuffer.GetBuffer();
}
UINT MnMesh::GetVertexBufferStride() const
{
	return m_vertexBuffer.GetStride();
}
const CPD3DBuffer MnMesh::GetIndexBuffer() const
{
	return m_indexBuffer.GetBuffer();
}
UINT MnMesh::GetIndexCount() const
{
	return m_indexBuffer.GetIndexCount();
}
DXGI_FORMAT MnMesh::GetIndexBufferFormat() const
{
	return m_indexBuffer.GetFormat();
}