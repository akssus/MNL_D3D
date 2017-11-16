#pragma once
#include <d3d11.h>
#include <vector>
#include <unordered_map>
#include "DXTK\SimpleMath.h"
#include "Core\MnTypedefs.h"
#include "MnBone.h"
#include "MnMatrixPalette.h"

#define MN_BONE_PALETTE_SIZE 192

namespace MNL
{

	class MnSkeleton
	{
	public:
		MnSkeleton();
		~MnSkeleton();

		void AddBone(const MnBone& bone);
		UINT GetNumBones() const;
		UINT GetBoneIndexByName(const std::string& boneName);
		std::string GetBoneName(UINT index) const;
		void SetRootBoneName(const std::string& rootBoneName);

	public:
		/**
		Update bone's local transformation. if bone name does not exist, do nothing 
		*/
		void UpdateBone(const std::string& boneName, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotation, const DirectX::SimpleMath::Vector3& scale);
		/*
		Repose all the bones according to its parent's transformation
		*/
		void ReposeBones();

		/*
		Number of matrix is 96. This is fixed specification
		*/
		D3D11_SUBRESOURCE_DATA GetBonePalette();
	private:
		UINT _GetBoneIndex(const std::string& boneName);
		void _ReposeBone(const std::string& boneName, const DirectX::SimpleMath::Matrix& baseMatrix);
	
	private:
		std::string m_rootBoneName;
		std::unordered_map<std::string, std::vector<std::string>> m_boneTree;
		std::vector<MnBone>	m_lstBones;
		std::unordered_map<std::string, UINT> m_boneIndexHashTable;
		std::vector<DirectX::SimpleMath::Matrix> m_lstBoneMatrix;

	};
}
