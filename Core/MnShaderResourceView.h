#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnShaderResourceView
	{
	public:
		MnShaderResourceView();
		~MnShaderResourceView();

		/**
		@brief ���̴� ���ҽ� �並 �ʱ�ȭ�Ѵ�. �⺻��� DIMENSION_2D + DXGI_FORMAT_R32G32B32A32_FLOAT
		*/
		HRESULT Init(const CPD3DDevice& cpDevice, const CPD3DTexture2D& cpResource);

		CPD3DShaderResourceView GetShaderResourceView() const;

	private:
		CPD3DShaderResourceView m_cpShaderResourceView;
	};
}