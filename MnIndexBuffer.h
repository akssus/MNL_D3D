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
		/*
		Initialize index buffer. index format is DXGI_FORMAT_R32_UINT fixed
		*/
		HRESULT Init(CPD3DDevice cpDevice, UINT indexCount, const D3D11_SUBRESOURCE_DATA* initialData);

		const CPD3DBuffer GetBuffer() const;
		const DXGI_FORMAT GetFormat() const;

	private:
		MnGpuBuffer			m_buffer;
		D3D11_BUFFER_DESC	m_bufferDesc;
		DXGI_FORMAT			m_format;
		UINT				m_indexCount;
	};
}