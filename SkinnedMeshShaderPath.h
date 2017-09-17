#pragma once
#include <d3d11.h>
#include "DXTK/SimpleMath.h"
#include "Render\MnShaderPathInstance.h"
#include "Core/MnConstantBuffer.h"

namespace MNL
{
	class SkinnedMeshShaderPath : public MnShaderPathInstance
	{
	public:
		SkinnedMeshShaderPath();
		~SkinnedMeshShaderPath();
		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType);

	};
}
