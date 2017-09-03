#pragma once
#include <d3d11.h>
#include <string>
#include "MnTypedefs.h"

namespace MNL
{
	class MnPixelShader
	{
	public:
		MnPixelShader();
		~MnPixelShader();

		HRESULT Init(CPD3DDevice cpDevice, std::wstring shaderFileName, std::string entryPoint, std::string shaderVersion);
		const CPD3DBlob GetByteCode() const;
		const CPD3DPixelShader GetShader() const;

	private:
		CPD3DBlob _CompileShaderFromFile(const std::wstring fileName, const std::string entryPoint, const std::string shaderVersion);
		HRESULT _CreateShader(const CPD3DDevice cpDevice, const CPD3DBlob cpByteCode);

		/*
		This function is only for temporarily debugging using. It need to be replaced later
		*/
		void _OutputShaderErrorMessage(const CPD3DBlob errorMessage);

	private:
		CPD3DBlob m_cpByteCode;
		CPD3DPixelShader m_cpShader;
	};
}