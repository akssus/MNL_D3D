#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnLog.h"
#include "Core/MnConstantBuffer.h"
#include "Render/MnSkeleton.h"

namespace MNL
{
	class MnBonePaletteBuffer : public MnConstantBuffer
	{
		/**
		@brief �� �ȷ�Ʈ�� Matrix �迭 192���� �����̴�.
		*/
		struct _BonePaletteBufferType
		{
			DirectX::SimpleMath::Matrix transforms[MN_BONE_PALETTE_SIZE];
		};
	public:
		MnBonePaletteBuffer();
		~MnBonePaletteBuffer();

		HRESULT Init(const CPD3DDevice& cpDevice, UINT registerSlot, MN_CONSTANT_BUFFER_BELONG bufferBelong);

		void SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const D3D11_SUBRESOURCE_DATA bonePalette);
		void SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnSkeleton> spSkeleton);
	};
}