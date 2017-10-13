#include "Renderer.h"
#include "MnFramework.h"
#include "Core/MnLog.h"

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

	HRESULT result = m_backBufferShader.Init(cpDevice, L"backBufferShader_vs.hlsl", L"backBufferShader_ps.hlsl", spBackBufferVertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_backBufferShader));
		return;
	}
	
	std::vector<Vector3> vertices = {
		Vector3(-1.0f,1.0f,0.0f), //LT
		Vector3(1.0f,1.0f,0.0f), //RT
		Vector3(-1.0f,-1.0f,0.0f), //LB
		Vector3(1.0f,-1.0f,0.0f), //RB
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

	std::vector<UINT> indices = { 0,1,2,2,1,3 };

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
	
	//todo 10.15
	//셰이더 리스트 얻어오기
	//셰이더 우선순위에 따라 각각 렌더링 실행
	//셰이딩 후 텍스쳐에 이펙트 효과 추가 //옵셔널
	//최종 렌더링 된 렌더타겟으로 _RenderToBackBuffer 실행
	//_RenderToBackBuffer();

}

void Renderer::_RenderToBackBuffer(const std::shared_ptr<MnCustomRenderTarget>& spRenderTarget, const MnRenderWindow& renderWindow)
{
	auto& renderAPI = MnFramework::renderAPI;
	renderAPI.SetVertexShader(m_backBufferShader.GetVertexShader());
	renderAPI.SetPixelShader(m_backBufferShader.GetPixelShader());

	renderAPI.SetVertexBuffer(m_vertexBuffer);
	renderAPI.SetIndexBuffer(m_indexBuffer);
	renderAPI.SetInputLayout(m_backBufferShader.GetInputLayout());
	renderAPI.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	renderAPI.SetShaderResoureView(spRenderTarget->GetShaderResourceView(), 0);
	renderAPI.SetRenderTarget(renderWindow.GetBackBufferRenderTargetView(), renderWindow.GetBackBufferDepthStencilView());

	renderAPI.DrawIndexed(6);
}