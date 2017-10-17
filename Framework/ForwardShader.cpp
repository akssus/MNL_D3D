#include "ForwardShader.h"
#include "Core\/MnLog.h"
#include "MnFramework.h"
#include "MnGameWorld.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "LightList.h"

using namespace MNL;

ForwardShader::ForwardShader()
{
	_Init();
}


ForwardShader::~ForwardShader()
{
}


void ForwardShader::_Init()
{
	_InitShaders();
	_InitConstantBuffers();
}

HRESULT ForwardShader::_InitShaders()
{
	auto& cpDevice = MnFramework::renderAPI.GetD3DDevice();

	m_spShaderPath = std::make_shared<MnShaderPathInstance>();
	assert(m_spShaderPath != nullptr);

	auto vertexType = std::make_shared<MnSkinnedMeshVertexType>();
	HRESULT result = m_spShaderPath->Init(cpDevice, L"forwardshader_vs.hlsl", L"forwardshader_ps.hlsl", vertexType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spShaderPath));
		return result;
	}
	return S_OK;
}
HRESULT ForwardShader::_InitConstantBuffers()
{
	auto& cpDevice = MnFramework::renderAPI.GetD3DDevice();

	m_spWorldBuffer = std::make_shared<MnWorldTransformBuffer>();
	assert(m_spWorldBuffer != nullptr);
	HRESULT result = m_spWorldBuffer->Init(cpDevice, _CONST_BUF_WORLD, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spWorldBuffer));
		return result;
	}

	m_spViewProjectionBuffer = std::make_shared<MnViewProjectionTransformBuffer>();
	assert(m_spViewProjectionBuffer != nullptr);
	result = m_spViewProjectionBuffer->Init(cpDevice, _CONST_BUF_VIEWPROJECTION, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spViewProjectionBuffer));
		return result;
	}

	m_spLightBuffer = std::make_shared<MnLightBuffer>();
	assert(m_spLightBuffer != nullptr);
	result = m_spLightBuffer->Init(cpDevice, _CONST_BUF_LIGHT, MN_CONSTANT_BUFFER_BELONG_BOTH);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spLightBuffer));
		return result;
	}
	//light buffer uses in both VS and PS

	m_spMaterialBuffer = std::make_shared<MnMaterialBuffer>();
	assert(m_spMaterialBuffer != nullptr);
	result = m_spMaterialBuffer->Init(cpDevice, _CONST_BUF_MATERIAL, MN_CONSTANT_BUFFER_BELONG_PS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spMaterialBuffer));
		return result;
	}

	m_spBonePaletteBuffer = std::make_shared<MnBonePaletteBuffer>();
	assert(m_spBonePaletteBuffer != nullptr);
	result = m_spBonePaletteBuffer->Init(cpDevice, _CONST_BUF_BONE_PALETTE, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spBonePaletteBuffer));
		return result;
	}

	return result;
}

void ForwardShader::SetWorldBuffer(const DirectX::SimpleMath::Matrix& matWorld)
{
	m_spWorldBuffer->SetWorldTransform(MnFramework::renderAPI.GetD3DDeviceContext(), matWorld);
}
void ForwardShader::SetViewProjectionBuffer(const DirectX::SimpleMath::Matrix& matView, const DirectX::SimpleMath::Matrix& matProjection)
{
	m_spViewProjectionBuffer->SetViewProjectionTransform(MnFramework::renderAPI.GetD3DDeviceContext(), matView, matProjection);
}
void ForwardShader::SetLightBuffer(const std::shared_ptr<MnLightSource> spLight)
{
	m_spLightBuffer->SetLight(MnFramework::renderAPI.GetD3DDeviceContext(), spLight);
}
void ForwardShader::SetMaterial(const std::shared_ptr<MnMaterial> spMaterial)
{
	m_spMaterialBuffer->SetMaterial(MnFramework::renderAPI.GetD3DDeviceContext(), spMaterial);
}
void ForwardShader::SetBonePalette(const std::shared_ptr<MnSkeleton> spSkeleton)
{
	m_spBonePaletteBuffer->SetBonePalette(MnFramework::renderAPI.GetD3DDeviceContext(), spSkeleton);
}

