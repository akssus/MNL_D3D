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

namespace MNL
{
	struct MnBoneAnimationKeyFrame
	{
		DirectX::SimpleMath::Vector3 keyPosition;
		DirectX::SimpleMath::Quaternion keyRotation;
		DirectX::SimpleMath::Vector3 keyScale;
		double keyTime; ///< �ش� Ű�������� �ð�.
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
		@brief MnBoneAnimationElement �� ������ ��ġ�� ���� �̸��� ��ȯ�Ѵ�. MnSkeleton ������ ����� �� �ִ�.
		*/
		std::string GetAffectingBoneName() const;

		/**
		@brief Ư�� �ð��� ������ Ű�������� ��ȯ�Ѵ�. �Ϲ������� �� �Լ��� ����Ѵ�.
		@param timeFactor timeFactor �� �ݵ�� 0.0 ~ 1.0 ���̿��� �ϸ�, (���� ƽ) / (��ü ƽ) ���� ����� �� �ִ�.
		@return ������ Ű�������� ��ȯ�ϸ� ������ �۵��� �� Ű�������� ��ȯ�Ѵ�.
		*/
		MnBoneAnimationKeyFrame MnBoneAnimationElement::GetLerpedKeyFrameAtTime(float timeFactor);

		/**
		@brief �ش� �ε����� Ű�������� ��ȯ�Ѵ�. Ư�� ���� �̿ܿ��� ������ �ʴ´�.
		*/
		MnBoneAnimationKeyFrame GetKeyFrame(UINT index) const;
		/**
		@brief Ư�� �ð��� �ش��ϴ� �������� ���� Ű�������� ��ȯ�Ѵ�. ���� Ű������1 �� Ű������2 ������ �ð����� Ű������1�� ��ȯ�ȴ�.
		@param timeFactor timeFactor �� �ݵ�� 0.0 ~ 1.0 ���̿��� �ϸ�, (���� ƽ) / (��ü ƽ) ���� ����� �� �ִ�.
		@return �������� ���� Ű�������� ��ȯ�ϸ� ������ �۵��� �� Ű�������� ��ȯ�Ѵ�.
		*/
		MnBoneAnimationKeyFrame GetKeyFrameAtTime(float timeFactor) const;
		/**
		@brief Ư�� �ð��� �ش��ϴ� �������� ���� Ű�������� �ε����� ��ȯ�Ѵ�. ���� Ű������1 �� Ű������2 ������ �ð����� �ε��� 1�� ��ȯ�ȴ�.
		@param timeFactor timeFactor �� �ݵ�� 0.0 ~ 1.0 ���̿��� �ϸ�, (���� ƽ) / (��ü ƽ) ���� ����� �� �ִ�.
		@return �������� ���� Ű�������� �ε����� ��ȯ�Ѵ�.
		*/
		UINT GetKeyFrameIndexAtTime(float timeFactor) const;

	private:
		/**
		@brief ���� �ε����� ���� �ε����� ��ȯ�ϸ� ���� �ε����� ������ Ű�������� ��� ���� �ε����� �״�� ��ȯ�Ѵ�.
		*/
		UINT _GetNextKeyFrameIndexOf(UINT currentIndex) const;

		/**
		@brief �� Ű������ ������ ������ �ǽ��Ѵ�.
		@param factor 0.0 ~ 1.0 ������ ���� ������.
		@return (keyFrame_from * factor) + (keyFrame_to * (1.0-factor)) ���� ������ ������ Ű�������� ��ȯ�Ѵ�.
		*/
		MnBoneAnimationKeyFrame _LerpKeyFrame(const MnBoneAnimationKeyFrame& keyFrame_from, const MnBoneAnimationKeyFrame& keyFrame_to, float factor);

	private:
		std::string m_affectingBoneName; ///< Ű�������� ������ ��ġ�� MnBone �� �̸�.
		double m_duration; ///< �� �ִϸ��̼��� ��ü Duration
		std::vector<MnBoneAnimationKeyFrame> m_lstKeyFrames;
	};
}