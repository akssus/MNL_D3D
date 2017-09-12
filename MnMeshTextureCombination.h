#pragma once
#include <vector>
#include <memory>
#include "Utility/MnMeshTexture.h"

namespace MNL
{
	class MnMeshTextureCombination
	{
	public:
		MnMeshTextureCombination();
		~MnMeshTextureCombination();
		
		void AddMeshTexture(const std::shared_ptr<MnMeshTexture>& spMeshTexture);

		const std::vector<CPD3DShaderResourceView>& GetShaderResourceViews() const;

	private:
		std::vector<std::shared_ptr<MnMeshTexture>> m_meshTextures;
		std::vector<CPD3DShaderResourceView> m_shaderResourceViews;
	};
}