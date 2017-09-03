#pragma once
#include <d3d11.h>
#include <vector>
#include "MnTypedefs.h"
#include "MnGpuBuffer.h"
#include "MnCustomVertexType.h"

namespace MNL
{
	class MnVertexBuffer
	{
	public:
		MnVertexBuffer();
		~MnVertexBuffer();

		HRESULT Init(CPD3DDevice cpDevice, const MnCustomVertexType& vertexType, UINT vertexCount, const D3D11_SUBRESOURCE_DATA* initialData, bool isDynamic);
		void UpdateBuffer(CPD3DDeviceContext cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data);

		const CPD3DBuffer GetBuffer() const;
		bool IsDynamic() const;
		UINT GetStride() const;
		

	private:
		MnGpuBuffer			m_buffer;
		UINT				m_stride;
		D3D11_BUFFER_DESC	m_bufferDesc;
		bool				m_isDynamic;
	};
}