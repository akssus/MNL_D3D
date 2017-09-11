#include "MnShaderPath.h"
#include <cassert>

using namespace MNL;

MnShaderPath::MnShaderPath()
{
}


MnShaderPath::~MnShaderPath()
{
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
const std::shared_ptr<MnVertexShader> MnShaderPath::GetMnVertexShader() const
{
	return m_spVertexShader;
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