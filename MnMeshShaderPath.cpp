#include "MnMeshShaderPath.h"

using namespace MNL;

MnMeshShaderPath::MnMeshShaderPath()
{
}

MnMeshShaderPath::~MnMeshShaderPath()
{
}

HRESULT MnMeshShaderPath::_InitConstantBuffers(const CPD3DDevice& cpDevice)
{
	//add world transformation buffer, index 0
	auto worldBufferType = std::make_shared<MnConstantBufferType>();
	worldBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	auto worldBuffer = std::make_shared<MnConstantBuffer>();

	HRESULT result = worldBuffer->Init(cpDevice, worldBufferType, 0, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	AddConstantBuffer(worldBuffer);

	//add viewProjectionBuffer, index 1
	auto viewProjectionBufferType = std::make_shared<MnConstantBufferType>();
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	auto viewProjectionBuffer = std::make_shared<MnConstantBuffer>();

	result = viewProjectionBuffer->Init(cpDevice, viewProjectionBufferType, 1, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	AddConstantBuffer(viewProjectionBuffer);

	//add light buffer, index 2
	auto lightBufferType = std::make_shared<MnConstantBufferType>();
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));

	auto lightBuffer = std::make_shared<MnConstantBuffer>();

	result = lightBuffer->Init(cpDevice, lightBufferType, 2, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	AddConstantBuffer(lightBuffer);
	
	//add material buffer to pixel shader, index 3
	auto materialBufferType = std::make_shared<MnConstantBufferType>();
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));

	auto materialBuffer = std::make_shared<MnConstantBuffer>();

	result = materialBuffer->Init(cpDevice, materialBufferType, 0, MN_CONSTANT_BUFFER_BELONG_PS);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	AddConstantBuffer(materialBuffer);


	return S_OK;
}