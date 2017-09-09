#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	class MnMaterial
	{
	public:
		MnMaterial();
		~MnMaterial();

		DirectX::SimpleMath::Vector4 m_diffuse;
		DirectX::SimpleMath::Vector4 m_ambient;
		DirectX::SimpleMath::Vector4 m_specular;

	};
}