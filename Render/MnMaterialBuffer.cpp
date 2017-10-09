#include "MnMaterialBuffer.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnMaterialBuffer::MnMaterialBuffer()
{
}


MnMaterialBuffer::~MnMaterialBuffer()
{
}


HRESULT MnMaterialBuffer::Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong)
{
	auto materialBufferType = std::make_shared<MnConstantBufferType>();
	assert(materialBufferType != nullptr);
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT1));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT3)); //padding

	HRESULT result = MnConstantBuffer::Init(cpDevice, materialBufferType, registerSlot, bufferBelong);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnMaterialBuffer));
		return result;
	}
	return result;
}

void MnMaterialBuffer::SetMaterial(const CPD3DDeviceContext& cpDeviceContext,
	const DirectX::SimpleMath::Vector4& diffuse,
	const DirectX::SimpleMath::Vector4& ambient,
	const DirectX::SimpleMath::Vector4& emissive,
	const DirectX::SimpleMath::Vector4& specular,
	float specularPower)
{
	_MaterialBufferType bufferType;
	ZeroMemory(&bufferType, sizeof(_MaterialBufferType));
	bufferType.diffuse = diffuse;
	bufferType.ambient = ambient;
	bufferType.emissive = emissive;
	bufferType.specular = specular;
	bufferType.specularPower = specularPower;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	this->UpdateBuffer(cpDeviceContext, data);
}

void MnMaterialBuffer::SetMaterial(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnMaterial> spMaterial)
{
	SetMaterial(cpDeviceContext, spMaterial->diffuse, spMaterial->ambient, spMaterial->emissive, spMaterial->specular, spMaterial->specularPower);
}