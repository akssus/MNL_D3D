#include "MnMeshTextureCombination.h"

using namespace MNL;

MnMeshTextureCombination::MnMeshTextureCombination()
{
}


MnMeshTextureCombination::~MnMeshTextureCombination()
{
}

void MnMeshTextureCombination::AddMeshTexture(const std::shared_ptr<MnMeshTexture>& spMeshTexture)
{
	const CPD3DShaderResourceView shaderResourceView = spMeshTexture->GetShaderResourceView();
	if (shaderResourceView == nullptr)
	{
		//uninitialized mesh texture
		return;
	}
	m_meshTextures.push_back(spMeshTexture);
	m_shaderResourceViews.push_back(shaderResourceView);
}

const std::vector<CPD3DShaderResourceView>& MnMeshTextureCombination::GetShaderResourceViews() const
{
	return m_shaderResourceViews;
}