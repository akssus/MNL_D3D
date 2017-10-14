#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnLog.h"
#include "Core/MnConstantBuffer.h"
#include "Render/MnMaterial.h"

namespace MNL
{
	class MnMaterialBuffer : public MnConstantBuffer
	{
		struct _MaterialBufferType
		{
			DirectX::SimpleMath::Vector4 diffuse;
			DirectX::SimpleMath::Vector4 ambient;
			DirectX::SimpleMath::Vector4 emissive;
			DirectX::SimpleMath::Vector4 specular;
			float specularPower;
			DirectX::SimpleMath::Vector3 padding;
		};
	public:
		MnMaterialBuffer();
		~MnMaterialBuffer();

		HRESULT Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong);

		void SetMaterial(const CPD3DDeviceContext& cpDeviceContext,
			const DirectX::SimpleMath::Vector4& diffuse,
			const DirectX::SimpleMath::Vector4& ambient,
			const DirectX::SimpleMath::Vector4& emissive,
			const DirectX::SimpleMath::Vector4& specular,
			float specularPower);
		void SetMaterial(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnMaterial> spMaterial);
	};
}