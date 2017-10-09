#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnLog.h"
#include "Core/MnConstantBuffer.h"
#include "MnLightSource.h"

namespace MNL
{
	class MnLightBuffer : public MnConstantBuffer
	{
		struct _LightBufferType
		{
			DirectX::SimpleMath::Vector4 lightPos;
			DirectX::SimpleMath::Vector4 lightDir;
			UINT lightType;
			DirectX::SimpleMath::Vector3  padding;
		};
	public:
		MnLightBuffer();
		~MnLightBuffer();

		HRESULT Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong);

		void SetLight(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType);
		void SetLight(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnLightSource> spLight);
	};
}