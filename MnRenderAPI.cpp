#include "MnRenderAPI.h"
#include <memory>


using namespace DirectX::SimpleMath;
using namespace MNL;

MnRenderAPI::MnRenderAPI()
{
}


MnRenderAPI::~MnRenderAPI()
{
}

HRESULT MnRenderAPI::Init(const MnHardware& hardwareInfo, bool useDefaultAdapter)
{
	m_pD3DDevice = std::make_shared<MnD3DDevice>();
	HRESULT result = m_pD3DDevice->Init(hardwareInfo, useDefaultAdapter);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
}

void MnRenderAPI::SetVertexBuffer(const MnVertexBuffer& vertexBuffer)
{
	UINT stride = vertexBuffer.GetStride();
	UINT offset = 0;
	m_pD3DDevice->GetDeviceContext()->IASetVertexBuffers(0,1,vertexBuffer.GetBuffer().GetAddressOf(),&stride,&offset);
}
void MnRenderAPI::SetIndexBuffer(const MnIndexBuffer& indexBuffer)
{
	m_pD3DDevice->GetDeviceContext()->IASetIndexBuffer(indexBuffer.GetBuffer().Get(),indexBuffer.GetFormat(),0);
}

void MnRenderAPI::SetInputLayout(const MnInputLayout& inputLayout)
{
	m_pD3DDevice->GetDeviceContext()->IASetInputLayout(inputLayout.GetInputLayout().Get());
}
void MnRenderAPI::SetVertexShader(const MnVertexShader& vertexShader)
{
	m_pD3DDevice->GetDeviceContext()->VSSetShader(vertexShader.GetShader().Get(),nullptr,0);
}
void MnRenderAPI::SetPixelShader(const MnPixelShader& pixelShader)
{
	m_pD3DDevice->GetDeviceContext()->PSSetShader(pixelShader.GetShader().Get(),nullptr,0);
}

void MnRenderAPI::SetRenderTarget(const CPD3DRenderTargetView cpRenderTargetView, const CPD3DDepthStencilView cpDepthStencilView)
{
	m_pD3DDevice->GetDeviceContext()->OMSetRenderTargets(1, cpRenderTargetView.GetAddressOf(), cpDepthStencilView.Get());
}

void MnRenderAPI::SetDepthStencilState(const CPD3DDepthStencilState cpDepthStencilState)
{
	m_pD3DDevice->GetDeviceContext()->OMSetDepthStencilState(cpDepthStencilState.Get(), 1);
}
void MnRenderAPI::SetRasterizerState(const CPD3DRasterizerState cpRasterizerState)
{
	m_pD3DDevice->GetDeviceContext()->RSSetState(cpRasterizerState.Get());
}

void MnRenderAPI::SetViewport(const D3D11_VIEWPORT& viewport)
{
	m_pD3DDevice->GetDeviceContext()->RSSetViewports(0, &viewport);
}
/*

*/
void MnRenderAPI::ClearRenderTargets(CPD3DRenderTargetView renderTargetView, CPD3DDepthStencilView depthStencilView, Vector4 color)
{
	float color4f[4] = { color.x, color.y, color.z, color.w };
	m_pD3DDevice->GetDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), color4f);
	m_pD3DDevice->GetDeviceContext()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}


/***************************
*Getters
****************************/
const std::shared_ptr<MnD3DDevice> MnRenderAPI::GetD3DDevice() const
{
	return m_pD3DDevice;
}