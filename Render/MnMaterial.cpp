#include "MnMaterial.h"

using namespace MNL;

MnMaterial::MnMaterial():specularPower(0.0f)
{
	ZeroMemory(&diffuse, sizeof(DirectX::SimpleMath::Vector4));
	ZeroMemory(&ambient, sizeof(DirectX::SimpleMath::Vector4));
	ZeroMemory(&specular, sizeof(DirectX::SimpleMath::Vector4));
	ZeroMemory(&emissive, sizeof(DirectX::SimpleMath::Vector4));
}


MnMaterial::~MnMaterial()
{
}
