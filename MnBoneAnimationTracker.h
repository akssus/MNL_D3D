#pragma once
#include "MnSkeleton.h"
#include "MnBoneAnimation.h"

namespace MNL
{
	class MnBoneAnimationTracker
	{
	public:
		MnBoneAnimationTracker();
		~MnBoneAnimationTracker();
		HRESULT Init(const std::shared_ptr<MnSkeleton>& spSkeleton, const MnBoneAnimation& animation);

		void PlayAnimation();

	private:
		std::shared_ptr<MnSkeleton> m_spCurrentSkeleton;
		MnBoneAnimation m_currentAnimation;
		MnBoneAnimationKeyFrame m_currentKeyFrame;
		double m_currentTime;
		double m_duration;

		bool m_isLoop;
		bool m_isPlaying;
		bool m_isPaused;
	};
}