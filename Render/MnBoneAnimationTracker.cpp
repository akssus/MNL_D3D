#include "MnBoneAnimationTracker.h"
#include <cassert>

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBoneAnimationTracker::MnBoneAnimationTracker():
	m_currentTime(0.0),
	m_animatingSpeed(1.0f),
	m_durationPerSeconds(24.0),
	m_isLoop(false),
	m_isPlaying(false),
	m_isPaused(false)
{
}


MnBoneAnimationTracker::~MnBoneAnimationTracker()
{
}

void MnBoneAnimationTracker::SetSkeleton(const std::shared_ptr<MnSkeleton>& spSkeleton)
{
	assert(spSkeleton != nullptr);
	m_spCurrentSkeleton = spSkeleton;
}
void MnBoneAnimationTracker::SetAnimation(const std::shared_ptr<MnBoneAnimation>& spAnimation)
{
	assert(spAnimation != nullptr);
	m_spCurrentAnimation = spAnimation;
}
void MnBoneAnimationTracker::SetFPS(double fps)
{
	m_durationPerSeconds = fps;
}
void MnBoneAnimationTracker::SetAnimatingSpeed(float speed)
{
	if (speed <= 0)
		speed = 1.0f;
	m_animatingSpeed = speed;
}

void MnBoneAnimationTracker::Reset()
{
	m_currentTime = 0.0f;
}

void MnBoneAnimationTracker::SetLoop(bool isLoop)
{
	m_isLoop = isLoop;
}

void MnBoneAnimationTracker::UpdateAnimation(double timeDelta)
{
	if (m_spCurrentAnimation == nullptr || m_spCurrentSkeleton == nullptr)
	{
		//설정된 애니메이션이나 스켈레톤이 없으면 업데이트 중지
		return;
	}

	//fixed temporarilly
	m_currentTime += timeDelta * 0.001 * m_durationPerSeconds;
	if (m_currentTime > m_spCurrentAnimation->GetTotalDuration())
	{
		//루프가 설정됬을 경우 프레임을 되돌린다.
		if (m_isLoop) m_currentTime -= m_spCurrentAnimation->GetTotalDuration();
		else m_currentTime = m_spCurrentAnimation->GetTotalDuration();
	}
	float timeFactor = m_currentTime / m_spCurrentAnimation->GetTotalDuration();
	_UpdateBones(timeFactor * m_animatingSpeed);
}

void MnBoneAnimationTracker::_UpdateBones(float timeFactor)
{
	int numElements = m_spCurrentAnimation->GetNumElements();
	for (int i = 0; i < numElements; ++i)
	{
		auto element = m_spCurrentAnimation->GetElement(i);
		auto keyFrame = element.GetLerpedKeyFrameAtTime(timeFactor);
		m_spCurrentSkeleton->UpdateBone(element.GetAffectingBoneName(), keyFrame.keyPosition, keyFrame.keyRotation, keyFrame.keyScale);
	}
	m_spCurrentSkeleton->ReposeBones();
}