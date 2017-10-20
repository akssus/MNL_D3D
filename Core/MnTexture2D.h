#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnTexture2D
	{
	public:
		MnTexture2D();
		~MnTexture2D();

		HRESULT Init(const CPD3DDevice device, const D3D11_TEXTURE2D_DESC& textureDesc);
		const CPD3DTexture2D GetTexture() const;

		/**
		@brief �ٸ� MnTexture2D �κ��� �ؽ��� ���ҽ��� �����ؿ´�.
		@warning �ʱ�ȭ ���� �ʾ��� ��� ����
		*/
		void CopyFrom(const CPD3DDeviceContext& cpDeviceContext, const MnTexture2D& other);
			
	private:
		D3D11_TEXTURE2D_DESC m_textureDesc;
		CPD3DTexture2D m_cpTexture2D;
	};
};