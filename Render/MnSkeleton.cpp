#include "MnSkeleton.h"
#include <algorithm>

using namespace MNL;
using namespace DirectX::SimpleMath;

MnSkeleton::MnSkeleton()
{
	m_lstBoneMatrix.resize(96);
	ZeroMemory(m_lstBoneMatrix.data(), sizeof(Matrix) * m_lstBoneMatrix.size());
}

MnSkeleton::~MnSkeleton()
{
}


void MnSkeleton::AddBone(const MnBone& bone)
{
	UINT boneIndex = m_lstBones.size();
	m_boneIndexHashTable[bone.GetName()] = boneIndex;

	m_lstBones.push_back(bone);
	m_lstBoneMatrix[GetNumBones() - 1] = (bone.GetOffsetTransform() * bone.GetTransform()).Transpose();
	m_boneTree[bone.GetParentName()].push_back(bone.GetName());
}

UINT MnSkeleton::GetNumBones() const
{
	return m_lstBones.size();
}

UINT MnSkeleton::GetBoneIndexByName(const std::string& boneName)
{
	return _GetBoneIndex(boneName);
}

std::string MnSkeleton::GetBoneName(UINT index) const
{
	return m_lstBones[index].GetName();
}
void MnSkeleton::SetRootBoneName(const std::string& rootBoneName)
{
	m_rootBoneName = rootBoneName;
}
void MnSkeleton::UpdateBone(const std::string& boneName, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotation, const DirectX::SimpleMath::Vector3& scale)
{
	int boneIndex = _GetBoneIndex(boneName);
	if (boneIndex == -1)
	{
		//bone is not exist
		return;
	}
	auto& bone = m_lstBones[boneIndex];
	bone.SetTransform(position, rotation, scale);
}

void MnSkeleton::ReposeBones()
{
	_ReposeBone(m_rootBoneName, Matrix::Identity);
}
void MnSkeleton::_ReposeBone(const std::string& boneName, const DirectX::SimpleMath::Matrix& baseMatrix)
{
	int boneIndex = _GetBoneIndex(boneName);
	if (boneIndex == -1)
	{
		//bone is not exist
		return;
	}
	auto& bone = m_lstBones[boneIndex];
	Matrix stackedMatrix = bone.GetTransform() * baseMatrix;
	Matrix reposedMatrix = bone.GetOffsetTransform() * stackedMatrix;
	m_lstBoneMatrix[boneIndex] = reposedMatrix.Transpose();

	const auto& lstChildren = m_boneTree[boneName];
	for (const auto& childName : lstChildren)
	{
		_ReposeBone(childName, stackedMatrix);
	}
}

D3D11_SUBRESOURCE_DATA MnSkeleton::GetBonePalette()
{
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = m_lstBoneMatrix.data();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	return data;
}
UINT MnSkeleton::_GetBoneIndex(const std::string& boneName)
{
	return m_boneIndexHashTable[boneName];
}