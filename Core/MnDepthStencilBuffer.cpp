#include "MnDepthStencilBuffer.h"

using namespace MNL;

MnDepthStencilBuffer::MnDepthStencilBuffer()
{
	ZeroMemory(&m_depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&m_depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
}


MnDepthStencilBuffer::~MnDepthStencilBuffer()
{
}

HRESULT MnDepthStencilBuffer::Init(const CPD3DDevice cpDevice, UINT width, UINT height) 
{
	//create depth stencil buffer
	ZeroMemory(&m_depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	m_depthStencilBufferDesc.ArraySize = 1;
	m_depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_depthStencilBufferDesc.MipLevels = 1;
	m_depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_depthStencilBufferDesc.SampleDesc.Count = 1;
	m_depthStencilBufferDesc.SampleDesc.Quality = 0;
	m_depthStencilBufferDesc.CPUAccessFlags = 0;
	m_depthStencilBufferDesc.MiscFlags = 0;
	m_depthStencilBufferDesc.Width = width;
	m_depthStencilBufferDesc.Height = height;

	HRESULT result = cpDevice->CreateTexture2D(&m_depthStencilBufferDesc, nullptr, m_depthStencilBuffer.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	//create depth stencil buffer view
	ZeroMemory(&m_depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	m_depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	m_depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = cpDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), &m_depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	return S_OK;
}

const CPD3DDepthStencilView& MnDepthStencilBuffer::GetDepthStencilView() const
{
	return m_depthStencilView;
}