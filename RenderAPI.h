#pragma once
#include <d3d11.h>
#include <memory>
#include "MNL.h"

namespace MNL
{
	/*
	* RenderAPI class is responsible for organizing rendering pipelines with D3D device
	*/
	class RenderAPI
	{
	public:
		RenderAPI();
		~RenderAPI();

		void SetVertexBuffer(const std::shared_ptr<MnVertexBuffer> cpVertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<MnIndexBuffer> cpIndexBuffer);

		void SetInputLayout(const std::shared_ptr<MnInputLayout> cpInputLayout);
		void SetVertexShader(const std::shared_ptr<MnVertexShader> cpVertexShader);
		void SetPixelShader(const std::shared_ptr<MnPixelShader> cpPixelShader);

		void SetRenderTarget(const CPD3DRenderTargetView cpRenderTargetView, const CPD3DDepthStencilView cpDepthStencilView);

		void SetDepthStencilState(const CPD3DDepthStencilState cpDepthStencilState);
		void SetRasterizerState(const CPD3DRasterizerState cpRasterizerState);
		
		void SetViewport(const D3D11_VIEWPORT& viewport);


	private:
		CPD3DDevice			m_pDevice;
		CPD3DDeviceContext	m_pDeviceContext;
	};
}