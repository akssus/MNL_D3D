#include "MnBoneAnimation.h"

using namespace MNL;

MnBoneAnimation::MnBoneAnimation():m_duration(0.0)
{

}
MnBoneAnimation::~MnBoneAnimation()
{

}
void MnBoneAnimation::SetName(const std::string& name)
{
	m_name = name;
}
const std::string& MnBoneAnimation::GetName() const
{
	return m_name;
}

void MnBoneAnimation::SetDuration(double duration)
{
	m_duration = duration;
}
const double& MnBoneAnimation::GetDuration() const
{
	return m_duration;
}
void MnBoneAnimation::AddKeyFrame(const MnBoneAnimationKeyFrame& keyFrame)
{
	m_lstKeyFrames.push_back(keyFrame);
}
UINT MnBoneAnimation::GetNumKeyFrames() const
{
	return m_lstKeyFrames.size();
}
MnBoneAnimationKeyFrame MnBoneAnimation::GetKeyFrame(UINT index) const
{
	return m_lstKeyFrames[index];
}