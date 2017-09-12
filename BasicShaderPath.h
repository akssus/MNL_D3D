#pragma once
#include <d3d11.h>
#include "DXTK/SimpleMath.h"
#include "Utility\MnShaderPathInstance.h"
#include "Core/MnConstantBuffer.h"

namespace MNL
{
	class BasicShaderPath : public MnShaderPathInstance
	{
	public:
		BasicShaderPath();
		~BasicShaderPath();
		HRESULT Init(const CPD3DDevice& cpDevice,const std::shared_ptr<MnCustomVertexType>& spVertexType);

	};
}
