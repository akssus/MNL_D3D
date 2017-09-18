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
	m_lstBones.push_back(bone);
	m_lstBoneMatrix[GetNumBones()-1] = bone.GetTransform().Transpose();
}

UINT MnSkeleton::GetNumBones() const
{
	return m_lstBones.size();
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

	m_lstBoneMatrix[boneIndex] = bone.GetTransform().Transpose();
}

D3D11_SUBRESOURCE_DATA MnSkeleton::GetBonePalette()
{
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = m_lstBoneMatrix.data();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	return data;
}
int MnSkeleton::_GetBoneIndex(const std::string& boneName)
{
	// is it... too complicated..? Doubtful
	auto it_bone = std::find_if(m_lstBones.begin(), m_lstBones.end(), [&](MnBone& bone) {
		if (bone.GetName() == boneName) 
			return true;
		return false;
	});
	if (it_bone == m_lstBones.end())
	{
		//bone not found
		return -1;
	}
	int index = std::distance(m_lstBones.begin(), it_bone);
	return index;
}