#include "SkinnedMeshShaderPath.h"
#include <memory>

using namespace MNL;
using namespace DirectX::SimpleMath;

SkinnedMeshShaderPath::SkinnedMeshShaderPath()
{
}

SkinnedMeshShaderPath::~SkinnedMeshShaderPath()
{
}

/*
I should replace this process to data driven with factory pattern
*/
HRESULT SkinnedMeshShaderPath::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	HRESULT result = _InitShaders(cpDevice, L"skinnedvertexshader.hlsl", L"skinnedpixelshader.hlsl");
	if (FAILED(result))
	{
		return result;
	}

	result = _InitInputLayout(cpDevice, GetMnVertexShader(), spVertexType);
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