#pragma once
#include <d3d11.h>
#include <vector>
#include "MnGpuBuffer.h"
#include "MnCustomVertexType.h"

namespace MNL
{
	class MnVertexBuffer
	{
	public:
		MnVertexBuffer();
		~MnVertexBuffer();

		void Init(const MnCustomVertexType& vertexType,UINT vertexCount, const D3D11_SUBRESOURCE_DATA* initialData, bool isDynamic);
		void UpdateBuffer(const D3D11_SUBRESOURCE_DATA* data);
		bool IsDynamic();
		

	private:
		MnGpuBuffer		m_buffers;
	};
}