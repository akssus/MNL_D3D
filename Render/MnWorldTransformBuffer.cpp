#include "MnWorldTransformBuffer.h"

using namespace MNL;

MnWorldTransformBuffer::MnWorldTransformBuffer()
{
}


MnWorldTransformBuffer::~MnWorldTransformBuffer()
{
}


HRESULT MnWorldTransformBuffer::Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong)
{
	auto worldBufferType = std::make_shared<MnConstantBufferType>();
	assert(worldBufferType != nullptr);
	worldBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	//world buffer is index 0 of vertex shader
	HRESULT result = MnConstantBuffer::Init(cpDevice, worldBufferType, registerSlot, bufferBelong);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnWorldTransformBuffer));
		return result;
	}
	return result;
}

void MnWorldTransformBuffer::SetWorldTransform(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Matrix& matWorld)
{
	//row major to column major
	_WorldBufferType bufferType;
	bufferType.matWorld = matWorld.Transpose();

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	this->UpdateBuffer(cpDeviceContext, data);
}