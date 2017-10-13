#pragma once
#include <d3d11.h>
#include "MnRenderer.h"
#include "MnLightSource.h"
#include "MnMaterial.h"

namespace MNL
{
	/*
	It contains world, view, projectoin matrix, light, material.
	나중에 이것들 전부 컴포넌트화 시킬것
	*/
	class MnMeshRenderer : public MnRenderer
	{
	private:
		/*
		This enum value equals constance buffer's index
		Must initialize in order
		*/
		enum _CONST_BUFFERS
		{
			_CONST_BUF_WORLD,
			_CONST_BUF_VIEWPROJECTION,
			_CONST_BUF_LIGHT_VS,
			_CONST_BUF_LIGHT_PS,
			_CONST_BUF_MATERIAL,
			_CONST_BUF_TOTAL
		};
	private:
		struct _WorldBufferType
		{
			DirectX::SimpleMath::Matrix matWorld;
		};
		struct _ViewProjectionBufferType
		{
			DirectX::SimpleMath::Matrix matView;
			DirectX::SimpleMath::Matrix matProjection;
		};
		struct _LightBufferType
		{
			DirectX::SimpleMath::Vector4 lightPos;
			DirectX::SimpleMath::Vector4 lightDir;
			UINT lightType;
			DirectX::SimpleMath::Vector3  padding;
		};
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
		MnMeshRenderer();
		~MnMeshRenderer();
		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType);

		void SetWorldBuffer(MnRenderAPI& renderAPI, 
			const DirectX::SimpleMath::Matrix& matWorld);
		
		void SetViewProjectionBuffer(MnRenderAPI& renderAPI,
			const DirectX::SimpleMath::Matrix& matView,
			const DirectX::SimpleMath::Matrix& matProjection);

		void SetLightBuffer(MnRenderAPI& renderAPI, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType);
		void SetLightBuffer(MnRenderAPI& renderAPI, const std::shared_ptr<MnLightSource> spLight);

		void SetMaterial(MnRenderAPI& renderAPI,
			const DirectX::SimpleMath::Vector4& diffuse,
			const DirectX::SimpleMath::Vector4& ambient,
			const DirectX::SimpleMath::Vector4& emissive,
			const DirectX::SimpleMath::Vector4& specular,
			float specularPower);
		void SetMaterial(MnRenderAPI& renderAPI, const std::shared_ptr<MnMaterial> spMaterial);

	private:
		HRESULT _InitConstantBuffers(const CPD3DDevice& cpDevice);
		HRESULT _InitWolrdBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitViewProjectionBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitLightBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitMaterialBuffer(const CPD3DDevice& cpDevice);
	};
}