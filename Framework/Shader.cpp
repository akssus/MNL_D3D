#include "Shader.h"
#include "MnFramework.h"
#include "Core/MnLog.h"

using namespace MNL;

Shader::Shader()
{
	_Init();
}


Shader::~Shader()
{
}

void Shader::_Init()
{
	auto screenSize = GameWorld()->GetScreenSize();
	HRESULT result = m_renderedScene.Init(MnFramework::renderAPI.GetD3DDevice(), screenSize.x, screenSize.y);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_renderedScene));
	}
}

void Shader::AddObjectsToQueue(const std::shared_ptr<MnGameObject>& spObject)
{
	m_renderQueue.push_back(spObject);
}

CPD3DShaderResourceView Shader::GetRenderedScene() const
{
	m_renderedScene.GetRenderTargetView();
}

void Shader::_ClearQueue()
{
	m_renderQueue.clear();
}