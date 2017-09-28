#include "MnVertexShader.h"
#include "MnLog.h"
#include <d3dcompiler.h>
#include <fstream>

using namespace MNL;

MnVertexShader::MnVertexShader()
{
}


MnVertexShader::~MnVertexShader()
{
}

HRESULT MnVertexShader::Init(CPD3DDevice cpDevice, std::wstring shaderFileName,std::string entryPoint, std::string shaderVersion)
{
	CPD3DBlob cpByteCode = _CompileShaderFromFile(shaderFileName,entryPoint,shaderVersion);
	if (cpByteCode == nullptr)
	{
		//error log
		return E_FAIL;
	}
	m_cpByteCode = cpByteCode;

	HRESULT result = _CreateShader(cpDevice,cpByteCode);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(_CreateShader));
		return result;
	}

	return S_OK;
}
const CPD3DBlob MnVertexShader::GetByteCode() const
{
	return m_cpByteCode;
}
const CPD3DVertexShader MnVertexShader::GetShader() const
{
	return m_cpShader;
}


CPD3DBlob MnVertexShader::_CompileShaderFromFile(const std::wstring fileName, const std::string entryPoint, const std::string shaderVersion)
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
HRESULT MnVertexShader::_CreateShader(const CPD3DDevice cpDevice, const CPD3DBlob cpByteCode)
{
	HRESULT result = cpDevice->CreateVertexShader(cpByteCode.Get()->GetBufferPointer(), cpByteCode.Get()->GetBufferSize(), nullptr, m_cpShader.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(CreateVertexShader));
		return result;
	}
	return S_OK;
}

void MnVertexShader::_OutputShaderErrorMessage(const CPD3DBlob errorMessage)
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