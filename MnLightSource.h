#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	class MnLightSource
	{
	public:
		MnLightSource();
		~MnLightSource();

		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Vector3 m_direction;
	};
}
