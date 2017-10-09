/**
@class MnRenderTargetView
@brief Texture2D �� ���� ����Ÿ�ٺ並 �����ϰ� �������̽��� �����Ѵ�.
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
		@brief ����Ÿ�ٺ並 �����Ѵ�. 
		@param pRenderTargetViewDesc ����ۿ� ���� ����Ÿ�ٺ� ������ nullptr �� �μ��� �ѱ��. ������ ������ ������ �� ���ڸ� �ޱ� ������.
		@return �ʱ�ȭ ���� ����
		*/
		HRESULT Init(const CPD3DDevice cpDevice, const CPD3DTexture2D renderSurface, const std::shared_ptr<D3D11_RENDER_TARGET_VIEW_DESC> pRenderTargetViewDesc);
		const CPD3DRenderTargetView& GetRenderTargetView() const;

	private:
		CPD3DRenderTargetView	m_cpRenderTargetView;
	};
}