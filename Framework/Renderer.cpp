#include "Renderer.h"
#include "MnFramework.h"
#include "Core/MnLog.h"
#include "Transform.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"
#include "Texture.h"
#include "Material.h"

using namespace MNL;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::_Init()
{
	auto& cpDevice = MnFramework::renderAPI.GetD3DDevice();
	HRESULT result = m_worldBuffer.Init(cpDevice, _CONST_BUF_WORLD, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_worldBuffer));
		return;
	}

	result = m_viewProjectionBuffer.Init(cpDevice, _CONST_BUF_VIEWPROJECTION, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_viewProjectionBuffer));
		return;
	}

	result = m_lightBuffer.Init(cpDevice, _CONST_BUF_LIGHT, MN_CONSTANT_BUFFER_BELONG_BOTH);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_lightBuffer));
		return;
	}

	result = m_materialBuffer.Init(cpDevice, _CONST_BUF_MATERIAL, MN_CONSTANT_BUFFER_BELONG_PS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_materialBuffer));
		return;
	}

	result = m_bonePaletteBuffer.Init(cpDevice, _CONST_BUF_BONE_PALETTE, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_bonePaletteBuffer));
		return;
	}
}

void Renderer::Render()
{
	auto& renderAPI = MnFramework::renderAPI;
	//빨간줄은 구현해야 될 사항
	auto& lstObjects = GameWorld().GetObjects();
	for (auto& object : lstObjects)
	{
		auto objTransform = object->GetComponent<Transform>();
		//위상정보가 없으면 렌더링은 불필요
		if (objTransform == nullptr) continue;
		
		auto objMesh = object->GetComponent<Mesh>();
		//메시가 없으면 렌더링은 불필요
		if (objMesh == nullptr) continue;
		
		auto objTexture = object->GetComponent<Texture>();
		if (objTexture != nullptr)
		{
			auto& lstShaderResourceViews = objTexture->GetShaderResourceViews();
			for (int i = 0; i < lstTextures.size(); ++i)
			{
				renderAPI.SetShaderResoureView(lstShaderResourceViews[i], i);
			}
		}

		auto objMaterial = object->GetComponent<Material>();
		if (objMaterial != nullptr)
		{
			m_materialBuffer.SetMaterial(renderAPI.GetD3DDeviceContext(), objMaterial->GetMaterial());
		}

		auto spSkeleton = objMesh->GetSkeleton();
		if (spSkeleton != nullptr)
		{
			m_bonePaletteBuffer.SetBonePalette(renderAPI.GetD3DDeviceContext(), spSkeleton());
		}
	}

	auto lstLights = GameWorld.GetLights();
}