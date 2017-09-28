#include "MnPixelShader.h"
#include "MnLog.h"
#include <d3dcompiler.h>
#include <fstream>

using namespace MNL;

MnPixelShader::MnPixelShader()
{
}


MnPixelShader::~MnPixelShader()
{
}

HRESULT MnPixelShader::Init(CPD3DDevice cpDevice, std::wstring shaderFileName, std::string entryPoint, std::string shaderVersion)
{
	CPD3DBlob cpByteCode = _CompileShaderFromFile(shaderFileName, entryPoint, shaderVersion);
	if (cpByteCode == nullptr)
	{
		//error log
		return E_FAIL;
	}
	m_cpByteCode = cpByteCode;

	HRESULT result = _CreateShader(cpDevice, cpByteCode);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(_CreateShader));
		return E_FAIL;
	}

	return S_OK;
}
const CPD3DBlob MnPixelShader::GetByteCode() const
{
	return m_cpByteCode;
}
const CPD3DPixelShader MnPixelShader::GetShader() const
{
	return m_cpShader;
}


CPD3DBlob MnPixelShader::_CompileShaderFromFile(const std::wstring fileName, const std::string entryPoint, const std::string shaderVersion)
{
	CPD3DBlob byteCode;
	CPD3DBlob errorMsg;
	HRESULT result = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, entryPoint.c_str(), shaderVersion.c_str(), 0, 0, byteCode.ReleaseAndGetAddressOf(), errorMsg.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(D3DCompileFromFile));
		_OutputShaderErrorMessage(errorMsg);
		return nullptr;
	}
	return byteCode;
}
HRESULT MnPixelShader::_CreateShader(const CPD3DDevice cpDevice, const CPD3DBlob cpByteCode)
{
	HRESULT result = cpDevice->CreatePixelShader(cpByteCode.Get()->GetBufferPointer(), cpByteCode.Get()->GetBufferSize(), nullptr, m_cpShader.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(CreatePixelShader));
		return result;
	}
	return S_OK;
}

void MnPixelShader::_OutputShaderErrorMessage(const CPD3DBlob errorMessage)
{
	char* compileErrors = nullptr;
	UINT bufferSize = 0;
	std::ofstream fout;

	compileErrors = (char*)(errorMessage->GetBufferPointer());
	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for (int i = 0; i < bufferSize; ++i)
	{
		fout << compileErrors[i];
	}

	fout.close();
}