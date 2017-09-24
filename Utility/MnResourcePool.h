#pragma once
#include <vector>
#include <map>
#include <memory>
#include "assimp\scene.h"
#include "../Core/MnTypedefs.h"
#include "../Render\MnMesh.h"
#include "../Render/MnMesh.h"
#include "../Render/MnMeshData.h"
#include "../Render/MnMaterial.h"
#include "../Render/MnLightSource.h"
#include "../MnSkeleton.h"
#include "../MnBoneAnimation.h"
#include "../MnBoneAnimationElement.h"

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
			std::vector<MnBoneAnimation> m_lstAnimations;
		};

		struct _BoneData
		{
			UINT boneIndex[4] = { 0, };
			float boneWeight[4] = { 0.0f, };
		};

	public:
		MnResourcePool();
		~MnResourcePool();

		/**
		Load meshes from file into the model package
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType);
		/**
		Load only a specific mesh in the file
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::string& fileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName);

	public:
		/**
		Find mesh in the model package.
		@return nullptr if modelPackage unfound or meshName unfound
		*/
		std::shared_ptr<MnMeshData> GetMeshData(const std::string& modelPackageName, const std::string& meshName) const;
		MnBoneAnimation GetBoneAnimation(const std::string& modelPackageName, const std::string& animationName) const;
		MnBoneAnimation GetBoneAnimation(const std::string& modelPackageName, UINT index) const;

	private:
		HRESULT _LoadModelFromMemory(const _MemoryChunk& memoryChunk, std::string modelPackageName);
		HRESULT _ReadFromAssimpScene(const aiScene* scene);

		/**
		Every sub mesh's vertices are serialized in unified lists in a MnMeshData.
		Each sub meshes has index offset so that a sub mesh is conceptually allocated in a partial space in the serialized list of MnMeshData
		*/
		HRESULT _ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene,const aiNode* node, UINT parentIndex, _ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType);
		std::shared_ptr<MnMeshData> _ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType);
		UINT _GetNodesTotalVertexCount(const aiScene* scene,const aiNode* node);
		UINT _GetNodesTotalIndexCount(const aiScene* scene,const aiNode* node);
		std::shared_ptr<MnSkeleton> _CreateSkeleton(const aiScene* scene, const aiNode* node);
		const aiNode* _FindRootBoneNode(const aiScene* scene, const aiNode* currentMeshNode, const aiBone* bone);

		void _ReadBoneData(const aiScene* scene, const aiNode* node, std::shared_ptr<MnCustomVertexType> vertexType, UINT numVertices, std::vector<_BoneData>& boneData);
		void _ReadMeshVertices(const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType, UINT numVertices, std::vector<float>& vertexArray, const std::vector<_BoneData>& boneData);
		void _ReadMeshIndices(const aiScene* scene, const aiNode* node, std::shared_ptr<MnMeshData>& meshData, UINT numIndices, std::vector<UINT>& indexArray);
		MnSubMesh _CreateSubMesh(const aiMesh* mesh, UINT indexBase);
		HRESULT _InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray, UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount);

		HRESULT _ReadAnimations(const aiScene* scene, _ModelPackage& modelPackage);
	private:
		std::map<std::string, _ModelPackage> m_modelPackages;
	};

}