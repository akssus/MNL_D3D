#include "Renderer.h"
#include "MnFramework.h"
#include "Core/MnLog.h"
#include "ShaderList.h"
#include "MnGameWorld.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

Renderer::Renderer()
{
	_Init();
}


Renderer::~Renderer()
{
}

void Renderer::_Init()
{
	auto& cpDevice = MnFramework::renderAPI.GetD3DDevice();

	auto spBackBufferVertexType = std::make_shared<MnCustomVertexType>();
	spBackBufferVertexType->AddInputElement(MnInputElement("POSITION", MN_INPUT_ELEMENT_TYPE_FLOAT3, 0));
	spBackBufferVertexType->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2, 0));

	HRESULT result = m_backBufferShader.Init(cpDevice, L"backBufferShader_vs.hlsl", L"backBufferShader_ps.hlsl", spBackBufferVertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_backBufferShader));
		return;
	}
	
	std::vector<_BackBufferShaderVertex> vertices = {
		{ Vector3(-1.0f,1.0f,0.0f),		Vector2(0.0f,0.0f) },	//LT
		{ Vector3(1.0f,1.0f,0.0f),		Vector2(1.0f,0.0f) },	//RT
		{ Vector3(-1.0f,-1.0f,0.0f),	Vector2(0.0f,1.0f) },	//LB
		{ Vector3(1.0f,-1.0f,0.0f),		Vector2(1.0f,1.0f) }	//RB
	};

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = m_vertexBuffer.Init(cpDevice, spBackBufferVertexType, 4, &vertexData, false);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_vertexBuffer));
		return;
	}

	std::vector<UINT> indices = { 0,2,1,1,2,3 };

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = m_indexBuffer.Init(cpDevice, 6, &indexData);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_indexBuffer));
		return;
	}

}

void Renderer::Render(const MnRenderWindow& renderWindow)
{
	auto& renderAPI = MnFramework::renderAPI;
	
	auto shaderList = GameWorld()->GetComponent<ShaderList>();
	if (shaderList == nullptr)
	{
		//���̴��� ������ �������� �����Ѵ�
		return;
	}

	auto& renderOrder = shaderList->GetRenderOrder();
	
	std::shared_ptr<MnCustomRenderTarget> spRenderedScene = nullptr;
	for (int id : renderOrder)
	{
		auto shader = shaderList->GetShader(id);
		if (shader != nullptr)
		{
			shader->Render(spRenderedScene);
			spRenderedScene = shader->GetFinalRenderTarget();
		}
	}
	if (spRenderedScene == nullptr)
	{
		//�׷��� ���� ���̸� �������� �����Ѵ�
		return;
	}

	//spRenderedScene�� ����Ʈ ���μ��� ȿ���� �ִ´�.. �̱���

	//���������� ����ۿ� �׸���
	_RenderToBackBuffer(spRenderedScene, renderWindow);
}

void Renderer::_RenderToBackBuffer(const std::shared_ptr<MnCustomRenderTarget>& spRenderTarget, const MnRenderWindow& renderWindow)
{
	auto& renderAPI = MnFramework::renderAPI;
	renderAPI.SetVertexShader(m_backBufferShader.GetVertexShader());
	renderAPI.SetPixelShader(m_backBufferShader.GetPixelShader());

	renderAPI.SetSamplerState(m_backBufferShader.GetSamplerState());
	renderAPI.SetInputLayout(m_backBufferShader.GetInputLayout());
	renderAPI.SetVertexBuffer(m_vertexBuffer);
	renderAPI.SetIndexBuffer(m_indexBuffer);
	renderAPI.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	renderAPI.SetRenderTarget(renderWindow.GetBackBufferRenderTargetView(), renderWindow.GetBackBufferDepthStencilView());
	renderAPI.SetShaderResoureView(spRenderTarget->GetShaderResourceView(), 0);

	renderAPI.DrawIndexed(6);

	renderAPI.SetShaderResoureView(nullptr, 0);
}