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

		/*
		Set how many frames per seconds
		*/
		void SetFPS(double fps);
		/*
		Set how fast the animations moves.
		@param speed 1.0f as normal speed
		*/
		void SetAnimatingSpeed(float speed);

		void UpdateAnimation(double timeDelta);

	private:
		void _UpdateBones(float timeFactor);

	private:
		std::shared_ptr<MnSkeleton> m_spCurrentSkeleton;
		MnBoneAnimation m_currentAnimation;
		double m_currentTime;
		/*
		In a single second, how long the duration is.
		*/
		double m_durationPerSeconds;
		/*
		Animation timing speed. 1.0f is normal
		*/
		float m_animatingSpeed;

		bool m_isLoop;
		bool m_isPlaying;
		bool m_isPaused;
	};
}