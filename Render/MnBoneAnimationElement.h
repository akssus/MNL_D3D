/**
@class MnBoneAnimationElement
@brief 전체 애니메이션 중 "본 하나"의 전구간 키프레임을 가지는 객체.
@author Akssus
@section 개요
한개의 애니메이션 내 키프레임들 중 오직 "본 하나"의 모든 키프레임을 가지는 객체. \n
이러함으로서 Skeleton의 각 Bone들의 움직임을 독립적으로 명세할 수 있다. \n
MnBone을 직접적으로 참조하지 않으며, AffectingBoneName 이란 멤버변수를 가져 간접적으로 참조한다. \n
뼈대에 해당 AffectingBoneName 이 존재한다면 키프레임에 따라 MnBone 의 변환을 갱신할 수 있고, \n
존재하지 않다면 아무것도 처리하지 않음으로서 존재하지 않는 MnBone을 참조하는 예외를 방지할 수 있다. \n
\n
MnBoneAnimationElement 객체는 MnBoneAnimationKeyFrame 객체의 리스트를 가지며, 
특정 시간에 해당하는 보간된 키프레임을 반환할 수 있다. \n
이때 timeFactor 라는 인수를 사용하는데, timeFactor 는 전체 애니메이션 Duration의 백분율을 의미하며 0.0 에서 1.0의 사이의 값을 가진다.
*/

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
		double keyTime; ///< 해당 키프레임의 시각.
	};

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

		/**
		@brief MnBoneAnimationElement 가 영향을 끼치는 본의 이름을 반환한다. MnSkeleton 내에서 사용할 수 있다.
		*/
		std::string GetAffectingBoneName() const;

		/**
		@brief 특정 시각의 보간된 키프레임을 반환한다. 일반적으로 이 함수를 사용한다.
		@param timeFactor timeFactor 는 반드시 0.0 ~ 1.0 사이여야 하며, (현재 틱) / (전체 틱) 으로 계산할 수 있다.
		@return 보간된 키프레임을 반환하며 비정상 작동시 빈 키프레임을 반환한다.
		*/
		MnBoneAnimationKeyFrame MnBoneAnimationElement::GetLerpedKeyFrameAtTime(float timeFactor);

		/**
		@brief 해당 인덱스의 키프레임을 반환한다. 특정 목적 이외에는 사용되지 않는다.
		*/
		MnBoneAnimationKeyFrame GetKeyFrame(UINT index) const;
		/**
		@brief 특정 시각에 해당하는 보간되지 않은 키프레임을 반환한다. 만약 키프레임1 과 키프레임2 사이의 시간대라면 키프레임1이 반환된다.
		@param timeFactor timeFactor 는 반드시 0.0 ~ 1.0 사이여야 하며, (현재 틱) / (전체 틱) 으로 계산할 수 있다.
		@return 보간되지 않은 키프레임을 반환하며 비정상 작동시 빈 키프레임을 반환한다.
		*/
		MnBoneAnimationKeyFrame GetKeyFrameAtTime(float timeFactor) const;
		/**
		@brief 특정 시각에 해당하는 보간되지 않은 키프레임의 인덱스를 반환한다. 만약 키프레임1 과 키프레임2 사이의 시간대라면 인덱스 1이 반환된다.
		@param timeFactor timeFactor 는 반드시 0.0 ~ 1.0 사이여야 하며, (현재 틱) / (전체 틱) 으로 계산할 수 있다.
		@return 보간되지 않은 키프레임의 인덱스를 반환한다.
		*/
		UINT GetKeyFrameIndexAtTime(float timeFactor) const;

	private:
		/**
		@brief 현재 인덱스의 다음 인덱스를 반환하며 현재 인덱스가 마지막 키프레임일 경우 현재 인덱스를 그대로 반환한다.
		*/
		UINT _GetNextKeyFrameIndexOf(UINT currentIndex) const;

		/**
		@brief 두 키프레임 사이의 보간을 실시한다.
		@param factor 0.0 ~ 1.0 사이의 값을 가진다.
		@return (keyFrame_from * factor) + (keyFrame_to * (1.0-factor)) 선형 보간을 적용한 키프레임을 반환한다.
		*/
		MnBoneAnimationKeyFrame _LerpKeyFrame(const MnBoneAnimationKeyFrame& keyFrame_from, const MnBoneAnimationKeyFrame& keyFrame_to, float factor);

	private:
		std::string m_affectingBoneName; ///< 키프레임이 영향을 끼치는 MnBone 의 이름.
		double m_duration; ///< 본 애니메이션의 전체 Duration
		std::vector<MnBoneAnimationKeyFrame> m_lstKeyFrames;
	};
}