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

void MnSkinnedMeshRenderer::SetWorldBuffer(MnRenderAPI& renderAPI,
	const DirectX::SimpleMath::Matrix& matWorld)
{
	//row major to column major
	_WorldBufferType bufferType;
	bufferType.matWorld = matWorld.Transpose();

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	UpdateConstantBuffer(renderAPI, _CONST_BUF_WORLD, data);
}

void MnSkinnedMeshRenderer::SetViewProjectionBuffer(MnRenderAPI& renderAPI,
	const DirectX::SimpleMath::Matrix& matView,
	const DirectX::SimpleMath::Matrix& matProjection)
{
	//row major to column major
	_ViewProjectionBufferType bufferType;
	bufferType.matView = matView.Transpose();
	bufferType.matProjection = matProjection.Transpose();

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	UpdateConstantBuffer(renderAPI, _CONST_BUF_VIEWPROJECTION, data);
}
void MnSkinnedMeshRenderer::SetLightBuffer(MnRenderAPI& renderAPI, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType)
{
	_LightBufferType bufferType;
	bufferType.lightPos = Vector4(lightPos);
	bufferType.lightDir = Vector4(lightDir);
	bufferType.lightType = lightType;
	bufferType.padding = Vector3(0.0f, 0.0f, 0.0f);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	UpdateConstantBuffer(renderAPI, _CONST_BUF_LIGHT_VS, data);
	UpdateConstantBuffer(renderAPI, _CONST_BUF_LIGHT_PS, data);
}
void MnSkinnedMeshRenderer::SetLightBuffer(MnRenderAPI& renderAPI, const std::shared_ptr<MnLightSource> spLight)
{
	SetLightBuffer(renderAPI, spLight->GetPosition(), spLight->GetDirection(), spLight->GetLightType());
}

void MnSkinnedMeshRenderer::SetMaterial(MnRenderAPI& renderAPI,
	const DirectX::SimpleMath::Vector4& diffuse,
	const DirectX::SimpleMath::Vector4& ambient,
	const DirectX::SimpleMath::Vector4& emissive,
	const DirectX::SimpleMath::Vector4& specular,
	float specularPower)
{
	_MaterialBufferType bufferType;
	ZeroMemory(&bufferType, sizeof(_MaterialBufferType));
	bufferType.diffuse = diffuse;
	bufferType.ambient = ambient;
	bufferType.emissive = emissive;
	bufferType.specular = specular;
	bufferType.specularPower = specularPower;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	UpdateConstantBuffer(renderAPI, _CONST_BUF_MATERIAL, data);
}
void MnSkinnedMeshRenderer::SetMaterial(MnRenderAPI& renderAPI, const std::shared_ptr<MnMaterial> spMaterial)
{
	SetMaterial(renderAPI, spMaterial->diffuse, spMaterial->ambient, spMaterial->emissive, spMaterial->specular, spMaterial->specularPower);
}
void MnSkinnedMeshRenderer::SetBonePalette(MnRenderAPI& renderAPI, const std::shared_ptr<MnSkeleton> spSkeleton)
{
	SetBonePalette(renderAPI, spSkeleton->GetBonePalette());
}
void MnSkinnedMeshRenderer::SetBonePalette(MnRenderAPI& renderAPI, const D3D11_SUBRESOURCE_DATA bonePalette)
{
	UpdateConstantBuffer(renderAPI, _CONST_BUF_BONE_PALETTE, bonePalette);
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
	auto worldBufferType = std::make_shared<MnConstantBufferType>();
	assert(worldBufferType != nullptr);
	worldBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	auto worldBuffer = std::make_shared<MnConstantBuffer>();
	assert(worldBuffer != nullptr);

	//world buffer is index 0 of vertex shader
	HRESULT result = worldBuffer->Init(cpDevice, worldBufferType, _CONST_BUF_WORLD, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	_AddConstantBuffer(worldBuffer);

	return S_OK;
}
HRESULT MnSkinnedMeshRenderer::_InitViewProjectionBuffer(const CPD3DDevice& cpDevice)
{
	auto viewProjectionBufferType = std::make_shared<MnConstantBufferType>();
	assert(viewProjectionBufferType != nullptr);
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	auto viewProjectionBuffer = std::make_shared<MnConstantBuffer>();
	assert(viewProjectionBuffer != nullptr);

	HRESULT result = viewProjectionBuffer->Init(cpDevice, viewProjectionBufferType, _CONST_BUF_VIEWPROJECTION, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	_AddConstantBuffer(viewProjectionBuffer);

	return S_OK;
}
HRESULT MnSkinnedMeshRenderer::_InitLightBuffer(const CPD3DDevice& cpDevice)
{
	auto lightBufferType = std::make_shared<MnConstantBufferType>();
	assert(lightBufferType != nullptr);
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_UINT));
	lightBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT3));//padding

	auto lightBufferVS = std::make_shared<MnConstantBuffer>();
	assert(lightBufferVS != nullptr);

	HRESULT result = lightBufferVS->Init(cpDevice, lightBufferType, _CONST_BUF_LIGHT_VS, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	//light buffer uses in both VS and PS
	_AddConstantBuffer(lightBufferVS);

	auto lightBufferPS = std::make_shared<MnConstantBuffer>();
	assert(lightBufferPS != nullptr);

	result = lightBufferPS->Init(cpDevice, lightBufferType, _CONST_BUF_LIGHT_PS, MN_CONSTANT_BUFFER_BELONG_PS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	//light buffer uses in both VS and PS
	_AddConstantBuffer(lightBufferPS);

	return S_OK;
}
HRESULT MnSkinnedMeshRenderer::_InitMaterialBuffer(const CPD3DDevice& cpDevice)
{
	auto materialBufferType = std::make_shared<MnConstantBufferType>();
	assert(materialBufferType != nullptr);
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT4));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT1));
	materialBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_FLOAT3)); //padding

	auto materialBuffer = std::make_shared<MnConstantBuffer>();
	assert(materialBuffer != nullptr);

	//world buffer is index 0 of vertex shader
	HRESULT result = materialBuffer->Init(cpDevice, materialBufferType, _CONST_BUF_MATERIAL, MN_CONSTANT_BUFFER_BELONG_PS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	_AddConstantBuffer(materialBuffer);

	return S_OK;
}

HRESULT MnSkinnedMeshRenderer::_InitBonePaletteBuffer(const CPD3DDevice& cpDevice)
{
	auto bufferType = std::make_shared<MnConstantBufferType>();
	assert(bufferType != nullptr);

	//this is bullshit, please find other way later
	for (UINT i = 0; i < 96; ++i)
	{
		bufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	}

	auto constBuffer = std::make_shared<MnConstantBuffer>();
	assert(constBuffer != nullptr);

	//world buffer is index 0 of vertex shader
	HRESULT result = constBuffer->Init(cpDevice, bufferType, _CONST_BUF_BONE_PALETTE, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return result;
	}
	_AddConstantBuffer(constBuffer);

	return S_OK;
}