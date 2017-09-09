#include "MnShaderPathInstance.h"

using namespace MNL;

MnShaderPathInstance::MnShaderPathInstance()
{
}


MnShaderPathInstance::~MnShaderPathInstance()
{
}


void MnShaderPathInstance::UpdateConstantBuffer(const CPD3DDeviceContext& cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data, UINT constBufferIndex)
{
	auto transformBuffer = GetConstantBuffer(constBufferIndex);
	transformBuffer->UpdateBuffer(cpDeviceContext, data);
}

HRESULT MnShaderPathInstance::_InitShaders(const CPD3DDevice& cpDevice, const std::wstring& vsFileName, const std::wstring& psFileName)
{
	auto vertexShader = std::make_shared<MnVertexShader>();

	HRESULT result = vertexShader->Init(cpDevice, vsFileName.c_str(), "VS_MAIN", "vs_5_0");
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	this->SetVertexShader(vertexShader);

	auto pixelShader = std::make_shared<MnPixelShader>();

	result = pixelShader->Init(cpDevice, psFileName.c_str(), "PS_MAIN", "ps_5_0");
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	this->SetPixelShader(pixelShader);

	return S_OK;
}
HRESULT MnShaderPathInstance::_InitInputLayout(const CPD3DDevice& cpDevice, const std::shared_ptr<MnVertexShader>& spVertexShader, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	auto inputLayout = std::make_shared<MnInputLayout>();
	HRESULT result = inputLayout->Init(cpDevice, spVertexType, spVertexShader);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	this->SetInputLayout(inputLayout);

	return S_OK;
}