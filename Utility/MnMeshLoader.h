/**
@class MNL::MnMeshLoader
@brief assimp �� �̿��� fbx ���� �δ�.
@author Akssus
@section ����
FBX ������ �޽ø� �о���̴� ��ƿ��Ƽ Ŭ�����̴�.

*/

#pragma once

#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <algorithm>
#include "assimp\scene.h"
#include "Core/MnTypedefs.h"
#include "Render/MnMesh.h"
#include "Render/MnMeshData.h"
#include "Render/MnSkeleton.h"
#include "Render/MnBoneAnimation.h"
#include "Render/MnBoneAnimationElement.h"


namespace MNL
{
	struct ModelPackage
	{
		std::wstring m_packageName;
		std::vector<std::shared_ptr<MnMeshData> > m_lstSpMeshes;
		std::vector<std::shared_ptr<MnBoneAnimation>> m_lstSpAnimations;

		/**
		@brief �ش� �޽� �̸��� ���� �޽õ����͸� ã�� ��ȯ�Ѵ�
		*/
		std::shared_ptr<MnMeshData> GetMeshData(const std::string meshName)
		{
			auto it = std::find_if(m_lstSpMeshes.begin(), m_lstSpMeshes.end(), [&](std::shared_ptr<MnMeshData>& spMeshData)
			{
				if (spMeshData->GetName() == meshName) return true;
				return false;
			});
			if (it == m_lstSpMeshes.end())
			{
				return std::shared_ptr<MnMeshData>(nullptr);
			}
			return *it;
		}

		std::shared_ptr<MnBoneAnimation> GetBoneAnimation(const std::string animName)
		{
			auto it = std::find_if(m_lstSpAnimations.begin(), m_lstSpAnimations.end(), [&](std::shared_ptr<MnBoneAnimation>& spAnim)
			{
				if (spAnim->GetName() == animName) return true;
				return false;
			});
			if (it == m_lstSpAnimations.end())
			{
				return std::shared_ptr<MnBoneAnimation>(nullptr);
			}
			return *it;
		}
	};

	class MnMeshLoader
	{
		struct _BoneData
		{
			UINT boneIndex[4] = { 0, };
			float boneWeight[4] = { 0.0f, };
		};

	public:
		MnMeshLoader();
		~MnMeshLoader();

	public:
		/**
		@brief ������ ��� ���� ���ҽ�Ǯ�� �ε��Ѵ�.
		@param fileOut[Out] �ε�� �� ��Ű���� ����� ����Ű�� ��ü
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& wFileName, const std::shared_ptr<MnCustomVertexType>& vertexType, ModelPackage& modelPackageOut);

		/**
		@brief FBX ������ Ư�� �𵨸��� �ε��Ѵ�.
		@param meshName FBX ���� �� �޽��� �̸�.
		@param meshDataOut[Out] �ε�� �޽ô� meshDataOut�� ��������.
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& wFileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName, std::shared_ptr<MnMeshData>& meshDataOut);

	private:
		/**
		@brief ���� ��带 �������� ��� aiNode �� �޽õ��� ��������� �ε��Ѵ�.
		*/
		HRESULT _ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType);

		/**
		@brief aiNode �ϳ��� �������� ��� ����޽ø� �ε��Ѵ�.. aiNode �� �� ����޽õ��� ����ȭ�Ǿ� MnMeshData �� ����ȴ�.
		*/
		std::shared_ptr<MnMeshData> _ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType);

		UINT _GetNodesTotalVertexCount(const aiScene* scene, const aiNode* node);
		UINT _GetNodesTotalIndexCount(const aiScene* scene, const aiNode* node);
		
		/**
		@brief 
		*/
		std::shared_ptr<MnSkeleton> _CreateSkeleton(const aiScene* scene, const aiNode* node);
		
		const aiNode* _FindRootBoneNode(const aiScene* scene, const aiNode* currentMeshNode, const aiBone* bone);

		void _ReadBoneData(const aiScene* scene, const aiNode* node, std::shared_ptr<MnCustomVertexType> vertexType, UINT numVertices, std::vector<_BoneData>& boneData);
		void _ReadMeshVertices(const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType, UINT numVertices, std::vector<float>& vertexArray, const std::vector<_BoneData>& boneData);
		void _ReadMeshIndices(const aiScene* scene, const aiNode* node, std::shared_ptr<MnMeshData>& meshData, UINT numIndices, std::vector<UINT>& indexArray);
		MnSubMesh _CreateSubMesh(const aiMesh* mesh, UINT indexBase);

		HRESULT _InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray, UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount);

		HRESULT _ReadAnimations(const aiScene* scene, ModelPackage& modelPackage);
	};
}