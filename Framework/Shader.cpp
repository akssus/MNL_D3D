#include "Shader.h"
#include "MnFramework.h"
#include "Core/MnLog.h"
#include "MnGameWorld.h"

using namespace MNL;

Shader::Shader():
	m_pWorld(nullptr),
	m_id(0)
{
	
}


Shader::~Shader()
{
}

void Shader::_Init(MnGameWorld* pWorld)
{
	_SetGameWorld(pWorld);
	auto screenSize = pWorld->GetScreenSize();
	m_spFinalRenderTarget = std::make_shared<MnCustomRenderTarget>();
	assert(m_spFinalRenderTarget != nullptr);
	HRESULT result = m_spFinalRenderTarget->Init(MnFramework::renderAPI.GetD3DDevice(), screenSize.x, screenSize.y);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spFinalRenderTarget));
	}
}
void Shader::OnAttatched()
{
	//nothing
}

void Shader::AddObjectsToQueue(const std::shared_ptr<MnGameObject>& spObject)
{
	m_renderQueue.push_back(spObject);
}

std::shared_ptr<MnCustomRenderTarget> Shader::GetFinalRenderTarget() const
{
	return m_spFinalRenderTarget;
}


void Shader::SetID(int id)
{
	m_id = id;
}
int Shader::GetID() const
{
	return m_id;
}

void Shader::_ClearQueue()
{
	m_renderQueue.clear();
}

MnGameWorld* Shader::_GameWorld() const
{
	return m_pWorld;
}

void Shader::_SetGameWorld(MnGameWorld* pWorld)
{
	m_pWorld = pWorld;
}

void Shader::_RenderMesh(const std::shared_ptr<MnMesh> mesh)
{
	auto& renderAPI = MnFramework::renderAPI;

	for (int i = 0; i < mesh->GetNumSubMehses(); ++i)
	{
		auto& subMesh = mesh->GetSubMesh(i);
		renderAPI.SetVertexBuffer(subMesh->GetVertexBuffer(), subMesh->GetVertexBufferStride(), 0);
		renderAPI.SetIndexBuffer(subMesh->GetIndexBuffer(), subMesh->GetIndexBufferFormat());
		renderAPI.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//draw call
		UINT numSubMeshFragments = subMesh->GetNumSubMeshFragments();
		for (UINT j = 0; j < numSubMeshFragments; ++j)
		{
			auto& submeshFragment = subMesh->GetSubMeshFragment(j);
			renderAPI.DrawIndexed(submeshFragment.indexCount, 0, submeshFragment.indexOffset);
		}
	}
}