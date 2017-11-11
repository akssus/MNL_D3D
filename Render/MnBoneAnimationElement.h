/**
@class MnBoneAnimationElement
@brief ��ü �ִϸ��̼� �� "�� �ϳ�"�� ������ Ű�������� ������ ��ü.
@author Akssus
@section ����
�Ѱ��� �ִϸ��̼� �� Ű�����ӵ� �� ���� "�� �ϳ�"�� ��� Ű�������� ������ ��ü. \n
�̷������μ� Skeleton�� �� Bone���� �������� ���������� ���� �� �ִ�. \n
MnBone�� ���������� �������� ������, AffectingBoneName �̶� ��������� ���� ���������� �����Ѵ�. \n
���뿡 �ش� AffectingBoneName �� �����Ѵٸ� Ű�����ӿ� ���� MnBone �� ��ȯ�� ������ �� �ְ�, \n
�������� �ʴٸ� �ƹ��͵� ó������ �������μ� �������� �ʴ� MnBone�� �����ϴ� ���ܸ� ������ �� �ִ�. \n
\n
MnBoneAnimationElement ��ü�� MnBoneAnimationKeyFrame ��ü�� ����Ʈ�� ������, 
Ư�� �ð��� �ش��ϴ� ������ Ű�������� ��ȯ�� �� �ִ�. \n
�̶� timeFactor ��� �μ��� ����ϴµ�, timeFactor �� ��ü �ִϸ��̼� Duration�� ������� �ǹ��ϸ� 0.0 ���� 1.0�� ������ ���� ������.
*/

#pragma once

#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <string>
#include <vector>
#include <algorithm>

namespace MNL
{
	//������ ä��

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
		@brief MnBoneAnimationElement �� ������ ��ġ�� ���� �̸��� ��ȯ�Ѵ�. MnSkeleton ������ ����� �� �ִ�.
		*/
		std::string GetAffectingBoneName() const;

		/**
		@brief Ư�� �ð��� ������ Ű�������� ��ȯ�Ѵ�. �Ϲ������� �� �Լ��� ����Ѵ�.
		@param timeFactor timeFactor �� �ݵ�� 0.0 ~ 1.0 ���̿��� �ϸ�, (���� ƽ) / (��ü ƽ) ���� ����� �� �ִ�.
		@return ������ Ű�������� ��ȯ�ϸ� ������ �۵��� �� Ű�������� ��ȯ�Ѵ�.
		*/
		MnBoneAnimationKeyFrame MnBoneAnimationElement::GetLerpedKeyFrameAtTime(float timeFactor);

	private:
		std::string m_affectingBoneName; ///< Ű�������� ������ ��ġ�� MnBone �� �̸�.
		double m_duration; ///< �� �ִϸ��̼��� ��ü Duration
		MnBoneAnimationKeyFrameChannelList m_keyFrameChannelList;
	};
}