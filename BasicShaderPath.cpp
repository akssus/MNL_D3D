#include "BasicShaderPath.h"
#include <memory>

using namespace MNL;
using namespace DirectX::SimpleMath;

BasicShaderPath::BasicShaderPath()
{
}


BasicShaderPath::~BasicShaderPath()
{
}

HRESULT BasicShaderPath::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	HRESULT result = _InitShaders(cpDevice,L"vertexshader.hlsl",L"pixelshader.hlsl");
	if (FAILED(result))
	{
		return result;
	}

	result = _InitInputLayout(cpDevice, GetMnVertexShader(),spVertexType);
	if (FAILED(result))
	{
		return result;
	}

	result = _InitSamplerState(cpDevice);
	if (FAILED(result))
	{
		return result;
	}

	return S_OK;
}