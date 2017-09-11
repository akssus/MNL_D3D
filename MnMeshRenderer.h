#pragma once
#include <d3d11.h>
#include "Utility\MnRenderer.h"

namespace MNL
{
	class MnMeshRenderer : public MnRenderer
	{
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
	public:
		MnMeshRenderer();
		~MnMeshRenderer();

		void SetWorldBuffer(const CPD3DDeviceContext& cpDeviceContext, 
			const DirectX::SimpleMath::Matrix& matWorld);
		
		void SetViewProjectionBuffer(const CPD3DDeviceContext& cpDeviceContext,
			const DirectX::SimpleMath::Matrix& matView,
			const DirectX::SimpleMath::Matrix& matProjection);
	};
}