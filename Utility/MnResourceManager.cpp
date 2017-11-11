#include "MnResourceManager.h"
#include "MnMeshLoader.h"
#include "Core/MnLog.h"

using namespace MNL;

MnResourceManager::MnResourceManager()
{
}


MnResourceManager::~MnResourceManager()
{
}

HRESULT MnResourceManager::LoadFBX(const CPD3DDevice& cpDevice, const std::wstring& filePath, const std::shared_ptr<MnCustomVertexType>& spVertexType)
{
	MnMeshLoader meshLoader;
	auto spModelPackage = std::make_shared<ModelPackage>();
	HRESULT result = meshLoader.LoadModelFromFile(cpDevice, filePath, spVertexType, *spModelPackage);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(LoadFBX));
		return result;
	}

	m_modelPackagePool.AddResource(filePath, spModelPackage);

	return result;
}
HRESULT MnResourceManager::LoadTexture(const CPD3DDevice& cpDevice, const std::wstring& filePath)
{
	auto spTexture = std::make_shared<MnMeshTexture>();
	HRESULT result = spTexture->LoadFromFile(cpDevice, filePath);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_FUNC_INFO(LoadTexture));
		return result;
	}
	m_meshTexturePool.AddResource(filePath, spTexture);

	return result;
}

std::shared_ptr<ModelPackage> MnResourceManager::GetModelPackage(const std::wstring& modelPackageName)
{
	std::shared_ptr<ModelPackage> spModelPackage = m_modelPackagePool.GetResource(modelPackageName);
	if (spModelPackage == nullptr)
	{
		//spMeshData = default mesh data
	}
	return spModelPackage;
}

std::shared_ptr<MnMeshTexture> MnResourceManager::GetTexture(const std::wstring& filePath)
{
	std::shared_ptr<MnMeshTexture> spTexture = m_meshTexturePool.GetResource(filePath);
	if (spTexture == nullptr)
	{
		//spTexture = default
	}
	return spTexture;
}