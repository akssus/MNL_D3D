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
	return S_OK;
}

void MnRenderAPI::SetVertexBuffer(const CPD3DBuffer& vertexBuffer, UINT stride, UINT offset)
{
	m_pD3DDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
}
void MnRenderAPI::SetVertexBuffer(const MnVertexBuffer& vertexBuffer)
{
	UINT stride = vertexBuffer.GetStride();
	UINT offset = 0;
	SetVertexBuffer(vertexBuffer.GetBuffer(),stride,offset);
}
void MnRenderAPI::SetIndexBuffer(const CPD3DBuffer& indexBuffer,DXGI_FORMAT format)
{
	m_pD3DDevice->GetDeviceContext()->IASetIndexBuffer(indexBuffer.Get(), format, 0);
}
void MnRenderAPI::SetIndexBuffer(const MnIndexBuffer& indexBuffer)
{
	SetIndexBuffer(indexBuffer.GetBuffer().Get(), indexBuffer.GetFormat());
}
void MnRenderAPI::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology)
{
	m_pD3DDevice->GetDeviceContext()->IASetPrimitiveTopology(primitiveTopology);
}
void MnRenderAPI::SetInputLayout(const CPD3DInputLayout& inputLayout)
{
	m_pD3DDevice->GetDeviceContext()->IASetInputLayout(inputLayout.Get());
}
void MnRenderAPI::SetVertexShader(const CPD3DVertexShader& vertexShader)
{
	m_pD3DDevice->GetDeviceContext()->VSSetShader(vertexShader.Get(),nullptr,0);
}
void MnRenderAPI::SetPixelShader(const CPD3DPixelShader& cpPixelShader)
{
	m_pD3DDevice->GetDeviceContext()->PSSetShader(cpPixelShader.Get(),nullptr,0);
}
void MnRenderAPI::SetConstantBufferVS(const CPD3DBuffer& cpConstantBuffer, UINT index)
{
	m_pD3DDevice->GetDeviceContext()->VSSetConstantBuffers(index, 1, cpConstantBuffer.GetAddressOf());
}
void MnRenderAPI::SetConstantBufferPS(const CPD3DBuffer& cpConstantBuffer, UINT index)
{
	m_pD3DDevice->GetDeviceContext()->PSSetConstantBuffers(index, 1, cpConstantBuffer.GetAddressOf());
}
void MnRenderAPI::SetRenderTarget(const CPD3DRenderTargetView& cpRenderTargetView, const CPD3DDepthStencilView& cpDepthStencilView)
{
	//m_pD3DDevice->GetDeviceContext()->OMSetRenderTargets(0, nullptr, cpDepthStencilView.Get());
	//m_pD3DDevice->GetDeviceContext()->OMSetRenderTargets(1, cpRenderTargetView.GetAddressOf(),nullptr);
	m_pD3DDevice->GetDeviceContext()->OMSetRenderTargets(1, cpRenderTargetView.GetAddressOf(), cpDepthStencilView.Get());
}

void MnRenderAPI::SetDepthStencilState(const CPD3DDepthStencilState& cpDepthStencilState)
{
	m_pD3DDevice->GetDeviceContext()->OMSetDepthStencilState(cpDepthStencilState.Get(), 1);
}
void MnRenderAPI::SetRasterizerState(const CPD3DRasterizerState& cpRasterizerState)
{
	m_pD3DDevice->GetDeviceContext()->RSSetState(cpRasterizerState.Get());
}

void MnRenderAPI::SetViewport(const D3D11_VIEWPORT& viewport)
{
	m_pD3DDevice->GetDeviceContext()->RSSetViewports(1, &viewport);
}
/*

*/
void MnRenderAPI::ClearRenderTargets(CPD3DRenderTargetView renderTargetView, CPD3DDepthStencilView depthStencilView, Vector4 color)
{
	float color4f[4] = { color.x, color.y, color.z, color.w };
	m_pD3DDevice->GetDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), color4f);
	m_pD3DDevice->GetDeviceContext()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void MnRenderAPI::DrawIndexed(UINT indexCount)
{
	m_pD3DDevice->GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
}
void MnRenderAPI::DrawIndexed(UINT indexCount,UINT indexOffset, UINT vertexBase)
{
	m_pD3DDevice->GetDeviceContext()->DrawIndexed(indexCount, indexOffset, vertexBase);
}


/***************************
*Getters
****************************/
const CPD3DDevice MnRenderAPI::GetD3DDevice() const
{
	return m_pD3DDevice->GetDevice();
}
const CPD3DDeviceContext MnRenderAPI::GetD3DDeviceContext() const
{
	return m_pD3DDevice->GetDeviceContext();
}