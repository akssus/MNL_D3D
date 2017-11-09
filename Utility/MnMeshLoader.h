/**
@class MNL::MnMeshLoader
@brief assimp 를 이용한 fbx 파일 로더.
@author Akssus
@section 개요
FBX 포맷의 메시를 읽어들이는 유틸리티 클래스이다.

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
		@brief 해당 메시 이름을 가진 메시데이터를 찾아 반환한다
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
		@brief 파일의 모든 모델을 리소스풀에 로드한다.
		@param fileOut[Out] 로드된 모델 패키지가 저장될 모델패키지 객체
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& wFileName, const std::shared_ptr<MnCustomVertexType>& vertexType, ModelPackage& modelPackageOut);

		/**
		@brief FBX 파일의 특정 모델만을 로드한다.
		@param meshName FBX 파일 내 메시의 이름.
		@param meshDataOut[Out] 로드된 메시는 meshDataOut에 씌여진다.
		*/
		HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& wFileName, const std::shared_ptr<MnCustomVertexType>& vertexType, const std::string& meshName, std::shared_ptr<MnMeshData>& meshDataOut);

	private:
		/**
		@brief 시작 노드를 기준으로 모든 aiNode 의 메시들을 재귀적으로 로드한다.
		*/
		HRESULT _ReadMeshes(const CPD3DDevice& cpDevice, const aiScene* scene, const aiNode* node, UINT parentIndex, ModelPackage& modelPackage, const std::shared_ptr<MnCustomVertexType>& vertexType);

		/**
		@brief aiNode 하나를 기준으로 모든 서브메시를 로드한다.. aiNode 의 각 서브메시들은 직렬화되어 MnMeshData 에 저장된다.
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