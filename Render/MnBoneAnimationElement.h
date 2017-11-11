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
#include <algorithm>

namespace MNL
{
	//스케일 채널

	typedef DirectX::SimpleMath::Vector3 KeyScale;
	typedef DirectX::SimpleMath::Quaternion KeyRotation;
	typedef DirectX::SimpleMath::Vector3 KeyPosition;

	template <typename T>
	class MnBoneAnimationChannelKey
	{
	public:
		T keyValue;
		double keyTime;
	};

	template <typename T>
	class MnBoneAnimationChannel
	{
	public:
		std::vector<MnBoneAnimationChannelKey<T>> keyValues;
		
		MnBoneAnimationChannelKey<T> GetLerpedKeyAtTime(float animDuration, float timeFactor)
		{
			float scaledTime = timeFactor * animDuration;
			MnBoneAnimationChannelKey<T> queryKey{ Vector3(0.0f,0.0f,0.0f), scaledTime };

			if (keyValues.size() == 0) return queryKey;

			MnBoneAnimationChannelKey<T>& prevKey = _GetPrevKeyFrame(queryKey, scaledTime);
			MnBoneAnimationChannelKey<T>& nextKey = _GetNextKeyFrame(queryKey, scaledTime);
			float blendFactor = (scaledTime - prevKey.keyTime) / (nextKey.keyTime - prevKey.keyTime);

			T lerpedValue =  T::Lerp(prevKey.keyValue, nextKey.keyValue, blendFactor);

			MnBoneAnimationChannelKey<T> retKey;
			retKey.keyTime = scaledTime;
			retKey.keyValue = lerpedValue;

			return retKey;
		}
	private:
		MnBoneAnimationChannelKey<T>& _GetPrevKeyFrame(const MnBoneAnimationChannelKey<T>& queryKey, float scaledTime)
		{
			auto it = std::upper_bound(keyValues.begin(), keyValues.end(), queryKey, [](const MnBoneAnimationChannelKey<T>& key1, const MnBoneAnimationChannelKey<T>& key2)
			{
				return (key1.keyTime < key2.keyTime);
			});
			if (it == keyValues.begin())
			{
				return *it;
			}
			if (it == keyValues.end())
			{
				return keyValues.back();
			}
			return *(it-1);
		}
		MnBoneAnimationChannelKey<T>& _GetNextKeyFrame(const MnBoneAnimationChannelKey<T>& queryKey, float scaledTime)
		{
			auto it = std::upper_bound(keyValues.begin(), keyValues.end(), queryKey, [](const MnBoneAnimationChannelKey<T>& key1, const MnBoneAnimationChannelKey<T>& key2)
			{
				return (key1.keyTime < key2.keyTime);
			});
			if (it == keyValues.end())
			{
				return keyValues.back();
			}
			return *it;
		}
	};

	struct MnBoneAnimationKeyFrameChannelList
	{
		MnBoneAnimationChannel<KeyScale> keyScales;
		MnBoneAnimationChannel<KeyRotation> keyRotations;
		MnBoneAnimationChannel<KeyPosition> keyPositions;
	};

	struct MnBoneAnimationKeyFrame
	{
		DirectX::SimpleMath::Vector3 keyScale;
		DirectX::SimpleMath::Quaternion keyRotation;
		DirectX::SimpleMath::Vector3 keyPosition;
	};

	class MnBoneAnimationElement
	{
	public:
		MnBoneAnimationElement();
		~MnBoneAnimationElement();

		void AddKeyFrameS(const MnBoneAnimationChannelKey<KeyScale>& key);
		void AddKeyFrameQ(const MnBoneAnimationChannelKey<KeyRotation>& key);
		void AddKeyFrameT(const MnBoneAnimationChannelKey<KeyPosition>& key);


		void SetAffectingBoneName(const std::string& affectingBoneName);
		void SetDuration(double duration);
		
		double GetDuration() const;

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

	private:
		std::string m_affectingBoneName; ///< 키프레임이 영향을 끼치는 MnBone 의 이름.
		double m_duration; ///< 본 애니메이션의 전체 Duration
		MnBoneAnimationKeyFrameChannelList m_keyFrameChannelList;
	};
}