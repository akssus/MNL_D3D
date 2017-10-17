#include "Texture.h"
#include <cassert>
#include "MnGameObject.h"
#include "Transform.h"

using namespace MNL;

Texture::Texture()
{
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
	if (m_tblTextures.count(textureType) == 0)
		return nullptr;
	return m_tblTextures[textureType];
}