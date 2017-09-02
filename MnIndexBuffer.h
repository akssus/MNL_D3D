#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	class MnIndexBuffer
	{
	public:
		MnIndexBuffer();
		~MnIndexBuffer();
		HRESULT Init(CPD3DDevice cpDevice, UINT indexCount, const D3D11_SUBRESOURCE_DATA* initialData);

		const CPD3DBuffer GetBuffer() const;

	private:
		MnGpuBuffer			m_buffer;
		D3D11_BUFFER_DESC	m_bufferDesc;
		UINT				m_indexCount;
	};
}