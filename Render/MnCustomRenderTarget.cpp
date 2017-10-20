#include "MnCustomRenderTarget.h"

using namespace MNL;

MnCustomRenderTarget::MnCustomRenderTarget()
{
}


MnCustomRenderTarget::~MnCustomRenderTarget()
{
}

HRESULT MnCustomRenderTarget::Init(const CPD3DDevice& cpDevice, float textureWidth, float textureHeight)
{
	//����Ÿ�ٿ� ���� ����
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.Width = static_cast<UINT>(textureWidth);
	texDesc.Height = static_cast<UINT>(textureHeight);
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT result = m_renderedTexture.Init(cpDevice, texDesc);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_renderedTexture));
		return result;
	}

	//����Ÿ�ٺ� ����
	auto renderTargetViewDesc = std::make_shared<D3D11_RENDER_TARGET_VIEW_DESC>();
	ZeroMemory(renderTargetViewDesc.get(), sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	renderTargetViewDesc->Format = texDesc.Format;
	renderTargetViewDesc->Texture2D.MipSlice = 0;
	renderTargetViewDesc->ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	result = m_renderTargetView.Init(cpDevice, m_renderedTexture.GetTexture(), renderTargetViewDesc);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_renderTargetView));
		return result;
	}

	//���̴� ���ҽ� �� ����
	result = m_shaderResourceView.Init(cpDevice, m_renderedTexture.GetTexture(), texDesc.Format);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_shaderResourceView));
		return result;
	}

	//�������ٽ� �� ����
	result = m_depthStencilBuffer.Init(cpDevice, static_cast<UINT>(textureWidth), static_cast<UINT>(textureHeight));
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_depthStencilBuffer));
		return result;
	}

	return result;
}

void MnCustomRenderTarget::Clear(MnRenderAPI& renderAPI, DirectX::SimpleMath::Color color)
{
	renderAPI.ClearRenderTargets(m_renderTargetView.GetRenderTargetView(), m_depthStencilBuffer.GetDepthStencilView(), color);
}

CPD3DRenderTargetView MnCustomRenderTarget::GetRenderTargetView() const
{
	return m_renderTargetView.GetRenderTargetView();
}

CPD3DDepthStencilView MnCustomRenderTarget::GetDepthStencilView() const
{
	return m_depthStencilBuffer.GetDepthStencilView();
}
CPD3DShaderResourceView MnCustomRenderTarget::GetShaderResourceView() const
{
	return m_shaderResourceView.GetShaderResourceView();
}

void MnCustomRenderTarget::CopyTextureFrom(MnRenderAPI& renderAPI, const MnCustomRenderTarget& other)
{
	m_renderedTexture.CopyFrom(renderAPI.GetD3DDeviceContext(), other.m_renderedTexture);
}