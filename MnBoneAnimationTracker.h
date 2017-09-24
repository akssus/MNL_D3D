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
		void _UpdateBones(float timeFactor);

	private:
		std::shared_ptr<MnSkeleton> m_spCurrentSkeleton;
		MnBoneAnimation m_currentAnimation;
		double m_currentTime;

		bool m_isLoop;
		bool m_isPlaying;
		bool m_isPaused;
	};
}