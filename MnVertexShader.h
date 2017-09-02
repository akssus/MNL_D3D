#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	class MnVertexShader
	{
	public:
		MnVertexShader();
		~MnVertexShader();

		const CPD3DBlob GetByteCode() const;
		const CPD3DVertexShader GetShader() const;

	private:
		CPD3DBlob m_cpByteCode;
		CPD3DVertexShader m_cpShader;
	};

}