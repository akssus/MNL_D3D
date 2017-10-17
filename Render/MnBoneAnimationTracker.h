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

		void SetSkeleton(const std::shared_ptr<MnSkeleton>& spSkeleton);
		void SetAnimation(const std::shared_ptr<MnBoneAnimation>& spAnimation);

		/*
		Set how many frames per seconds
		*/
		void SetFPS(double fps);
		/*
		Set how fast the animations moves.
		@param speed 1.0f as normal speed
		*/
		void SetAnimatingSpeed(float speed);

		/**
		@brief 현재 애니메이션 프레임을 0으로 되돌린다.
		*/
		void Reset();

		/**
		@brief 애니메이션 재생 종료시 루프 여부를 설정한다.
		*/
		void SetLoop(bool isLoop);

		void UpdateAnimation(double timeDelta);

	private:
		void _UpdateBones(float timeFactor);

	private:
		std::shared_ptr<MnSkeleton> m_spCurrentSkeleton;
		std::shared_ptr<MnBoneAnimation> m_spCurrentAnimation;

		double m_currentTime; ///< 현재 애니메이팅 타이밍.
		double m_durationPerSeconds; ///< 초당 듀레이션. 듀레이션은 fbx파일 기준
		float m_animatingSpeed; ///< 원래 애니메이팅 스피드의 백분율. 1.0일 경우 정상속도. 기본값 1.0

		bool m_isLoop;
		bool m_isPlaying;
		bool m_isPaused;
	};
}