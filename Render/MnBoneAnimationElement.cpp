#include "MnBoneAnimationElement.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBoneAnimationElement::MnBoneAnimationElement():m_duration(0.0)
{

}
MnBoneAnimationElement::~MnBoneAnimationElement()
{

}
void MnBoneAnimationElement::AddKeyFrame(const MnBoneAnimationKeyFrame& key)
{
	m_lstKeyFrames.push_back(key);
}
void MnBoneAnimationElement::SetAffectingBoneName(const std::string& affectingBoneName)
{
	m_affectingBoneName = affectingBoneName;
}
MnBoneAnimationKeyFrame MnBoneAnimationElement::GetKeyFrame(UINT index) const
{
	return m_lstKeyFrames[index];
}
void MnBoneAnimationElement::SetDuration(double duration)
{
	m_duration = duration;
}

double MnBoneAnimationElement::GetDuration() const
{
	return m_duration;
}
UINT MnBoneAnimationElement::GetNumKeyFrames() const
{
	return m_lstKeyFrames.size();
}
std::string MnBoneAnimationElement::GetAffectingBoneName() const
{
	return m_affectingBoneName;
}
MnBoneAnimationKeyFrame MnBoneAnimationElement::GetLerpedKeyFrameAtTime(float timeFactor)
{
	double currentTime = timeFactor * m_duration;

	UINT currentKeyFrameIndex = GetKeyFrameIndexAtTime(timeFactor);
	UINT nextKeyFrameIndex = _GetNextKeyFrameIndexOf(currentKeyFrameIndex);

	auto currentKeyFrame = GetKeyFrame(currentKeyFrameIndex);
	auto nextKeyFrame = GetKeyFrame(nextKeyFrameIndex);

	float factor = 1.0f;
	bool isNotLastKeyFrame = currentKeyFrameIndex != nextKeyFrameIndex;
	if (isNotLastKeyFrame)
	{
		factor = (currentTime - currentKeyFrame.keyTime) / (nextKeyFrame.keyTime - currentKeyFrame.keyTime);
	}

	auto lerpedKeyFrame = _LerpKeyFrame(currentKeyFrame, nextKeyFrame, factor);

	return lerpedKeyFrame;
}

MnBoneAnimationKeyFrame MnBoneAnimationElement::GetKeyFrameAtTime(float timeFactor) const
{
	//prevent referencing nothing
	if (GetNumKeyFrames() <= 0) return MnBoneAnimationKeyFrame();

	UINT keyFrameIndex = GetKeyFrameIndexAtTime(timeFactor);
	return m_lstKeyFrames[keyFrameIndex];
}

UINT MnBoneAnimationElement::GetKeyFrameIndexAtTime(float timeFactor) const
{
	double time = timeFactor * m_duration;
	int numKeyFrames = GetNumKeyFrames();

	//prevent referencing nothing
	if (numKeyFrames <= 0) return 0;

	for (int i = 0; i < numKeyFrames; ++i)
	{
		auto& keyFrame = m_lstKeyFrames[i];
		if (time <= keyFrame.keyTime)
		{
			return i - 1;
		}
	}
	int lastFrameIndex = numKeyFrames - 1;
	return lastFrameIndex;
}

UINT MnBoneAnimationElement::_GetNextKeyFrameIndexOf(UINT currentIndex) const
{
	UINT nextKeyFrameIndex = currentIndex + 1;
	if (nextKeyFrameIndex >= GetNumKeyFrames())
	{
		nextKeyFrameIndex = currentIndex;
	}
	return nextKeyFrameIndex;
}

MnBoneAnimationKeyFrame MnBoneAnimationElement::_LerpKeyFrame(const MnBoneAnimationKeyFrame& keyFrame_from, const MnBoneAnimationKeyFrame& keyFrame_to, float factor)
{
	MnBoneAnimationKeyFrame lerpKeyFrame;

	lerpKeyFrame.keyPosition = Vector3::Lerp(keyFrame_from.keyPosition, keyFrame_to.keyPosition, factor);
	lerpKeyFrame.keyRotation= Quaternion::Lerp(keyFrame_from.keyRotation, keyFrame_to.keyRotation, factor);
	lerpKeyFrame.keyScale = Vector3::Lerp(keyFrame_from.keyScale, keyFrame_to.keyScale, factor);
	lerpKeyFrame.keyTime = (keyFrame_from.keyTime * factor) + (keyFrame_to.keyTime * (1 - factor));

	return lerpKeyFrame;
}
