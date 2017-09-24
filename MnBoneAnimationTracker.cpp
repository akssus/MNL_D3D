#include "MnBoneAnimationTracker.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBoneAnimationTracker::MnBoneAnimationTracker():m_currentTime(0.0),
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
	return S_OK;
}

void MnBoneAnimationTracker::PlayAnimation()
{
	//fixed temporarilly
	m_currentTime += 0.5;
	if (m_currentTime > m_currentAnimation.GetTotalDuration())
	{
		m_currentTime -= m_currentAnimation.GetTotalDuration();
	}
	float timeFactor = m_currentTime / m_currentAnimation.GetTotalDuration();
	
	_UpdateBones(timeFactor);
}

void MnBoneAnimationTracker::_UpdateBones(float timeFactor)
{
	int numElements = m_currentAnimation.GetNumElements();
	for (int i = 0; i < numElements; ++i)
	{
		auto element = m_currentAnimation.GetElement(i);
		auto keyFrame = element.GetLerpedKeyFrameAtTime(timeFactor);
		m_spCurrentSkeleton->UpdateBone(element.GetAffectingBoneName(), keyFrame.keyPosition, keyFrame.keyRotation, keyFrame.keyScale);
	}
	m_spCurrentSkeleton->ReposeBones();
}