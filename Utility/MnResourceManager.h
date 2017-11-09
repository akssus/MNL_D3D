#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "Core/MnTypedefs.h"
#include "Core/MnCustomVertexType.h"
#include "MnResourcePool.h"
#include "Render/MnMeshData.h"
#include "Render/MnBoneAnimation.h"
#include "Render/MnMeshTexture.h"
#include "Utility\MnMeshLoader.h"

namespace MNL
{

	template <typename T>
	class MnResourceChunk
	{
		
	};

	class MnResourceManager
	{
	public:
		MnResourceManager();
		~MnResourceManager();


		HRESULT LoadFBX(const CPD3DDevice& cpDevice, const std::wstring& filePath, const std::shared_ptr<MnCustomVertexType>& spVertexType);
		HRESULT LoadTexture(const CPD3DDevice& cpDevice, const std::wstring& filePath);

		/**
		@return ���ҽ��� �������� ���� ��� ����Ʈ �޽õ����� ��ȯ
		*/
		std::shared_ptr<ModelPackage> GetModelPackage(const std::wstring& modelPackageName);

		/**
		@return �ؽ��İ� �������� ���� ��� ����Ʈ �ؽ��� ��ȯ
		*/
		std::shared_ptr<MnMeshTexture> GetTexture(const std::wstring& filePath);
	private:
		//void _Init();

	private:
		MnResourcePool<ModelPackage> m_modelPackagePool;
		MnResourcePool<MnMeshTexture> m_meshTexturePool;
	};
}