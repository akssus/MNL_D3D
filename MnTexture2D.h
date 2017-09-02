#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	class MnTexture2D
	{
	public:
		MnTexture2D();
		~MnTexture2D();
		HRESULT Init(const CPD3DDevice device, const D3D11_TEXTURE2D_DESC& textureDesc);
		const CPD3DTexture2D GetTexture() const;

	private:
		D3D11_TEXTURE2D_DESC m_textureDesc;
		CPD3DTexture2D m_cpTexture2D;
	};
}
