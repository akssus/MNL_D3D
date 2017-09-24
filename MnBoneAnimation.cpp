#include "MnBoneAnimation.h"

using namespace MNL;

MnBoneAnimation::MnBoneAnimation():m_totalDuration(0.0)
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

void MnBoneAnimation::SetTotalDuration(double duration)
{
	m_totalDuration = duration;
}
const double& MnBoneAnimation::GetTotalDuration() const
{
	return m_totalDuration;
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
MnBoneAnimationKeyFrame MnBoneAnimation::GetKeyFrameAtTime(float timeFactor) const
{
	UINT keyFrameIndex = GetKeyFrameIndex(timeFactor);
	return m_lstKeyFrames[keyFrameIndex];
}

UINT MnBoneAnimation::GetKeyFrameIndex(float timeFactor) const
{
	double time = timeFactor * m_totalDuration;
	int numKeyFrames = GetNumKeyFrames();
	for (int i = 0; i < numKeyFrames; ++i)
	{
		auto& keyFrame = m_lstKeyFrames[i];
		if (time <= keyFrame.keyTime)
		{
			return i-1;
		}
	}
	int lastFrameIndex = numKeyFrames - 1;
	return lastFrameIndex;
}