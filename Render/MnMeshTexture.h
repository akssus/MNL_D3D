#pragma once
#include <d3d11.h>
#include <string>
#include "DXTK\WICTextureLoader.h"
#include "../Core\MnTypedefs.h"
#include "../Core/MnTexture2D.h"

namespace MNL
{
	class MnMeshTexture
	{
	public:
		MnMeshTexture();
		~MnMeshTexture();
		HRESULT LoadFromFile(const CPD3DDevice& cpDevice, const std::wstring& textureFileName);

		const CPD3DShaderResourceView GetShaderResourceView() const;

	private:
		CPD3DShaderResourceView m_cpShaderResourceView;
	};
}
