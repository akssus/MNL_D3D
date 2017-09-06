#pragma once
#include <d3d11.h>
#include "DXTK/SimpleMath.h"
#include "Utility\MnShaderPath.h"
#include "Core/MnConstantBuffer.h"

namespace MNL
{
	class BasicShaderPath : public MnShaderPath
	{
	private:
		struct _TransformBufferType
		{
			DirectX::SimpleMath::Matrix matWorld;
			DirectX::SimpleMath::Matrix matView;
			DirectX::SimpleMath::Matrix matProjection;
		};
	public:
		BasicShaderPath();
		~BasicShaderPath();
		HRESULT Init(const CPD3DDevice& cpDevice,const std::shared_ptr<MnCustomVertexType>& spVertexType);
		
		void SetTransformBuffer(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Matrix& matWorld, const DirectX::SimpleMath::Matrix& matView, const DirectX::SimpleMath::Matrix& matProjection);


	private:
		HRESULT _InitConstantBuffers(const CPD3DDevice& cpDevice);
		HRESULT _InitShaders(const CPD3DDevice& cpDevice);
		HRESULT _InitInputLayout(const CPD3DDevice& cpDevice, const std::shared_ptr<MnVertexShader>& spVertexShader, const std::shared_ptr<MnCustomVertexType>& spVertexType);

	private:
		//MnConstantBuffer m_transformBuffer;
	};
}
