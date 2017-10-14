#include "MnSamplerState.h"
#include "MnLog.h"

using namespace MNL;

MnSamplerState::MnSamplerState()
{
}


MnSamplerState::~MnSamplerState()
{
}


HRESULT MnSamplerState::Init(const CPD3DDevice& cpDevice)
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerDesc.BorderColor[0] = samplerDesc.BorderColor[1] = samplerDesc.BorderColor[2] = samplerDesc.BorderColor[3] = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT result = cpDevice->CreateSamplerState(&samplerDesc, m_cpSamplerState.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpSamplerState));
		return result;
	}
	return S_OK;
}

const CPD3DSamplerState MnSamplerState::GetSamplerState() const
{
	return m_cpSamplerState;
}