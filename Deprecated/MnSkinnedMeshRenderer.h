#pragma once
#include <d3d11.h>
#include "MnRenderer.h"
#include "MnLightSource.h"
#include "MnMaterial.h"
#include "MnSkeleton.h"
#include "MnWorldTransformBuffer.h"
#include "MnViewProjectionTransformBuffer.h"
#include "MnLightBuffer.h"
#include "MnMaterialBuffer.h"
#include "MnBonePaletteBuffer.h"

namespace MNL
{
	/*
	It contains world, view, projectoin matrix, light, material.
	나중에 이것들 전부 컴포넌트화 시킬것
	*/
	class MnSkinnedMeshRenderer : public MnRenderer
	{
	private:
		/**
		@brief 열거형의 값이 레지스터 슬롯으로 고정된다. 예를들어 _CONST_BUF_LIGHT 는 VS 및 PS에서 모두 register(b2)에 바인딩된다.
		*/
		enum _CONST_BUFFERS
		{
			_CONST_BUF_WORLD,  //register(b0)
			_CONST_BUF_VIEWPROJECTION, //register(b1)
			_CONST_BUF_LIGHT, //register(b2)
			_CONST_BUF_MATERIAL, //register(b3)
			_CONST_BUF_BONE_PALETTE, //register(b4)
			_CONST_BUF_TOTAL 
		};

	public:
		MnSkinnedMeshRenderer();
		~MnSkinnedMeshRenderer();
		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType);

		void SetWorldBuffer(const CPD3DDeviceContext& cpDeviceContext,
			const DirectX::SimpleMath::Matrix& matWorld);

		void SetViewProjectionBuffer(const CPD3DDeviceContext& cpDeviceContext,
			const DirectX::SimpleMath::Matrix& matView,
			const DirectX::SimpleMath::Matrix& matProjection);

		void SetLightBuffer(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType);
		void SetLightBuffer(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnLightSource> spLight);

		void SetMaterial(const CPD3DDeviceContext& cpDeviceContext,
			const DirectX::SimpleMath::Vector4& diffuse,
			const DirectX::SimpleMath::Vector4& ambient,
			const DirectX::SimpleMath::Vector4& emissive,
			const DirectX::SimpleMath::Vector4& specular,
			float specularPower);
		void SetMaterial(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnMaterial> spMaterial);

		void SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnSkeleton> spSkeleton);
		void SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const D3D11_SUBRESOURCE_DATA bonePalette);

	private:
		HRESULT _InitConstantBuffers(const CPD3DDevice& cpDevice);
		HRESULT _InitWolrdBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitViewProjectionBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitLightBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitMaterialBuffer(const CPD3DDevice& cpDevice);
		HRESULT _InitBonePaletteBuffer(const CPD3DDevice& cpDevice);

	private:
		std::shared_ptr<MnWorldTransformBuffer> m_spWorldBuffer;
		std::shared_ptr<MnViewProjectionTransformBuffer> m_spViewProjectionBuffer;
		std::shared_ptr<MnLightBuffer> m_spLightBuffer;
		std::shared_ptr<MnMaterialBuffer> m_spMaterialBuffer;
		std::shared_ptr<MnBonePaletteBuffer> m_spBonePaletteBuffer;
	};
}