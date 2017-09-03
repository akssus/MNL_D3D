#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnDepthStencilBuffer
	{
	public:
		MnDepthStencilBuffer();
		~MnDepthStencilBuffer();

		HRESULT Init(const CPD3DDevice cpDevice, UINT width, UINT height);
		const CPD3DDepthStencilView GetDepthStencilView() const;

	private:
		D3D11_TEXTURE2D_DESC m_depthStencilBufferDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC m_depthStencilViewDesc;
		CPD3DTexture2D m_depthStencilBuffer;
		CPD3DDepthStencilView m_depthStencilView;
	};
}