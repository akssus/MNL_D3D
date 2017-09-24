#pragma once
#include <d3d11.h>
#include <string>
#include <vector>
#include "MnBoneAnimationKeyFrame.h"

namespace MNL
{
	class MnBoneAnimation
	{
	public:
		MnBoneAnimation();
		~MnBoneAnimation();

		void SetName(const std::string& name);
		const std::string& GetName() const;

		void SetTotalDuration(double duration);
		const double& GetTotalDuration() const;

		void AddKeyFrame(const MnBoneAnimationKeyFrame& keyFrame);
		UINT GetNumKeyFrames() const;
		MnBoneAnimationKeyFrame GetKeyFrame(UINT index) const;
		/**
		Get key frame at the specific time.
		@param timeFactor must be 0.0 ~ 1.0. Calculated by (targetTick)/(totalTick)
		*/
		MnBoneAnimationKeyFrame GetKeyFrameAtTime(float timeFactor) const;
		/*
		Get key frame's index at the specific time.
		@param timeFactor must be 0.0 ~ 1.0. Calculated by (targetTick)/(totalTick)
		*/
		UINT GetKeyFrameIndex(float timeFactor) const;

	private:
		std::string m_name;
		double m_totalDuration;
		std::vector<MnBoneAnimationKeyFrame> m_lstKeyFrames;

	};
}