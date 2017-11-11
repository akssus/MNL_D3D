#include "MnBoneAnimationElement.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBoneAnimationElement::MnBoneAnimationElement():m_duration(0.0)
{

}
MnBoneAnimationElement::~MnBoneAnimationElement()
{

}
void MnBoneAnimationElement::AddKeyFrameS(const MnBoneAnimationChannelKey<KeyScale>& key)
{
	m_keyFrameChannelList.keyScales.keyValues.push_back(key);
}
void MnBoneAnimationElement::AddKeyFrameQ(const MnBoneAnimationChannelKey<KeyRotation>& key)
{
	m_keyFrameChannelList.keyRotations.keyValues.push_back(key);
}
void MnBoneAnimationElement::AddKeyFrameT(const MnBoneAnimationChannelKey<KeyPosition>& key)
{
	m_keyFrameChannelList.keyPositions.keyValues.push_back(key);
}

void MnBoneAnimationElement::SetAffectingBoneName(const std::string& affectingBoneName)
{
	m_affectingBoneName = affectingBoneName;
}

void MnBoneAnimationElement::SetDuration(double duration)
{
	m_duration = duration;
}

double MnBoneAnimationElement::GetDuration() const
{
	return m_duration;
}

std::string MnBoneAnimationElement::GetAffectingBoneName() const
{
	return m_affectingBoneName;
}

MnBoneAnimationKeyFrame MnBoneAnimationElement::GetLerpedKeyFrameAtTime(float timeFactor)
{
	double currentTime = timeFactor * m_duration;
	
	auto lerpedKeyFrameS = m_keyFrameChannelList.keyScales.GetLerpedKeyAtTime(m_duration, timeFactor);
	auto lerpedKeyFrameQ = m_keyFrameChannelList.keyRotations.GetLerpedKeyAtTime(m_duration, timeFactor);
	auto lerpedKeyFrameT = m_keyFrameChannelList.keyPositions.GetLerpedKeyAtTime(m_duration, timeFactor);

	DirectX::SimpleMath::Vector3& scale = lerpedKeyFrameS.keyValue;
	DirectX::SimpleMath::Quaternion& rotation = lerpedKeyFrameQ.keyValue;
	DirectX::SimpleMath::Vector3& position = lerpedKeyFrameT.keyValue;

	MnBoneAnimationKeyFrame lerpedKeyFrame = { scale,rotation,position };

	return lerpedKeyFrame;
}
