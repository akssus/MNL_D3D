/**
@class MnRenderTargetView
@brief Texture2D 에 대한 렌더타겟뷰를 생성하고 인터페이스를 제공한다.
@author Akssus
*/

#pragma once
#include <d3d11.h>
#include <memory>
#include "MnTypedefs.h"

namespace MNL
{
	class MnRenderTargetView
	{
	public:
		MnRenderTargetView();
		~MnRenderTargetView();

		/**
		@brief 렌더타겟뷰를 생성한다. 
		@param pRenderTargetViewDesc 백버퍼에 대한 렌더타겟뷰 생성시 nullptr 를 인수로 넘긴다. 포인터 형식인 이유는 널 인자를 받기 위함임.
		@return 초기화 성공 여부
		*/
		HRESULT Init(const CPD3DDevice cpDevice, const CPD3DTexture2D renderSurface, const std::shared_ptr<D3D11_RENDER_TARGET_VIEW_DESC> pRenderTargetViewDesc);
		const CPD3DRenderTargetView& GetRenderTargetView() const;

	private:
		CPD3DRenderTargetView	m_cpRenderTargetView;
	};
}