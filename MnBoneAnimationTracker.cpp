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

	int keysSize = m_currentKeyFrame.keys.size();
	for (int i = 0; i < keysSize; ++i)
	{
		auto& key = m_currentKeyFrame.keys[i];
		m_spCurrentSkeleton->UpdateBone(key.affectingBoneName, key.keyPosition, key.keyRotation, key.keyScale);
	}

}