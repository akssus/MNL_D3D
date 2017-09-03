#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnRasterizerState
	{
	public:
		MnRasterizerState();
		~MnRasterizerState();
		HRESULT Init(CPD3DDevice cpDevice, D3D11_FILL_MODE fillMode, bool isCCW);
		const CPD3DRasterizerState GetState() const;

	private:
		D3D11_RASTERIZER_DESC m_rasterizerDesc;
		CPD3DRasterizerState m_cpRasterizerState;
	};
}
