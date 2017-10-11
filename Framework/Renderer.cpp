#include "Renderer.h"

using namespace MNL;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::SetTextures(const std::shared_ptr<MnMeshTextureCombination>& spTextures)
{
	m_spTextures = spTextures;
}
void Renderer::AddTexture(const std::shared_ptr<MnMeshTexture>& spTexture)
{
	m_spTextures->AddMeshTexture(spTexture);
}
void Renderer::ClearTextures()
{
	m_spTextures.reset();
}

void Renderer::AddShaderPath(const std::shared_ptr<MnShaderPathInstance>& spShaderPath)
{
	m_lstShaderPaths.push_back(spShaderPath);
}
void Renderer::ClearShaderPaths()
{
	m_lstShaderPaths.clear();
}

void Renderer::SetLight(const std::shared_ptr<MnLightSource>& spLight)
{
	m_spLight = spLight;
}
void Renderer::ClearLight()
{
	m_spLight.reset();
}

void Renderer::SetMaterial(const std::shared_ptr<MnMaterial>& spMaterial)
{
	m_spMaterial = spMaterial;
}
void Renderer::ClearMaterial()
{
	m_spMaterial.reset();
}