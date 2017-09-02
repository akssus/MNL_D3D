#include "MnIndexBuffer.h"

using namespace MNL;

MnIndexBuffer::MnIndexBuffer()
{
}


MnIndexBuffer::~MnIndexBuffer()
{
}

HRESULT MnIndexBuffer::Init(CPD3DDevice cpDevice, UINT indexCount, const D3D11_SUBRESOURCE_DATA* initialData)
{
	m_format = DXGI_FORMAT_R32_UINT;
	ZeroMemory(&m_bufferDesc, sizeof(D3D11_BUFFER_DESC));
	m_bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_bufferDesc.ByteWidth = sizeof(UINT) * indexCount;
	m_bufferDesc.CPUAccessFlags = 0;
	m_bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_bufferDesc.MiscFlags = 0;
	m_bufferDesc.StructureByteStride = 0;

	HRESULT result = m_buffer.Init(cpDevice, m_bufferDesc, initialData);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	return S_OK;
}

const CPD3DBuffer MnIndexBuffer::GetBuffer() const
{
	return m_buffer.GetBuffer();
}
const DXGI_FORMAT MnIndexBuffer::GetFormat() const
{
	return m_format;
}