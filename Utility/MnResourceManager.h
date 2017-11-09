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
		@return 리소스가 존재하지 않을 경우 디폴트 메시데이터 반환
		*/
		std::shared_ptr<ModelPackage> GetModelPackage(const std::wstring& modelPackageName);

		/**
		@return 텍스쳐가 존재하지 않을 경우 디폴트 텍스쳐 반환
		*/
		std::shared_ptr<MnMeshTexture> GetTexture(const std::wstring& filePath);
	private:
		//void _Init();

	private:
		MnResourcePool<ModelPackage> m_modelPackagePool;
		MnResourcePool<MnMeshTexture> m_meshTexturePool;
	};
}