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
	renderAPI.SetVertexBuffer(mesh->GetVertexBuffer(), mesh->GetVertexBufferStride(), 0);
	renderAPI.SetIndexBuffer(mesh->GetIndexBuffer(), mesh->GetIndexBufferFormat());
	renderAPI.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw call
	UINT numSubMeshes = mesh->GetNumSubMeshes();
	for (UINT i = 0; i < numSubMeshes; ++i)
	{
		auto& submesh = mesh->GetSubMesh(i);
		renderAPI.DrawIndexed(submesh.indexCount, 0, submesh.indexOffset);
	}
}