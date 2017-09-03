#include "MnTexture2D.h"

using namespace MNL;

MnTexture2D::MnTexture2D()
{
}


MnTexture2D::~MnTexture2D()
{
}

HRESULT MnTexture2D::Init(const CPD3DDevice device, const D3D11_TEXTURE2D_DESC& textureDesc)
{
	m_textureDesc = textureDesc;
	HRESULT result = device->CreateTexture2D(&textureDesc, nullptr, m_cpTexture2D.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}

const CPD3DTexture2D MnTexture2D::GetTexture() const
{
	return m_cpTexture2D;
}