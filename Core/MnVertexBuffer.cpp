#include "MnVertexBuffer.h"

using namespace MNL;

MnVertexBuffer::MnVertexBuffer():m_isDynamic(false),m_stride(0)
{
	ZeroMemory(&m_bufferDesc, sizeof(D3D11_BUFFER_DESC));
}


MnVertexBuffer::~MnVertexBuffer()
{
}

HRESULT MnVertexBuffer::Init(CPD3DDevice cpDevice,const std::shared_ptr<MnCustomVertexType>& spVertexType, UINT vertexCount, const D3D11_SUBRESOURCE_DATA* initialData, bool isDynamic)
{
	m_stride = spVertexType->TotalByteSize();
	m_isDynamic = isDynamic;

	ZeroMemory(&m_bufferDesc, sizeof(D3D11_BUFFER_DESC));
	m_bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_bufferDesc.ByteWidth = m_stride * vertexCount;
	if (isDynamic)
	{
		m_bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	}
	else
	{
		m_bufferDesc.CPUAccessFlags = 0;
		m_bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	m_bufferDesc.MiscFlags = 0;
	m_bufferDesc.StructureByteStride = 0;

	HRESULT result = m_buffer.Init(cpDevice, m_bufferDesc, initialData);
	if (FAILED(result))
	{
		return E_FAIL;
	}

	return S_OK;
}
void MnVertexBuffer::UpdateBuffer(CPD3DDeviceContext cpDeviceContext,const D3D11_SUBRESOURCE_DATA& data)
{
	m_buffer.UpdateBuffer(cpDeviceContext, data);
}

const CPD3DBuffer MnVertexBuffer::GetBuffer() const
{
	return m_buffer.GetBuffer();
}

bool MnVertexBuffer::IsDynamic() const
{
	return m_buffer.IsDynamic();
}

UINT MnVertexBuffer::GetStride() const
{
	return m_stride;
}