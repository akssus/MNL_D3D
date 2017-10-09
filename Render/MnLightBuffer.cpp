#include "MnLightBuffer.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnLightBuffer::MnLightBuffer()
{
}


MnLightBuffer::~MnLightBuffer()
{
}


HRESULT MnLightBuffer::Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong)
{
	auto lightBufferType = std::make_shared<MnConstantBufferType>();
	assert(lightBufferType != nullptr);
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_UINT));
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT3));//padding

	HRESULT result = MnConstantBuffer::Init(cpDevice, lightBufferType, registerSlot, bufferBelong);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnLightBuffer));
		return result;
	}
	return result;
}

void MnLightBuffer::SetLight(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType)
{
	_LightBufferType bufferType;
	bufferType.lightPos = Vector4(lightPos);
	bufferType.lightDir = Vector4(lightDir);
	bufferType.lightType = lightType;
	bufferType.padding = Vector3(0.0f, 0.0f, 0.0f);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	this->UpdateBuffer(cpDeviceContext, data);
}

void MnLightBuffer::SetLight(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnLightSource> spLight)
{
	SetLight(cpDeviceContext, spLight->GetPosition(), spLight->GetDirection(), spLight->GetLightType());
}