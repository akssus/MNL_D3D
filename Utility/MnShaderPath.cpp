#include "MnShaderPath.h"
#include <cassert>

using namespace MNL;

MnShaderPath::MnShaderPath()
{
}


MnShaderPath::~MnShaderPath()
{
}
/*
HRESULT MnShaderPath::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnVertexShader> spVertexShader, const std::shared_ptr<MnPixelShader> spPixelShader, const std::shared_ptr<MnCustomVertexType> spVertexType)
{
	m_spVertexShader = spVertexShader;
	m_spPixelShader = spPixelShader;
	
	auto spLayout = _CreateInputLayout(cpDevice,spVertexType,spVertexShader);
	if (spLayout == nullptr)
	{
		//error log
		return E_FAIL;
	}
	m_spInputLayout = spLayout;

	return S_OK;
}
*/
void MnShaderPath::AddConstantBuffer(const std::shared_ptr< MnConstantBuffer> spConstantBuffer)
{
	assert(spConstantBuffer != nullptr);
	m_constantBuffers.push_back(spConstantBuffer);
}
void MnShaderPath::SetVertexShader(const std::shared_ptr<MnVertexShader>& spVertexShader) 
{
	assert(spVertexShader != nullptr);
	m_spVertexShader = spVertexShader;
}
void MnShaderPath::SetPixelShader(const std::shared_ptr<MnPixelShader>& spPixelShader)
{
	assert(spPixelShader != nullptr);
	m_spPixelShader = spPixelShader;
}
void MnShaderPath::SetInputLayout(const std::shared_ptr<MnInputLayout>& spInputLayout)
{
	assert(spInputLayout != nullptr);
	m_spInputLayout = spInputLayout;
}

const CPD3DVertexShader MnShaderPath::GetVertexShader() const
{
	return m_spVertexShader->GetShader();
}
const CPD3DPixelShader MnShaderPath::GetPixelShader() const
{
	return m_spPixelShader->GetShader();
}
const CPD3DInputLayout MnShaderPath::GetInputLayout() const
{
	return m_spInputLayout->GetInputLayout();
}
UINT MnShaderPath::GetNumConstantBuffers() const
{
	return m_constantBuffers.size();
}
const std::shared_ptr<MnConstantBuffer> MnShaderPath::GetConstantBuffer(UINT index) const
{
	return m_constantBuffers[index];
}
/*
std::shared_ptr<MnInputLayout> MnShaderPath::_CreateInputLayout(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType> spVertexType, const std::shared_ptr<MnVertexShader> spVertexShader)
{
	auto spInputLayout = std::make_shared<MnInputLayout>();
	assert(spInputLayout != nullptr);
	
	HRESULT result = spInputLayout->Init(cpDevice, spVertexType, spVertexShader);
	if (FAILED(result))
	{
		//erorr log
		return nullptr;
	}
	return spInputLayout;
}
std::shared_ptr<MnConstantBuffer> MnShaderPath::_CreateConstantBuffer(const CPD3DDevice& cpDevice, const std::shared_ptr<MnConstantBufferType> spConstantBufferType)
{
	auto spConstantBuffer = std::make_shared<MnConstantBuffer>();
	assert(spConstantBuffer != nullptr);

	HRESULT result = spConstantBuffer->Init(cpDevice, spConstantBufferType);
	if (FAILED(result))
	{
		//erorr log
		return nullptr;
	}

	return spConstantBuffer;
}
*/