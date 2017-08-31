#pragma once
#include <d3d11.h>
#include "MNL.h"

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

		CPD3DBuffer GetBuffer();
		bool IsDynamic();

	protected:
		bool AllocateBuffer(const D3D11_BUFFER_DESC* bufferDesc, const D3D11_SUBRESOURCE_DATA* initialData);

	protected:
		CPD3DBuffer m_cpBuffer;
		bool			m_isDynamic;
	};
}