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

		void SetDuration(double duration);
		const double& GetDuration() const;

		void AddKeyFrame(const MnBoneAnimationKeyFrame& keyFrame);
		UINT GetNumKeyFrames() const;
		MnBoneAnimationKeyFrame GetKeyFrame(UINT index) const;

	private:
		std::string m_name;
		double m_duration;
		std::vector<MnBoneAnimationKeyFrame> m_lstKeyFrames;

	};
}