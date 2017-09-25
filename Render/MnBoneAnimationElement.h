#pragma once

#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <string>
#include <vector>

namespace MNL
{
	struct MnBoneAnimationKeyFrame
	{
		DirectX::SimpleMath::Vector3 keyPosition;
		DirectX::SimpleMath::Quaternion keyRotation;
		DirectX::SimpleMath::Vector3 keyScale;
		double keyTime;
	};

	/*
	A MnBoneAnimationElement includes all keyframes of a bone.
	*/
	class MnBoneAnimationElement
	{
	public:
		MnBoneAnimationElement();
		~MnBoneAnimationElement();

		void AddKeyFrame(const MnBoneAnimationKeyFrame& key);
		void SetAffectingBoneName(const std::string& affectingBoneName);
		void SetDuration(double duration);
		
		double GetDuration() const;
		UINT GetNumKeyFrames() const;
		std::string GetAffectingBoneName() const;

		/**
		Get automatically lerped key frame at the specific time.
		@param timeFactor must be 0.0 ~ 1.0. Calculated by (targetTick)/(totalTick)
		@return empty key frame if it has no key frames
		*/
		MnBoneAnimationKeyFrame MnBoneAnimationElement::GetLerpedKeyFrameAtTime(float timeFactor);

		/**
		Get key frame at the index
		*/
		MnBoneAnimationKeyFrame GetKeyFrame(UINT index) const;
		/**
		Get key frame at the specific time.
		@param timeFactor must be 0.0 ~ 1.0. Calculated by (targetTick)/(totalTick)
		@return empty key frame if it has no key frames
		*/
		MnBoneAnimationKeyFrame GetKeyFrameAtTime(float timeFactor) const;
		/**
		Get key frame's index at the specific time.
		@param timeFactor must be 0.0 ~ 1.0. Calculated by (targetTick)/(totalTick)
		@return empty key frame if it has no key frames
		*/
		UINT GetKeyFrameIndexAtTime(float timeFactor) const;

	private:
		UINT _GetNextKeyFrameIndexOf(UINT currentIndex) const;
		MnBoneAnimationKeyFrame _LerpKeyFrame(const MnBoneAnimationKeyFrame& keyFrame_from, const MnBoneAnimationKeyFrame& keyFrame_to, float factor);

	private:
		std::string m_affectingBoneName;
		double m_duration;
		std::vector<MnBoneAnimationKeyFrame> m_lstKeyFrames;
	};
}