#include "MnMesh.h"

using namespace MNL;

MnMesh::MnMesh()
{
}


MnMesh::~MnMesh()
{
}


//HRESULT MnMesh::LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& modelFileName, const std::shared_ptr<MnCustomVertexType>& spVertexType)

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