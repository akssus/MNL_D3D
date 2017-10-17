#include "MeshAnimationController.h"
#include "Mesh.h"
#include "MnGameObject.h"
#include "MnGameWorld.h"
#include "MnFramework.h"


using namespace MNL;

MeshAnimationController::MeshAnimationController()
{
}


MeshAnimationController::~MeshAnimationController()
{
}

void MeshAnimationController::_Init()
{
	
}

void MeshAnimationController::AddAnimation(const std::string& animName, const std::shared_ptr<MnBoneAnimation>& spAnimation)
{
	m_tblAnimations[animName] = spAnimation;
}

void MeshAnimationController::SetAnimation(const std::string& animName)
{
	if (m_tblAnimations.count(animName) > 0)
	{
		m_tracker.SetAnimation(m_tblAnimations[animName]);
	}
}

void MeshAnimationController::RemoveAnimation(const std::string& animName)
{
	m_tblAnimations.erase(animName);
}

std::shared_ptr<MnBoneAnimation>& MeshAnimationController::GetAnimation(const std::string& animName)
{
	if (m_tblAnimations.count(animName) == 0)
	{
		return std::shared_ptr<MnBoneAnimation>(nullptr);
	}
	return m_tblAnimations[animName];
}


void MeshAnimationController::UpdateBones()
{
	if (IsAttatched() == false)
	{
		return;
	}

	auto compMesh = GetComponent<Mesh>();
	if (compMesh == nullptr)
	{
		//�޽� ������Ʈ�� �������� �ʴ� ��� ��������
		return;
	}
	auto spSkeleton = compMesh->GetSkeleton();
	if (spSkeleton == nullptr)
	{
		//�޽ÿ� ���̷����� �������� �ʴ� ��� ��������
		return;
	}
	auto world = GameObject()->GameWorld();
	if (world == nullptr)
	{
		//�Ҽӵ� ���� ���尡 ���� ��� ���� ����
		return;
	}

	m_tracker.SetSkeleton(spSkeleton);
	m_tracker.UpdateAnimation(MnFramework::GetElapsedTime().ScaledTime());
}

void MeshAnimationController::SetLoop(bool isLoop)
{
	m_tracker.SetLoop(isLoop);
}