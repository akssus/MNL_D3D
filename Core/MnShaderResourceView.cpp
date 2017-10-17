#include "MnShaderResourceView.h"
#include "MnLog.h"

using namespace MNL;

MnShaderResourceView::MnShaderResourceView()
{
}


MnShaderResourceView::~MnShaderResourceView()
{
}


HRESULT MnShaderResourceView::Init(const CPD3DDevice& cpDevice, const CPD3DTexture2D& cpResource)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	shaderResourceViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	HRESULT result = cpDevice->CreateShaderResourceView(cpResource.Get(), &shaderResourceViewDesc, m_cpShaderResourceView.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpShaderResourceView));
		return result;
	}

	return S_OK;
}


CPD3DShaderResourceView MnShaderResourceView::GetShaderResourceView() const
{
	return m_cpShaderResourceView;
}