#include "SkinnedMeshRenderer.h"
#include "Render\MnSkinnedMeshVertexType.h"
#include "MnFramework.h"
#include "Core/MnLog.h"
#include "Mesh.h"
#include "Transform.h"

using namespace MNL;

SkinnedMeshRenderer::SkinnedMeshRenderer() : m_isInitialized(false)
{
	_Init();
}


SkinnedMeshRenderer::~SkinnedMeshRenderer()
{
}

void SkinnedMeshRenderer::Render()
{
	//렌더러가 초기화 되지 못했을 경우 렌더링을 취소한다.
	if (!m_isInitialized)
	{
		return;
	}
	auto& renderAPI = MnFramework::renderAPI;
	auto spMeshComponent = GetComponent<Mesh>();
	if (spMeshComponent != nullptr)
	{
		auto spMesh = spMeshComponent->GetMesh();
		//메시가 존재하지 않을 경우 렌더링을 취소한다.
		if (spMesh == nullptr)
		{
			return;
		}

		auto spSkeleton = spMeshComponent->GetSkeleton();
		//스켈레톤이 존재하지 않을 경우 디폴트 스켈레톤을 사용한다.(본팔레트 모두가 Identity)
		if (spSkeleton == nullptr)
		{
			//@todo 디폴트 스켈레톤으로 변경 요망
			spSkeleton = std::make_shared<MnSkeleton>();
		}

		auto transformComponent = GetComponent<Transform>();
		//위상 정보가 없을 경우 렌더링을 취소한다.
		if (transformComponent == nullptr)
		{
			return;
		}

		m_renderer.SetBonePalette(renderAPI.GetD3DDeviceContext(), spSkeleton->GetBonePalette());
		m_renderer.SetWorldBuffer(renderAPI.GetD3DDeviceContext(), transformComponent->GetTransformMatrix());
		m_renderer.SetViewProjectionBuffer

		m_renderer.RenderMesh(MnFramework::renderAPI, spMesh);
	}
}

void SkinnedMeshRenderer::_Init()
{
	HRESULT result = m_renderer.Init(MnFramework::renderAPI.GetD3DDevice(), std::make_shared<MnSkinnedMeshVertexType>());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_renderer));
		return;
	}
	m_isInitialized = true;
}