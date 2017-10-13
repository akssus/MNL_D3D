#include "MnGpuBuffer.h"
#include "MnLog.h"

using namespace MNL;

MnGpuBuffer::MnGpuBuffer():m_bufferSize(0),m_isDynamic(false),m_numBuffers(0)
{
	ZeroMemory(&m_bufferDesc, sizeof(D3D11_BUFFER_DESC));
}


MnGpuBuffer::~MnGpuBuffer()
{
}

HRESULT MnGpuBuffer::Init(const CPD3DDevice& cpDevice, const D3D11_BUFFER_DESC& bufferDesc, const D3D11_SUBRESOURCE_DATA* initialData)
{
	m_bufferSize = bufferDesc.ByteWidth;
	m_bufferDesc = bufferDesc;
	m_isDynamic = (bufferDesc.Usage == D3D11_USAGE_DYNAMIC);
	HRESULT result = cpDevice->CreateBuffer(&bufferDesc, initialData, m_cpBuffer.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpBuffer));
		return result;
	}
	return S_OK;
}
D3D11_MAPPED_SUBRESOURCE MnGpuBuffer::Map(const CPD3DDeviceContext& cpDeviceContext, UINT subresourceIndex)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ZeroMemory(&mappedSubresource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT result = cpDeviceContext->Map(m_cpBuffer.Get(), subresourceIndex, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(Map));
	}
	return mappedSubresource;
}
void MnGpuBuffer::Unmap(const CPD3DDeviceContext& cpDeviceContext, UINT subresourceIndex)
{
	cpDeviceContext->Unmap(m_cpBuffer.Get(), 0);
}
void MnGpuBuffer::UpdateBuffer(CPD3DDeviceContext cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data)
{
	cpDeviceContext->UpdateSubresource(m_cpBuffer.Get(), 0, nullptr, data.pSysMem, data.SysMemPitch, data.SysMemSlicePitch);
}
UINT MnGpuBuffer::GetBufferByteSize() const
{
	return m_bufferSize;
}

const CPD3DBuffer MnGpuBuffer::GetBuffer() const
{
	return m_cpBuffer;
}
bool MnGpuBuffer::IsDynamic() const
{
	return m_isDynamic;
}