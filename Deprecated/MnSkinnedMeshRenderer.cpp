#include "MnSkinnedMeshRenderer.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnSkinnedMeshRenderer::MnSkinnedMeshRenderer()
{
}

MnSkinnedMeshRenderer::~MnSkinnedMeshRenderer()
{
}

HRESULT MnSkinnedMeshRenderer::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	HRESULT result = _InitConstantBuffers(cpDevice);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	return S_OK;
}

void MnSkinnedMeshRenderer::SetWorldBuffer(const CPD3DDeviceContext& cpDeviceContext,
	const DirectX::SimpleMath::Matrix& matWorld)
{
	m_spWorldBuffer->SetWorldTransform(cpDeviceContext, matWorld);
}
void MnSkinnedMeshRenderer::SetViewProjectionBuffer(const CPD3DDeviceContext& cpDeviceContext,
	const DirectX::SimpleMath::Matrix& matView,
	const DirectX::SimpleMath::Matrix& matProjection)
{
	m_spViewProjectionBuffer->SetViewProjectionTransform(cpDeviceContext, matView, matProjection);
}
void MnSkinnedMeshRenderer::SetLightBuffer(const CPD3DDeviceContext& cpDeviceContext, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType)
{
	m_spLightBuffer->SetLight(cpDeviceContext, lightPos, lightDir, lightType);
}
void MnSkinnedMeshRenderer::SetLightBuffer(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnLightSource> spLight)
{
	m_spLightBuffer->SetLight(cpDeviceContext, spLight->GetPosition(), spLight->GetDirection(), spLight->GetLightType());
}

void MnSkinnedMeshRenderer::SetMaterial(const CPD3DDeviceContext& cpDeviceContext,
	const DirectX::SimpleMath::Vector4& diffuse,
	const DirectX::SimpleMath::Vector4& ambient,
	const DirectX::SimpleMath::Vector4& emissive,
	const DirectX::SimpleMath::Vector4& specular,
	float specularPower)
{
	m_spMaterialBuffer->SetMaterial(cpDeviceContext, diffuse, ambient, emissive, specular, specularPower);
}
void MnSkinnedMeshRenderer::SetMaterial(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnMaterial> spMaterial)
{
	m_spMaterialBuffer->SetMaterial(cpDeviceContext, spMaterial->diffuse, spMaterial->ambient, spMaterial->emissive, spMaterial->specular, spMaterial->specularPower);
}
void MnSkinnedMeshRenderer::SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const std::shared_ptr<MnSkeleton> spSkeleton)
{
	m_spBonePaletteBuffer->SetBonePalette(cpDeviceContext, spSkeleton->GetBonePalette());
}
void MnSkinnedMeshRenderer::SetBonePalette(const CPD3DDeviceContext& cpDeviceContext, const D3D11_SUBRESOURCE_DATA bonePalette)
{
	m_spBonePaletteBuffer->SetBonePalette(cpDeviceContext, bonePalette);
}

HRESULT MnSkinnedMeshRenderer::_InitConstantBuffers(const CPD3DDevice& cpDevice)
{
	//clear buffers
	_ClearConstantBuffers();

	//make world buffer
	HRESULT result = _InitWolrdBuffer(cpDevice);
	if (FAILED(result))
	{
		return result;
	}

	//make view projection buffer
	result = _InitViewProjectionBuffer(cpDevice);
	if (FAILED(result))
	{
		return result;
	}

	//make light buffer
	result = _InitLightBuffer(cpDevice);
	if (FAILED(result))
	{
		return result;
	}

	//make material buffer
	result = _InitMaterialBuffer(cpDevice);
	if (FAILED(result))
	{
		return result;
	}

	//make material buffer
	result = _InitBonePaletteBuffer(cpDevice);
	if (FAILED(result))
	{
		return result;
	}

	return S_OK;
}

HRESULT MnSkinnedMeshRenderer::_InitWolrdBuffer(const CPD3DDevice& cpDevice)
{
	m_spWorldBuffer = std::make_shared<MnWorldTransformBuffer>();
	assert(m_spWorldBuffer != nullptr);
	HRESULT result = m_spWorldBuffer->Init(cpDevice, _CONST_BUF_WORLD, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		return result;
	}
	_AddConstantBuffer(m_spWorldBuffer);

	return S_OK;
}
HRESULT MnSkinnedMeshRenderer::_InitViewProjectionBuffer(const CPD3DDevice& cpDevice)
{
	m_spViewProjectionBuffer = std::make_shared<MnViewProjectionTransformBuffer>();
	assert(m_spViewProjectionBuffer != nullptr);
	HRESULT result = m_spViewProjectionBuffer->Init(cpDevice, _CONST_BUF_VIEWPROJECTION, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		return result;
	}
	_AddConstantBuffer(m_spViewProjectionBuffer);

	return S_OK;
}
HRESULT MnSkinnedMeshRenderer::_InitLightBuffer(const CPD3DDevice& cpDevice)
{
	m_spLightBuffer = std::make_shared<MnLightBuffer>();
	assert(m_spLightBuffer != nullptr);
	HRESULT result = m_spLightBuffer->Init(cpDevice, _CONST_BUF_LIGHT, MN_CONSTANT_BUFFER_BELONG_BOTH);
	if (FAILED(result))
	{
		return result;
	}
	//light buffer uses in both VS and PS
	_AddConstantBuffer(m_spLightBuffer);

	return S_OK;
}
HRESULT MnSkinnedMeshRenderer::_InitMaterialBuffer(const CPD3DDevice& cpDevice)
{
	m_spMaterialBuffer = std::make_shared<MnMaterialBuffer>();
	HRESULT result = m_spMaterialBuffer->Init(cpDevice, _CONST_BUF_MATERIAL, MN_CONSTANT_BUFFER_BELONG_PS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	_AddConstantBuffer(m_spMaterialBuffer);

	return S_OK;
}

HRESULT MnSkinnedMeshRenderer::_InitBonePaletteBuffer(const CPD3DDevice& cpDevice)
{
	m_spBonePaletteBuffer = std::make_shared<MnBonePaletteBuffer>();
	HRESULT result = m_spBonePaletteBuffer->Init(cpDevice, _CONST_BUF_BONE_PALETTE, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	_AddConstantBuffer(m_spBonePaletteBuffer);

	return S_OK;
}