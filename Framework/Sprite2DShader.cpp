#include "Sprite2DShader.h"
#include "Sprite2D.h"
#include "Texture.h"
#include "MnGameWorld.h"
#include "MnFramework.h"
#include "Core/MnLog.h"
#include "Core/MnCustomVertexType.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

Sprite2DShader::Sprite2DShader():
	m_screenWidth(0.0f),
	m_screenHeight(0.0f)
{
	ZeroMemory(&m_projection, sizeof(Matrix));
	_Init();
}


Sprite2DShader::~Sprite2DShader()
{
}

void Sprite2DShader::_Init()
{
	auto cpDevice = MnFramework::renderAPI.GetD3DDevice();

	auto vertexType = std::make_shared<MnCustomVertexType>();
	vertexType->AddInputElement(MnInputElement("POSITION", MN_INPUT_ELEMENT_TYPE_FLOAT3, 0));
	vertexType->AddInputElement(MnInputElement("TEXCOORD", MN_INPUT_ELEMENT_TYPE_FLOAT2, 0));

	HRESULT result = m_shaderPath.Init(cpDevice, L"sprite2dshader_vs.hlsl", L"sprite2dshader_ps.hlsl", vertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_shaderPath));
		return;
	}

	result = m_worldBuffer.Init(cpDevice, 0, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_worldBuffer));
		return;
	}

	result = m_viewProjectionBuffer.Init(cpDevice, 1, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_viewProjectionBuffer));
		return;
	}

	_VertexType vertices[4] = {
		{ Vector3(-1.0f,1.0f,0.0f),		Vector2(0.0f,0.0f) },	//LT
		{ Vector3(1.0f,1.0f,0.0f),		Vector2(1.0f,0.0f) },	//RT
		{ Vector3(-1.0f,-1.0f,0.0f),	Vector2(0.0f,1.0f) },	//LB
		{ Vector3(1.0f,-1.0f,0.0f),		Vector2(1.0f,1.0f) }	//RB
	};

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = m_vertexBuffer.Init(cpDevice, vertexType, 4, &vertexData, false);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_vertexBuffer));
		return;
	}

	UINT indices[6] = { 0,2,1,1,2,3 };

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = m_indexBuffer.Init(cpDevice, 6, &indexData);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_indexBuffer));
		return;
	}
}

void Sprite2DShader::OnAttatched()
{
	auto pGameWorld = _GameWorld();
	if (pGameWorld == nullptr)
	{
		MnLog::MB_IsNull(MN_FUNC_INFO(_GameWorld));
		return;
	}
	auto screenSize = pGameWorld->GetScreenSize();
	SetScreenSize(screenSize.x, screenSize.y);
}

void Sprite2DShader::SetScreenSize(float width, float height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	_CalcProjection();
}

void Sprite2DShader::Render(const std::shared_ptr<MnCustomRenderTarget>& prevRenderedScene)
{
	auto& renderAPI = MnFramework::renderAPI;

	auto finalRenderTarget = GetFinalRenderTarget();
	finalRenderTarget->Clear(renderAPI, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f));
	if (prevRenderedScene != nullptr)
	{
		finalRenderTarget->CopyTextureFrom(renderAPI, *prevRenderedScene);
	}
	MnFramework::renderAPI.SetRenderTarget(finalRenderTarget->GetRenderTargetView(), finalRenderTarget->GetDepthStencilView());

	renderAPI.SetVertexShader(m_shaderPath.GetVertexShader());
	renderAPI.SetPixelShader(m_shaderPath.GetPixelShader());
	renderAPI.SetInputLayout(m_shaderPath.GetInputLayout());
	renderAPI.SetVertexBuffer(m_vertexBuffer);
	renderAPI.SetIndexBuffer(m_indexBuffer);
	
	renderAPI.SetConstantBufferVS(m_worldBuffer.GetBuffer(), 0);
	renderAPI.SetConstantBufferVS(m_viewProjectionBuffer.GetBuffer(), 1);

	m_viewProjectionBuffer.SetViewProjectionTransform(renderAPI.GetD3DDeviceContext(), Matrix::Identity, m_projection);

	if (MnFramework::IsDepthTestEnabled() == true)
	{
		MnFramework::SetDepthTestEnable(false);
	}
	if (MnFramework::IsAlphaBlendingEnabled() == false)
	{
		MnFramework::SetAlphaBlendiingEnable(true);
	}

	for (auto& obj : m_renderQueue)
	{
		auto compSprite = obj->GetComponent<Sprite2D>();
		if (compSprite == nullptr) continue;

		auto compTexture = obj->GetComponent<Texture>();
		if (compTexture == nullptr) continue;

		auto& matSprite = compSprite->GetTransform();
		auto texture = compTexture->GetTexture(MN_TEXTURE_DIFFUSE);
		if (texture == nullptr)
		{
			//디폴트 텍스쳐 사용
		}

		m_worldBuffer.SetWorldTransform(renderAPI.GetD3DDeviceContext(), matSprite);
		
		renderAPI.SetShaderResoureView(texture->GetShaderResourceView(),0);
		renderAPI.DrawIndexed(6);
	}
	if (MnFramework::IsDepthTestEnabled() == false)
	{
		MnFramework::SetDepthTestEnable(true);
	}

	_ClearQueue();
}

void Sprite2DShader::_CalcProjection()
{
	m_projection = Matrix::CreateOrthographic(m_screenWidth, m_screenHeight, 0.0f, 1.0f);
}