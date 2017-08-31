#pragma once
#include <d3d11.h>
#include <string>
#include "MNL.h"


namespace MNL
{
	class ShaderPath
	{
	public:
		ShaderPath();
		~ShaderPath();

		bool Init(std::wstring VSFileName, std::wstring PSFileName);

	private:
		CPD3DVertexShader	m_pVertexShader;
		CPD3DPixelShader	m_pPixelShader;
	};
}