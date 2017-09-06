#include "BasicShaderPath.h"
#include "UniversalVertexType.h"
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
	HRESULT result = _InitConstantBuffers(cpDevice);
	if (FAILED(result))
	{
		return E_FAIL;
	}

	result = _InitShaders(cpDevice);
	if (FAILED(result))
	{
		return E_FAIL;
	}

	result = _InitInputLayout(cpDevice, GetMnVertexShader(),spVertexType);
	if (FAILED(result))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT BasicShaderPath::_InitConstantBuffers(const CPD3DDevice& cpDevice)
{
	auto transformBufferType = std::make_shared<MnConstantBufferType>();
	assert(transformBufferType != nullptr);
	transformBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	transformBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	transformBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	auto transformBuffer = std::make_shared<MnConstantBuffer>();
	assert(transformBuffer != nullptr);

	//transform buffer is index 0 of vertex shader
	HRESULT result = transformBuffer->Init(cpDevice, transformBufferType, 0, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	AddConstantBuffer(transformBuffer);

	return S_OK;
}
HRESULT BasicShaderPath::_InitShaders(const CPD3DDevice& cpDevice)
{
	auto vertexShader = std::make_shared<MnVertexShader>();
	assert(vertexShader != nullptr);
	HRESULT result = vertexShader->Init(cpDevice, L"vertexshader.hlsl", "VS_MAIN", "vs_5_0");
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	this->SetVertexShader(vertexShader);

	auto pixelShader = std::make_shared<MnPixelShader>();
	assert(pixelShader != nullptr);
	result = pixelShader->Init(cpDevice, L"pixelshader.hlsl", "PS_MAIN", "ps_5_0");
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	
	this->SetPixelShader(pixelShader);

	return S_OK;
}
HRESULT BasicShaderPath::_InitInputLayout(const CPD3DDevice& cpDevice, const std::shared_ptr<MnVertexShader>& spVertexShader, const std::shared_ptr<MnCustomVertexType>& spVertexType)
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

void BasicShaderPath::SetTransformBuffer(const CPD3DDeviceContext& cpDeviceContext, 
	const DirectX::SimpleMath::Matrix& matWorld, 
	const DirectX::SimpleMath::Matrix& matView, 
	const DirectX::SimpleMath::Matrix& matProjection)
{
	//row major to column major
	_TransformBufferType bufferType;
	bufferType.matProjection = matProjection.Transpose();;
	bufferType.matWorld = matWorld.Transpose();
	bufferType.matView = matView.Transpose();

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	auto transformBuffer = GetConstantBuffer(0);
	transformBuffer->UpdateBuffer(cpDeviceContext, data);
}