#include "MnMeshRenderer.h"

using namespace MNL;

MnMeshRenderer::MnMeshRenderer()
{
}


MnMeshRenderer::~MnMeshRenderer()
{
}


HRESULT MnMeshRenderer::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	HRESULT result = _InitConstantBuffers(cpDevice);
	if (FAILED(result))
	{
		return E_FAIL;
	}
	return S_OK;
}

void MnMeshRenderer::SetWorldBuffer(MnRenderAPI& renderAPI,
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

void MnMeshRenderer::SetViewProjectionBuffer(MnRenderAPI& renderAPI,
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
void MnMeshRenderer::SetLightBuffer(MnRenderAPI& renderAPI, const DirectX::SimpleMath::Vector3& lightPos, const DirectX::SimpleMath::Vector3& lightDir, MN_LIGHT_TYPE lightType)
{
	_LightBufferType bufferType;
	bufferType.lightPos = lightPos;
	bufferType.lightDir = lightDir;
	bufferType.lightType = lightType;
	bufferType.padding = 0.0f;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &bufferType;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	UpdateConstantBuffer(renderAPI, _CONST_BUF_LIGHT, data);
}
void MnMeshRenderer::SetLightBuffer(MnRenderAPI& renderAPI, const MnLightSource& light)
{
	SetLightBuffer(renderAPI,light.GetPosition(), light.GetDirection(), light.GetLightType());
}

void MnMeshRenderer::SetMaterial(MnRenderAPI& renderAPI,
	const DirectX::SimpleMath::Vector4& diffuse,
	const DirectX::SimpleMath::Vector4& ambient,
	const DirectX::SimpleMath::Vector4& emissive,
	const DirectX::SimpleMath::Vector4& specular,
	float specularPower)
{
	_MaterialBufferType bufferType;
	bufferType.diffuse = diffuse;
	bufferType.ambient = ambient;
	bufferType.emissive = emissive;
	bufferType.specular = specular;
	bufferType.specularPower = specularPower;
}
void MnMeshRenderer::SetMaterial(MnRenderAPI& renderAPI, const MnMaterial& material)
{

}

HRESULT MnMeshRenderer::_InitConstantBuffers(const CPD3DDevice& cpDevice)
{
	//allocate 
	_ClearConstantBuffers();

	//make world buffer
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
		return E_FAIL;
	}
	_AddConstantBuffer(worldBuffer);

	//make world buffer
	auto viewProjectionBufferType = std::make_shared<MnConstantBufferType>();
	assert(viewProjectionBufferType != nullptr);
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));
	viewProjectionBufferType->AddConstantElement(MnConstantElement(MN_CONSTANT_ELEMENT_TYPE_MATRIX));

	auto viewProjectionBuffer = std::make_shared<MnConstantBuffer>();
	assert(viewProjectionBuffer != nullptr);

	//world buffer is index 0 of vertex shader
	result = viewProjectionBuffer->Init(cpDevice, viewProjectionBufferType, _CONST_BUF_VIEWPROJECTION, MN_CONSTANT_BUFFER_BELONG_VS);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	_AddConstantBuffer(viewProjectionBuffer);

	return S_OK;
}