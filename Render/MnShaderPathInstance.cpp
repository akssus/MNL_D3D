#include "MnShaderPathInstance.h"

using namespace MNL;

MnShaderPathInstance::MnShaderPathInstance()
{
}


MnShaderPathInstance::~MnShaderPathInstance()
{
}

HRESULT MnShaderPathInstance::_InitShaders(const CPD3DDevice& cpDevice, const std::wstring& vsFileName, const std::wstring& psFileName)
{
	auto vertexShader = std::make_shared<MnVertexShader>();

	HRESULT result = vertexShader->Init(cpDevice, vsFileName.c_str(), "VS_MAIN", "vs_5_0");
	if (FAILED(result))
	{
		//error log
		return result;
	}

	this->SetVertexShader(vertexShader);

	auto pixelShader = std::make_shared<MnPixelShader>();

	result = pixelShader->Init(cpDevice, psFileName.c_str(), "PS_MAIN", "ps_5_0");
	if (FAILED(result))
	{
		//error log
		return result;
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
		return result;
	}

	this->SetInputLayout(inputLayout);

	return S_OK;
}

HRESULT MnShaderPathInstance::_InitSamplerState(const CPD3DDevice& cpDevice)
{
	auto samplerState = std::make_shared<MnSamplerState>();
	HRESULT result = samplerState->Init(cpDevice);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	this->SetSamplerState(samplerState);
	return S_OK;
}