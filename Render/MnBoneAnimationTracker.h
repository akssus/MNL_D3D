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
		@brief ���� �ִϸ��̼� �������� 0���� �ǵ�����.
		*/
		void Reset();

		/**
		@brief �ִϸ��̼� ��� ����� ���� ���θ� �����Ѵ�.
		*/
		void SetLoop(bool isLoop);

		void UpdateAnimation(double timeDelta);

	private:
		void _UpdateBones(float timeFactor);

	private:
		std::shared_ptr<MnSkeleton> m_spCurrentSkeleton;
		std::shared_ptr<MnBoneAnimation> m_spCurrentAnimation;

		double m_currentTime; ///< ���� �ִϸ����� Ÿ�̹�.
		double m_durationPerSeconds; ///< �ʴ� �෹�̼�. �෹�̼��� fbx���� ����
		float m_animatingSpeed; ///< ���� �ִϸ����� ���ǵ��� �����. 1.0�� ��� ����ӵ�. �⺻�� 1.0

		bool m_isLoop;
		bool m_isPlaying;
		bool m_isPaused;
	};
}