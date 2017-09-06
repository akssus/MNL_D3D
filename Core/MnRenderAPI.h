#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <memory>
#include "MnTypedefs.h"
#include "MnVertexBuffer.h"
#include "MnIndexBuffer.h"
#include "MnInputLayout.h"
#include "MnPixelShader.h"
#include "MnVertexShader.h"
#include "MnHardware.h"
#include "MnD3DDevice.h"

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

		/**
		Set vertex buffer to the context. only supports one buffer
		*/
		void SetVertexBuffer(const CPD3DBuffer& vertexBuffer, UINT stride, UINT offset);
		void SetVertexBuffer(const MnVertexBuffer& vertexBuffer);
		/**
		Set index buffer to the context
		*/
		void SetIndexBuffer(const CPD3DBuffer& indexBuffer, DXGI_FORMAT format);
		void SetIndexBuffer(const MnIndexBuffer& indexBuffer);
		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology);

		void SetInputLayout(const CPD3DInputLayout& cpInputLayout);
		void SetVertexShader(const CPD3DVertexShader& cpVertexShader);
		void SetPixelShader(const CPD3DPixelShader& cpPixelShader);
		void SetConstantBufferVS(const CPD3DBuffer& cpConstantBuffer, UINT index);
		void SetConstantBufferPS(const CPD3DBuffer& cpConstantBuffer, UINT index);

		void SetRenderTarget(const CPD3DRenderTargetView& cpRenderTargetView, const CPD3DDepthStencilView& cpDepthStencilView);

		void SetDepthStencilState(const CPD3DDepthStencilState& cpDepthStencilState);
		void SetRasterizerState(const CPD3DRasterizerState& cpRasterizerState);
		
		/**
		It supports only one viewport at the same time
		*/
		void SetViewport(const D3D11_VIEWPORT& viewport);



	public:
		void ClearRenderTargets(CPD3DRenderTargetView renderTargetView, CPD3DDepthStencilView depthStencilView, DirectX::SimpleMath::Vector4 color = DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		/**
		Draw primitives with offset as 0, base vertex location as 0
		*/
		void DrawIndexed(UINT indexCount);

	public:
		const std::shared_ptr<MnD3DDevice> GetD3DDevice() const;

	private:		
		std::shared_ptr<MnD3DDevice>		m_pD3DDevice;
	};
}