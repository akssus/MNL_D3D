#include "MnMaterial.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnMaterial::MnMaterial():
	diffuse(Vector4(0.0f,0.0f,0.0f,0.0f)),
	ambient(Vector4(0.0f, 0.0f, 0.0f, 0.0f)),
	specular(Vector4(0.0f, 0.0f, 0.0f, 0.0f)),
	emissive(Vector4(0.0f, 0.0f, 0.0f, 0.0f)),
	specularPower(0.0f)
{
	
}


MnMaterial::~MnMaterial()
{
}
