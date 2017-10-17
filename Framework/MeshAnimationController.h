/**
@section ����
�ִϸ��̼� ��Ʈ�ѷ��� ���̷��� ��ü�� ������ �ʴ´�. \n
�ִϸ��̼� ��Ʈ�ѷ��� �ִϸ��̼� ����(Ű������ �� �� Bone�� ���� Ʈ������) ���� ����Ʈ�� ������,
Mesh ������Ʈ�� ���̷��濡 ���� ������Ʈ�� �����Ѵ�. �̿� Mesh ������Ʈ�� ���̷����� �� Bone�� ���� Ʈ������ ���� ����Ǹ�, �޽��� ���ؽ��� ������� �ʴ´�.
*/


#pragma once

#include "MnGameObjectComponent.h"
#include <map>
#include <memory>
#include "Render/MnBoneAnimation.h"
#include "Render/MnBoneAnimationTracker.h"


namespace MNL
{
	class MeshAnimationController : public MnGameObjectComponent
	{
	public:
		MeshAnimationController();
		~MeshAnimationController();

		/**
		@brief �ִϸ��̼��� �ش� �̸��� Key�μ� �߰��Ѵ�. �̹� Key�� �����ϴ� ��� ������.
		*/
		void AddAnimation(const std::string& animName, const std::shared_ptr<MnBoneAnimation>& spAnimation);

		/**
		@brief ���� �ִϸ��̼��� �ش� �ִϸ��̼����� �����Ѵ�. Key�� �������� ���� ��� �������� �ʴ´�.
		*/
		void SetAnimation(const std::string& animName);

		/**
		@brief �ش� �ִϸ��̼��� �����Ѵ�.
		*/
		void RemoveAnimation(const std::string& animName);

		std::shared_ptr<MnBoneAnimation>& GetAnimation(const std::string&);

		/**
		@brief ���� ������Ʈ�� �޽ø� Ȯ���Ͽ� ���� ������Ʈ�Ѵ�.
		*/
		void UpdateBones();

		/**
		@brief �ִϸ��̼� ��� �Ϸ� �� ���� ���θ� �����Ѵ�.
		*/
		void SetLoop(bool isLoop);

		
	private:
		void _Init();

	private:
		std::map<std::string, std::shared_ptr<MnBoneAnimation>> m_tblAnimations;
		MnBoneAnimationTracker m_tracker;
	};
}