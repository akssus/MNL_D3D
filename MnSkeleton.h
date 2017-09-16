#pragma once
#include <d3d11.h>
#include <vector>
#include "DXTK\SimpleMath.h"
#include "Core\MnTypedefs.h"
#include "MnBone.h"
#include "MnMatrixPalette.h"

namespace MNL
{
	class MnSkeleton
	{
	public:
		MnSkeleton();
		~MnSkeleton();

		void AddBone(const MnBone& bone);
		UINT GetNumBones() const;

	public:
		/**
		Update bone property. if bone name does not exist, do nothing 
		*/
		void UpdateBone(const std::string& boneName, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotation, const DirectX::SimpleMath::Vector3& scale);

		/*
		Number of matrix is 96. This is fixed specification
		*/
		D3D11_SUBRESOURCE_DATA GetBonePalette();
	private:
		/**
		@return -1 if bone is not exist
		*/
		int _GetBoneIndex(const std::string& boneName);
	private:
		std::vector<MnBone> m_lstBones;
		std::vector<DirectX::SimpleMath::Matrix> m_lstBoneMatrix;

	};
}
