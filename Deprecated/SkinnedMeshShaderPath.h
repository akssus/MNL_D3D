#pragma once
#include <d3d11.h>
#include <memory>
#include "DXTK/SimpleMath.h"
#include "Core/MnTypedefs.h"
#include "Core/MnCustomVertexType.h"
#include "Render\MnShaderPathInstance.h"


class SkinnedMeshShaderPath : public MNL::MnShaderPathInstance
{
public:
	SkinnedMeshShaderPath();
	~SkinnedMeshShaderPath();
	HRESULT Init(const MNL::CPD3DDevice& cpDevice, const std::shared_ptr<MNL::MnCustomVertexType>& spVertexType);
};
