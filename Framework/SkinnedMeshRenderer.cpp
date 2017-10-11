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
	//�������� �ʱ�ȭ ���� ������ ��� �������� ����Ѵ�.
	if (!m_isInitialized)
	{
		return;
	}
	auto& renderAPI = MnFramework::renderAPI;
	auto spMeshComponent = GetComponent<Mesh>();
	if (spMeshComponent != nullptr)
	{
		auto spMesh = spMeshComponent->GetMesh();
		//�޽ð� �������� ���� ��� �������� ����Ѵ�.
		if (spMesh == nullptr)
		{
			return;
		}

		auto spSkeleton = spMeshComponent->GetSkeleton();
		//���̷����� �������� ���� ��� ����Ʈ ���̷����� ����Ѵ�.(���ȷ�Ʈ ��ΰ� Identity)
		if (spSkeleton == nullptr)
		{
			//@todo ����Ʈ ���̷������� ���� ���
			spSkeleton = std::make_shared<MnSkeleton>();
		}

		auto transformComponent = GetComponent<Transform>();
		//���� ������ ���� ��� �������� ����Ѵ�.
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