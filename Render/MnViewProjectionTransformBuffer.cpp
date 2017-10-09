#include "MnViewProjectionTransformBuffer.h"

using namespace MNL;

MnViewProjectionTransformBuffer::MnViewProjectionTransformBuffer()
{
}


MnViewProjectionTransformBuffer::~MnViewProjectionTransformBuffer()
{
}


HRESULT MnViewProjectionTransformBuffer::Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong)
{
	auto viewProjectionBufferType = std::make_shared<MnConstantBufferType>();
	assert(viewProjectionBufferType != nullptr);
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	//world buffer is index 0 of vertex shader
	HRESULT result = MnConstantBuffer::Init(cpDevice, viewProjectionBufferType, registerSlot, bufferBelong);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnViewProjectionTransformBuffer));
		return result;
	}
	return result;
}

void MnViewProjectionTransformBuffer::SetViewProjectionTransform(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Matrix& matView, const DirectX::SimpleMath::Matrix& matProjection)
{
	//row major to column major
	_ViewProjectionBufferType bufferType;
	bufferType.matView = matView.Transpose();
	bufferType.matProjection = matProjection.Transpose();

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	this->UpdateBuffer(cpDeviceContext, data);
}