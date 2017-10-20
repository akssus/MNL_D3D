#include "Texture.h"
#include <cassert>
#include "MnGameObject.h"
#include "Transform.h"

using namespace MNL;

Texture::Texture()
{
	m_tblTextures.resize(MN_TEXTURE_TYPE_TOTAL, nullptr);
}


Texture::~Texture()
{
}


void Texture::SetTexture(const std::shared_ptr<MnMeshTexture>& spTexture, MN_TEXTURE_TYPE textureType)
{
	assert(spTexture != nullptr);
	m_tblTextures[textureType] = spTexture;
}

std::shared_ptr<MnMeshTexture> Texture::GetTexture(MN_TEXTURE_TYPE textureType)
{
	return m_tblTextures[textureType];
}