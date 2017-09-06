#pragma once
#include <d3d11.h>
#include <memory>
#include "MnTypedefs.h"

namespace MNL
{
	/*
	the render target can be video ram or a texture
	*/
	class MnRenderTargetView
	{
	public:
		MnRenderTargetView();
		~MnRenderTargetView();

		/*
		If use back buffer as render target, then pRenderTargetViewDesc is nullptr
		*/
		HRESULT Init(const CPD3DDevice cpDevice, const CPD3DTexture2D renderSurface, const std::shared_ptr<D3D11_RENDER_TARGET_VIEW_DESC> pRenderTargetViewDesc);
		const CPD3DRenderTargetView& GetRenderTargetView() const;

	private:
		CPD3DRenderTargetView	m_cpRenderTargetView;
	};
}