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
		@brief 다른 MnTexture2D 로부터 텍스쳐 리소스를 복사해온다.
		@warning 초기화 되지 않았을 경우 에러
		*/
		void CopyFrom(const CPD3DDeviceContext& cpDeviceContext, const MnTexture2D& other);
			
	private:
		D3D11_TEXTURE2D_DESC m_textureDesc;
		CPD3DTexture2D m_cpTexture2D;
	};
};