#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	/*
	* MnGpuBuffer allocates video ram memory
	*/
	class MnGpuBuffer
	{
	public:
		MnGpuBuffer();
		~MnGpuBuffer();

		HRESULT Init(const CPD3DDevice& cpDevice, const D3D11_BUFFER_DESC& bufferDesc, const D3D11_SUBRESOURCE_DATA* initialData);
		D3D11_MAPPED_SUBRESOURCE MnGpuBuffer::Map(const CPD3DDeviceContext& cpDeviceContext, UINT subresourceIndex);
		void Unmap(const CPD3DDeviceContext& cpDeviceContext, UINT subresourceIndex);
		void UpdateBuffer(CPD3DDeviceContext cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data);

		const CPD3DBuffer GetBuffer() const;
		UINT GetBufferByteSize() const;
		bool IsDynamic() const;

	protected:
		D3D11_BUFFER_DESC	m_bufferDesc;
		CPD3DBuffer			m_cpBuffer;
		UINT				m_numBuffers;
		UINT				m_bufferSize;
		bool				m_isDynamic;
	};
}