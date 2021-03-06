#include "MnConstantBuffer.h"
#include <cassert>

using namespace MNL;

MnConstantBuffer::MnConstantBuffer():m_index(0),m_belong(Mn_CONSTANT_BUFFER_BELONG_NONE)
{
}


MnConstantBuffer::~MnConstantBuffer()
{
}


HRESULT MnConstantBuffer::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnConstantBufferType>& constantBufferType, UINT index, const MN_CONSTANT_BUFFER_BELONG& constantBufferBelong)
{
	m_index = index;
	m_belong = constantBufferBelong;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = constantBufferType->PaddedByteSize();
	bufferDesc.CPUAccessFlags = 0;// D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT result = m_buffer.Init(cpDevice, bufferDesc, nullptr);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	return S_OK;
}
void MnConstantBuffer::UpdateBuffer(CPD3DDeviceContext cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data)
{
	m_buffer.UpdateBuffer(cpDeviceContext, data);
}

const CPD3DBuffer MnConstantBuffer::GetBuffer() const
{
	return m_buffer.GetBuffer();
}
UINT MnConstantBuffer::GetBufferByteSize() const
{
	return m_buffer.GetBufferByteSize();
}

UINT MnConstantBuffer::GetIndex() const
{
	return m_index;
}

MN_CONSTANT_BUFFER_BELONG MnConstantBuffer::GetBelong() const
{
	return m_belong;
}