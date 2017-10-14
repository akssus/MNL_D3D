#include "MnRasterizerState.h"
#include "MnLog.h"

using namespace MNL;

MnRasterizerState::MnRasterizerState()
{
	ZeroMemory(&m_rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
}


MnRasterizerState::~MnRasterizerState()
{
}

HRESULT MnRasterizerState::Init(CPD3DDevice cpDevice, D3D11_FILL_MODE fillMode, bool isCCW)
{
	ZeroMemory(&m_rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	m_rasterizerDesc.FrontCounterClockwise = isCCW;
	m_rasterizerDesc.FillMode = fillMode;
	m_rasterizerDesc.AntialiasedLineEnable = false;
	m_rasterizerDesc.CullMode = D3D11_CULL_BACK;
	m_rasterizerDesc.DepthBias = 0;
	m_rasterizerDesc.DepthBiasClamp = 0.0f;
	m_rasterizerDesc.DepthClipEnable = true;
	m_rasterizerDesc.MultisampleEnable = false;
	m_rasterizerDesc.ScissorEnable = false;
	m_rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	HRESULT result = cpDevice->CreateRasterizerState(&m_rasterizerDesc, m_cpRasterizerState.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpRasterizerState));
		return result;
	}

	return S_OK;
}

const CPD3DRasterizerState MnRasterizerState::GetState() const
{
	return m_cpRasterizerState;
}