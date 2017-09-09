#pragma once
#include <vector>
#include <map>
#include <memory>
#include "assimp\scene.h"
#include "Utility\MnMesh.h"
#include "MnGenericVertexStruct.h"
#include "MnMeshData.h"
#include "MnMaterial.h"
#include "MnLightSource.h"


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
			std::vector<std::shared_ptr<MnMeshData>> m_lstSpMeshes;
			std::vector<std::shared_ptr<MnLightSource>> m_lstSpLights;
			std::vector<std::shared_ptr<MnMaterial>> m_lstSpMaterials;
		};

	public:
		MnResourcePool();
		~MnResourcePool();

		HRESULT LoadModelFromFile(const std::string& fileName);

	private:
		HRESULT _LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName);
		HRESULT _ReadFromAssimpScene(const aiScene* scene);

		/*
		Every sub mesh's vertices are serialized in unified lists in a MnMeshData.
		Each sub meshes has index offset so that a sub mesh is conceptually allocated in a partial space in the serialized list of MnMeshData
		*/
		std::shared_ptr<MnMeshData> _ReadMeshes(const aiScene* scene,const aiNode* node,const MnMeshData* pParent);


	private:
		std::map<std::string, _ModelPackage> m_modelPackages;
	};

}