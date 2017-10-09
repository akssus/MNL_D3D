#pragma once
#include <vector>
#include <memory>
#include "MnMeshTexture.h"

namespace MNL
{
	/*
	Provides serialized shader resource views
	*/
	class MnMeshTextureCombination
	{
	public:
		MnMeshTextureCombination();
		~MnMeshTextureCombination();
		
		void AddMeshTexture(const std::shared_ptr<MnMeshTexture>& spMeshTexture);

		const std::vector<CPD3DShaderResourceView>& GetShaderResourceViews() const;

		UINT GetNumTextures() const;

	private:
		std::vector<std::shared_ptr<MnMeshTexture>> m_meshTextures;
		std::vector<CPD3DShaderResourceView> m_shaderResourceViews;
	};
}