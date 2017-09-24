#include "MnBoneAnimationTracker.h"

using namespace MNL;

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
	m_duration = animation.GetDuration();
	return S_OK;
}

void MnBoneAnimationTracker::PlayAnimation()
{
	//fixed temporarilly
	m_currentTime += 1.0;

	_UpdateBones();
}

void MnBoneAnimationTracker::_UpdateBones(const MnBoneAnimationKeyFrame& keyFrame_from, const MnBoneAnimationKeyFrame& keyFrame_to, float factor)
{
	int keysSize = m_currentKeyFrame.keys.size();
	for (int i = 0; i < keysSize; ++i)
	{ 
		auto& key_from = keyFrame_from.keys[i];
		auto& key_to = keyFrame_to.keys[i];
		auto& key_lerp = _LerpKeys(key_from, key_to, factor);
		std::string affectingBoneName = key_from.affectingBoneName;
		m_spCurrentSkeleton->UpdateBone(affectingBoneName, key_lerp.keyPosition, key_lerp.keyRotation, key_lerp.keyScale);
	}
	m_spCurrentSkeleton->ReposeBones();
}

MnBoneAnimationKey MnBoneAnimationTracker::_LerpKeys(const MnBoneAnimationKey& key_from, const MnBoneAnimationKey& key_to, float factor)
{
	MnBoneAnimationKey retKey;
	
	retKey.affectingBoneName = key_from.affectingBoneName;
	retKey.keyPosition = key_from.keyPosition * factor + key_to.keyPosition * (1.0f - factor);
	retKey.keyRotation = key_from.keyRotation * factor + key_to.keyRotation * (1.0f - factor);
	retKey.keyScale = key_from.keyScale * factor + key_to.keyScale * (1.0f - factor);

	return retKey;
}