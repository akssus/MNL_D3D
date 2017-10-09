#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnLog.h"
#include "Core/MnConstantBuffer.h"

namespace MNL
{
	class MnViewProjectionTransformBuffer : public MnConstantBuffer
	{
		struct _ViewProjectionBufferType
		{
			DirectX::SimpleMath::Matrix matView;
			DirectX::SimpleMath::Matrix matProjection;
		};
	public:
		MnViewProjectionTransformBuffer();
		~MnViewProjectionTransformBuffer();

		HRESULT Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong);

		void SetViewProjectionTransform(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Matrix& matView, const DirectX::SimpleMath::Matrix& matProjection);
	};
}