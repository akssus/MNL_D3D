#include "MnBoneAnimationTracker.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBoneAnimationTracker::MnBoneAnimationTracker():m_duration(0.0),
m_currentTime(0.0),
m_isLoop(false),
m_isPlaying(false),
m_isPaused(false)
{
}


MnBoneAnimationTracker::~MnBoneAnimationTracker()
{
}

HRESULT MnBoneAnimationTracker::Init(const std::shared_ptr<MnSkeleton>& spSkeleton, const MnBoneAnimation& animation)
{
	m_spCurrentSkeleton = spSkeleton;
	m_currentAnimation = animation;
	m_currentKeyFrame = animation.GetKeyFrame(0);
	m_duration = animation.GetTotalDuration();
	return S_OK;
}

void MnBoneAnimationTracker::PlayAnimation()
{
	//fixed temporarilly
	m_currentTime += 10.0;
	float timeFactor = m_currentTime / m_currentAnimation.GetTotalDuration();

	UINT currentFrameIndex = m_currentAnimation.GetKeyFrameIndex(timeFactor);
	UINT nextFrameIndex = _GetNextFrameIndex(currentFrameIndex);

	auto currentKeyFrame = m_currentAnimation.GetKeyFrame(currentFrameIndex);
	auto nextKeyFrame = m_currentAnimation.GetKeyFrame(nextFrameIndex);

	float animFactor = 1.0f;
	bool isNotLastKeyFrame = currentFrameIndex != nextFrameIndex;
	if (isNotLastKeyFrame)
	{
		animFactor = (m_currentTime - currentKeyFrame.keyTime) / (nextKeyFrame.keyTime - currentKeyFrame.keyTime);
	}

	_UpdateBones(currentKeyFrame, nextKeyFrame, animFactor);
}

UINT MnBoneAnimationTracker::_GetNextFrameIndex(UINT currentFrameIndex)
{
	UINT nextFrameIndex = currentFrameIndex + 1;
	if (nextFrameIndex >= m_currentAnimation.GetNumKeyFrames())
	{
		nextFrameIndex = currentFrameIndex;
	}
	return nextFrameIndex;
}

void MnBoneAnimationTracker::_UpdateBones(const MnBoneAnimationKeyFrame& keyFrame_from, const MnBoneAnimationKeyFrame& keyFrame_to, float factor)
{
	int keysSize = m_currentKeyFrame.keys.size();
	for (int i = 0; i < keysSize; ++i)
	{ 
		auto& key_from = keyFrame_from.keys[i];
		auto& key_to = keyFrame_to.keys[i];
		auto key_lerp = _LerpKeys(key_from, key_to, factor);
		std::string affectingBoneName = key_from.affectingBoneName;
		m_spCurrentSkeleton->UpdateBone(affectingBoneName, key_lerp.keyPosition, key_lerp.keyRotation, key_lerp.keyScale);
	}
	m_spCurrentSkeleton->ReposeBones();
}

MnBoneAnimationKey MnBoneAnimationTracker::_LerpKeys(const MnBoneAnimationKey& key_from, const MnBoneAnimationKey& key_to, float factor)
{
	MnBoneAnimationKey retKey;
	
	retKey.affectingBoneName = key_from.affectingBoneName;
	retKey.keyPosition = Vector3::Lerp(key_from.keyPosition, key_to.keyPosition, factor);
	retKey.keyRotation = Quaternion::Lerp(key_from.keyRotation, key_to.keyRotation, factor);
	retKey.keyScale = Vector3::Lerp(key_from.keyScale, key_to.keyScale, factor);

	return retKey;
}