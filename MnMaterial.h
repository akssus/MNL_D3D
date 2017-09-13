#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	/*
	Materials are not producted by model files. Just make some fixed material datas with factory then use them.
	*/
	class MnMaterial
	{
	public:
		MnMaterial();
		~MnMaterial();

		DirectX::SimpleMath::Vector4 diffuse;
		DirectX::SimpleMath::Vector4 ambient;
		DirectX::SimpleMath::Vector4 emissive;
		DirectX::SimpleMath::Vector4 specular;
		float specularPower;
	};
}