void ForwardShader::Render(const CPD3DShaderResourceView& prevRenderedScene)
{
	auto& renderAPI = MnFramework::renderAPI;
	auto& cpDeviceContext = renderAPI.GetD3DDeviceContext();


	//���� ��� ����Ÿ�� ����
	auto finalRenderTarget = GetFinalRenderTarget();
	MnFramework::renderAPI.SetRenderTarget(finalRenderTarget->GetRenderTargetView(), finalRenderTarget->GetDepthStencilView());


	//���̴� ����
	renderAPI.SetVertexShader(m_spShaderPath->GetVertexShader());
	renderAPI.SetPixelShader(m_spShaderPath->GetPixelShader());
	renderAPI.SetInputLayout(m_spShaderPath->GetInputLayout());

	//������� ����
	renderAPI.SetConstantBufferVS(m_spWorldBuffer->GetBuffer(), 0);
	renderAPI.SetConstantBufferVS(m_spViewProjectionBuffer->GetBuffer(), 1);
	renderAPI.SetConstantBufferVS(m_spLightBuffer->GetBuffer(), 2);
	renderAPI.SetConstantBufferVS(m_spBonePaletteBuffer->GetBuffer(), 3);
	renderAPI.SetConstantBufferPS(m_spLightBuffer->GetBuffer(), 0);
	renderAPI.SetConstantBufferPS(m_spMaterialBuffer->GetBuffer(), 1);

	/*****************������ ����************************/
	auto compLightList = _GameWorld()->GetComponent<LightList>();
	//���� ������ �ƹ��͵� �Ⱥ��̴¹�
	if (compLightList == nullptr) return;

	auto& lstLight = compLightList->GetLights();
	//�׽�Ʈ��. ���߿� ��� ����Ʈ�� �ѹ��� ����
	auto testLight = lstLight[0];
	m_spLightBuffer->SetLight(cpDeviceContext, testLight);


	/************ī�޶� ����*****************************/
	auto& camera = _GameWorld()->GetMainCamera();
	//ī�޶� ������ ���̴°� ����
	if (camera == nullptr) return;
	
	m_spViewProjectionBuffer->SetViewProjectionTransform(cpDeviceContext, camera->GetViewMatrix(), camera->GetProjectionMatrix());


	for (auto& obj : m_renderQueue)
	{
		auto compTransform = obj->GetComponent<Transform>();
		//Transform ������Ʈ�� ���ٸ� ������ ���� �ʴ´�
		if (compTransform == nullptr) continue;

		auto compMesh = obj->GetComponent<Mesh>();
		//Mesh ������Ʈ�� ���ٸ� ������ ���� �ʴ´�
		if (compMesh == nullptr) continue;

		/*****************���� ��ȯ ����************************/
		m_spWorldBuffer->SetWorldTransform(cpDeviceContext, compTransform->GetTransformMatrix());

		/*****************�� �ȷ�Ʈ ����************************/
		m_spBonePaletteBuffer->SetBonePalette(cpDeviceContext, compMesh->GetSkeleton());

		/*****************���׸��� ����************************/
		auto compMaterial = obj->GetComponent<Material>();
		if (compMaterial == nullptr)
		{
			//����Ʈ ���׸��� ���
		}
		auto material = compMaterial->GetMaterial();
		if(material != nullptr)
			m_spMaterialBuffer->SetMaterial(cpDeviceContext,compMaterial->GetMaterial());

		/*****************�ؽ��� ����************************/
		std::shared_ptr<MnMeshTexture> diffuseTexture = nullptr;

		auto compTexture = obj->GetComponent<Texture>();
		if (compTexture == nullptr)
		{
			//����Ʈ �ؽ��� (���) ���
		}

		if (compTexture != nullptr)
		{
			auto diffuseTexture = compTexture->GetTexture(MN_TEXTURE_DIFFUSE);
			if (diffuseTexture == nullptr)
			{
				//����Ʈ �ؽ��� ���...
			}
			renderAPI.SetShaderResoureView(diffuseTexture->GetShaderResourceView(), 0);
		}

		//��ο���
		auto mesh = compMesh->GetMesh();
		if(mesh != nullptr)
			_RenderMesh(mesh);
	}

	//���� ť�� ����
	_ClearQueue();
}