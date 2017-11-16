#include "MnBonePaletteBuffer.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBonePaletteBuffer::MnBonePaletteBuffer()
{
}


MnBonePaletteBuffer::~MnBonePaletteBuffer()
{
}


HRESULT MnBonePaletteBuffer::Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong)
{
	auto bufferType = std::make_shared<MnConstantBufferType>();
	assert(bufferType != nullptr);

	//this is bullshit, please find other way later
	for (UINT i = 0; i < MN_BONE_PALETTE_SIZE; ++i)
	{
		bufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	}

	HRESULT result = MnConstantBuffer::Init(cpDevice, bufferType, registerSlot, bufferBelong);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnBonePaletteBuffer));
		return result;
	}
	return result;
}

void MnBonePaletteBuffer::SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const D3D11_SUBRESOURCE_DATA bonePalette)
{
	this->UpdateBuffer(cpDeviceContext, bonePalette);
}

void MnBonePaletteBuffer::SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnSkeleton> spSkeleton)
{
	SetBonePalette(cpDeviceContext, spSkeleton->GetBonePalette());
}