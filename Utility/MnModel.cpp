#include "MnModel.h"

using namespace MNL;

MnModel::MnModel()
{
}


MnModel::~MnModel()
{
}


HRESULT MnModel::LoadModelFromFile(std::wstring modelFileName)
{


	return S_OK;
}

const CPD3DBuffer MnModel::GetVertexBuffer() const
{
	return m_vertexBuffer.GetBuffer();
}
UINT MnModel::GetVertexBufferStride() const
{
	return m_vertexBuffer.GetStride();
}
const CPD3DBuffer MnModel::GetIndexBuffer() const
{
	return m_indexBuffer.GetBuffer();
}
UINT MnModel::GetIndexCount() const
{
	return m_indexBuffer.GetIndexCount();
}
DXGI_FORMAT MnModel::GetIndexBufferFormat() const
{
	return m_indexBuffer.GetFormat();
}