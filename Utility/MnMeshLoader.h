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
		std::shared_ptr<MnMeshData> m_spMeshData;
		std::vector<std::shared_ptr<MnBoneAnimation>> m_lstSpAnimations;

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

	class _SkeletonBoneReferenceTable
	{
	public:
		struct _BoneReference
		{
			std::string name;
			std::string parentName;
		};

		_SkeletonBoneReferenceTable() : m_boneCount(0) {};
		~_SkeletonBoneReferenceTable() {};

		void AddBoneName(const std::string& boneName, const std::string& parentName)
		{
			m_boneTable[m_boneCount] = _BoneReference{ boneName ,parentName };
			m_boneCount++;
		}

		void SetRootBoneName(const std::string& rootBoneName)
		{
			m_rootBoneName = rootBoneName;
		}

		const std::string& GetRootBoneName() const
		{
			return m_rootBoneName;
		}

		int GetBoneCount() const
		{
			return m_boneCount;
		}

		_BoneReference GetBoneReference(int index) const
		{
			return m_boneTable.at(index);
		}

	private:
		int m_boneCount;
		std::string m_rootBoneName;
		std::unordered_map<int, _BoneReference> m_boneTable;

	};

	class MnMeshLoader
	{
		struct _BoneData
		{
			float boneIndex[4] = { 0.0f, };
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

	private:
		const aiNode* _FindAncestor(const aiScene* scene, const aiNode* currentNode);
		/**
		@return ��Ʈ����尡 ���� ��� nullptr ��ȯ
		*/
		const aiNode* _FindRootBoneNode(const aiScene* scene);
		HRESULT _EstablishSkeletonTable(_SkeletonBoneReferenceTable& skeletonTable, const aiNode* rootBoneNode);
		void _ProcessBoneNode(_SkeletonBoneReferenceTable& skeletonTable, const aiNode* boneNode);
		const aiBone* _FindBoneByName(const std::string& targetBoneName, const aiScene* pScene);
		std::shared_ptr<MnSkeleton> _CreateSkeleton(_SkeletonBoneReferenceTable& skeletonTable, const aiScene* pScene);
		/**
		@brief ���� ��带 �������� ��� aiNode �� �޽õ��� ��������� �ε��Ѵ�.
		*/
		HRESULT _ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, std::shared_ptr<MnMeshData>& spMeshData, const std::shared_ptr<MnCustomVertexType>& vertexType);

		/**
		@brief aiNode �ϳ��� �������� ��� ����޽ø� �ε��Ѵ�.. aiNode �� �� ����޽õ��� ����ȭ�Ǿ� MnMeshData �� ����ȴ�.
		*/
		std::shared_ptr<MnSubMeshData> _ReadSingleMesh(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType, std::shared_ptr<MnSkeleton>& spSkeleton);

		UINT _GetNodesTotalVertexCount(const aiScene* scene, const aiNode* node);
		UINT _GetNodesTotalIndexCount(const aiScene* scene, const aiNode* node);
		
		void _ReadBoneData(const aiScene* scene, const aiNode* node, std::shared_ptr<MnCustomVertexType> vertexType, UINT numVertices, std::vector<_BoneData>& boneData, std::shared_ptr<MnSkeleton>& skeleton);
		void _ReadMeshVertices(const aiScene* scene, const aiNode* node, const std::shared_ptr<MnCustomVertexType>& vertexType, UINT numVertices, std::vector<float>& vertexArray, const std::vector<_BoneData>& boneData);
		void _ReadMeshIndices(const aiScene* scene, const aiNode* node, std::shared_ptr<MnSubMeshData>& meshData, UINT numIndices, std::vector<UINT>& indexArray);
		MnSubMeshFragment _CreateSubMeshFragment(const aiMesh* mesh, UINT indexBase);

		HRESULT _InitBuffers(const CPD3DDevice& cpDevice, std::shared_ptr<MnSubMeshData> meshData, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::vector<float>& vertexArray, UINT vertexCount, const std::vector<UINT>& indexArray, UINT indexCount);

		HRESULT _ReadAnimations(const aiScene* scene, ModelPackage& modelPackage);
	};
}