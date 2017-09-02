#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	class MnPixelShader
	{
	public:
		MnPixelShader();
		~MnPixelShader();
		
		const CPD3DBlob GetByteCode() const;
		const CPD3DPixelShader GetShader() const;

	private:
		CPD3DBlob m_cpByteCode;
		CPD3DPixelShader m_cpShader;
	};
}