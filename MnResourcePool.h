#pragma once
#include <vector>
#include <map>
#include <memory>
#include "assimp\scene.h"
#include "Core/MnTypedefs.h"
#include "Utility\MnMesh.h"
#include "Utility/MnMesh.h"
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
		A model file equals to a model package. Only read meshes and ignores lights and materials
		*/
		struct _ModelPackage
		{
			std::string m_packageName;
			std::vector<std::shared_ptr<MnMeshData> > m_lstSpMeshes;
		};

	public:
		MnResourcePool();
		~MnResourcePool();

		/*
		Load meshes from file into the model package
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType);
		/*
		Load only a specific mesh in the file
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName);

		

	public:
		/*
		Find mesh in the model package.
		@return nullptr if modelPackage unfound or meshName unfound
		*/
		std::shared_ptr<MnMeshData> GetMeshData(const std::string& modelPackageName, const std::string& meshName) const;

	private:
		HRESULT _LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName);
		HRESULT _ReadFromAssimpScene(const aiScene* scene);

		/*
		Every sub mesh's vertices are serialized in unified lists in a MnMeshData.
		Each sub meshes has index offset so that a sub mesh is conceptually allocated in a partial space in the serialized list of MnMeshData
		*/
		HRESULT _ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene,const aiNode* node, UINT parentIndex, _ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType);
		std::shared_ptr<MnMeshData> _ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType);
		HRESULT _InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray, UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount);

	private:
		std::map<std::string, _ModelPackage> m_modelPackages;
	};

}