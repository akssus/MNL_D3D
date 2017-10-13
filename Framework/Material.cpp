#include "Material.h"

using namespace MNL;

Material::Material()
{
}


Material::~Material()
{
}


void Material::SetMaterial(const std::shared_ptr<MnMaterial>& spMaterial)
{
	m_spMaterial = spMaterial;
}

std::shared_ptr<MnMaterial> Material::GetMaterial() const
{
	return m_spMaterial;
}