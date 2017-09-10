#pragma once
#include <d3d11.h>
#include "DXTK/SimpleMath.h"
#include "Core\MnCustomVertexType.h"

namespace MNL
{
	struct MnStaticMeshVertex
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector2 texCoord;
	};
	class MnMeshVertexType : public MnCustomVertexType
	{
	public:
		MnMeshVertexType();
		~MnMeshVertexType();
	};
}