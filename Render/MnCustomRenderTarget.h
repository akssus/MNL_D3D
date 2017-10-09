/**
@class MnCustomRenderTarget
@brief ����Ÿ�ٿ� �ؽ��ĸ� �����ϰ� ����Ÿ�ٺ�� �������ٽ� ���� �並 �����Ѵ�.
@author Akssus
@section ����
Render-To-Texture �� ����Ÿ���� �����Ѵ�.
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
		@brief ����Ÿ���� �����Ѵ�.
		@param textureWidth ����Ÿ�� �ؽ����� ����
		@param textureHeight ����Ÿ�� �ؽ����� ����
		@return �ʱ�ȭ ���� ����
		*/
		HRESULT Init(const CPD3DDevice& cpDevice, float textureWidth, float textureHeight);

		void Clear(MnRenderAPI& renderAPI, DirectX::SimpleMath::Color = { 0.0f,0.0f,0.0f,0.0f });

		CPD3DRenderTargetView GetRenderTargetView() const;
		CPD3DDepthStencilView GetDepthStencilView() const;

	private:
		MnTexture2D m_renderedTexture; ///< ����Ÿ�ٿ� ����
		MnRenderTargetView m_renderTargetView; ///< ����Ÿ�ٿ� ���ۿ� ���� ����Ÿ�ٺ�
		MnDepthStencilBuffer m_depthStencilBuffer; ///< ����Ÿ�ٿ� ���� ���ٽ� ����

	};
}