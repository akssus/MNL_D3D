#pragma once
#include <d3d11.h>
#include <string>
#include "../Core\MnTypedefs.h"
#include "DXTK\WICTextureLoader.h"

namespace MNL
{
	class MnTexture
	{
	public:
		MnTexture();
		~MnTexture();
		HRESULT LoadFromFile(std::wstring textureFileName);

		const CPD3DShaderResourceView GetShaderResourceView() const;

	private:
		CPD3DShaderResourceView m_cpShaderResourceView;
	};
}
