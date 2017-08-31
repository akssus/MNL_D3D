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

		CPD3DBlob GetByteCode() const;

	private:
		CPD3DBlob m_byteCode;
	};

}