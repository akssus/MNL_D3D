/**
@class MnCustomRenderTarget
@brief 렌더타겟용 텍스쳐를 생성하고 렌더타겟뷰와 뎁스스텐실 버퍼 뷰를 제공한다.
@author Akssus
@section 개요
Render-To-Texture 용 렌더타겟을 제공한다.
*/

#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnTypedefs.h"
#include "Core/MnRenderAPI.h"
#include "Core/MnLog.h"
#include "Core/MnTexture2D.h"
#include "Core/MnRenderTargetView.h"
#include "Core/MnDepthStencilBuffer.h"


namespace MNL
{
	class MnCustomRenderTarget
	{
	public:
		MnCustomRenderTarget();
		~MnCustomRenderTarget();
		
		/**
		@brief 렌더타겟을 생성한다.
		@param textureWidth 렌더타겟 텍스쳐의 넓이
		@param textureHeight 렌더타겟 텍스쳐의 높이
		@return 초기화 성공 여부
		*/
		HRESULT Init(const CPD3DDevice& cpDevice, float textureWidth, float textureHeight);

		void Clear(MnRenderAPI& renderAPI, DirectX::SimpleMath::Color = { 0.0f,0.0f,0.0f,0.0f });

		CPD3DRenderTargetView GetRenderTargetView() const;
		CPD3DDepthStencilView GetDepthStencilView() const;

	private:
		MnTexture2D m_renderedTexture; ///< 렌더타겟용 버퍼
		MnRenderTargetView m_renderTargetView; ///< 렌더타겟용 버퍼에 대한 렌더타겟뷰
		MnDepthStencilBuffer m_depthStencilBuffer; ///< 렌더타겟용 뎁스 스텐실 버퍼

	};
}