#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnDepthStencilState
	{
	public:
		MnDepthStencilState();
		~MnDepthStencilState();

		HRESULT Init(CPD3DDevice cpDevice, bool depthEnable, bool stencilEnable);
		const CPD3DDepthStencilState GetState() const;

	private:
		D3D11_DEPTH_STENCIL_DESC m_depthStencilStateDesc;
		CPD3DDepthStencilState m_cpDepthStencilState;
	};
}