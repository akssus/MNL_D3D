#pragma once
#include <d3d11.h>
#include "Utility\MnRenderer.h"

namespace MNL
{
	class MnMeshRenderer : public MnRenderer
	{
	private:
		/*
		This enum value equals constance buffer's index
		*/
		enum _CONST_BUFFERS
		{
			_CONST_BUF_WORLD,
			_CONST_BUF_VIEWPROJECTION,
			_CONST_BUF_LIGHT,
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
			DirectX::SimpleMath::Vector3 lightPos;
			DirectX::SimpleMath::Vector3 lightDir;
			DirectX::SimpleMath::Vector2 padding;
		};
		struct _MaterialBufferType
		{
			DirectX::SimpleMath::Vector4 diffuse;
			DirectX::SimpleMath::Vector4 ambient;
			DirectX::SimpleMath::Vector4 specular;
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

	private:
		HRESULT _InitConstantBuffers(const CPD3DDevice& cpDevice);
	};
}