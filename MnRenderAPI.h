#pragma once
#include <d3d11.h>
#include <memory>
#include "MNL.h"

namespace MNL
{
	/*
	* RenderAPI class is responsible for organizing rendering pipelines with D3D device
	*/
	class MnRenderAPI
	{
	public:
		MnRenderAPI();
		~MnRenderAPI();

		HRESULT Init(const MnHardware& hardwareInfo, bool useDefaultAdapter);

		void SetVertexBuffer(const MnVertexBuffer& vertexBuffer);
		void SetIndexBuffer(const MnIndexBuffer& indexBuffer);

		void SetInputLayout(const MnInputLayout& inputLayout);
		void SetVertexShader(const MnVertexShader& vertexShader);
		void SetPixelShader(const MnPixelShader& pixelShader);

		void SetRenderTarget(const CPD3DRenderTargetView cpRenderTargetView, const CPD3DDepthStencilView cpDepthStencilView);

		void SetDepthStencilState(const CPD3DDepthStencilState cpDepthStencilState);
		void SetRasterizerState(const CPD3DRasterizerState cpRasterizerState);
		
		void SetViewport(const D3D11_VIEWPORT& viewport);

		const std::shared_ptr<MnD3DDevice> GetD3DDevice() const;

	private:		
		std::shared_ptr<MnD3DDevice>		m_pD3DDevice;
	};
}