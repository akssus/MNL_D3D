#pragma once
#include <vector>
#include <map>
#include <memory>
#include "assimp\scene.h"
#include "Utility\MnMesh.h"
#include "MnGenericVertexStruct.h"


namespace MNL
{
	class MnResourcePool
	{
		struct _MemoryChunk
		{
			std::unique_ptr<char> pData;
			UINT dataSize;
		};
		/*
		A model file equals to a model package
		*/
		struct _ModelPackage
		{
			std::string m_packageName;
			std::vector<MnMesh> m_lstMeshes;
			//and light, materials, etc
		};

	public:
		MnResourcePool();
		~MnResourcePool();

		HRESULT LoadModelFromFile(const std::string& fileName);

	private:
		HRESULT _LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName);
		HRESULT _ReadFromAssimpScene(const aiScene* scene);

	private:
		std::map<std::string, _ModelPackage> m_modelPackages;
	};

}