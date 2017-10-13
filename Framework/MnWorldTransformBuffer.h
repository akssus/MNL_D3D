#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnLog.h"
#include "Core/MnConstantBuffer.h"

namespace MNL
{
	class MnWorldTransformBuffer : public MnConstantBuffer
	{
		struct _WorldBufferType
		{
			DirectX::SimpleMath::Matrix matWorld;
		};
	public:
		MnWorldTransformBuffer();
		~MnWorldTransformBuffer();

		HRESULT Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong);

		void SetWorldTransform(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Matrix& worldTransform);
	};
}