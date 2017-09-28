#include "MnDepthStencilState.h"
#include "MnLog.h"

using namespace MNL;

MnDepthStencilState::MnDepthStencilState()
{
	ZeroMemory(&m_depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
}


MnDepthStencilState::~MnDepthStencilState()
{
}

HRESULT MnDepthStencilState::Init(CPD3DDevice cpDevice, bool depthEnable, bool stencilEnable)
{
	ZeroMemory(&m_depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	m_depthStencilStateDesc.DepthEnable = depthEnable;
	m_depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	m_depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	m_depthStencilStateDesc.StencilEnable = stencilEnable;
	m_depthStencilStateDesc.StencilReadMask = 0xFF;
	m_depthStencilStateDesc.StencilWriteMask = 0xFF;

	m_depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	m_depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	m_depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	m_depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	m_depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT result = cpDevice->CreateDepthStencilState(&m_depthStencilStateDesc, m_cpDepthStencilState.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_cpDepthStencilState));
		return result;
	}

	return S_OK;
}

const CPD3DDepthStencilState MnDepthStencilState::GetState() const
{
	return m_cpDepthStencilState;
}