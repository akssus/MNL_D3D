#pragma once
#include <vector>
#include "Framework\MnFramework.h"
#include "Core\MNL_Core.h"
#include "Render\MNL_Render.h"
#include "Utility\MNL_Utility.h"


class TestGame : public MNL::MnFramework
{
public:
	TestGame();
	~TestGame();

	HRESULT OnInit();
	bool OnUpdate();

private:
	std::shared_ptr<MNL::MnSkinnedMeshRenderer> m_spSkinnedMeshRenderer;
	MNL::MnCamera m_camera;
	MNL::MnBoneAnimationTracker m_boneAnimTracker;
	MNL::MnResourcePool m_resourcePool;
	MNL::MnTimer m_timer;

	//�Ʒ� ����Ʈ���� ���� �Ŵ�¡ �ϴ� Ŭ���� ������ �ɵ�
	std::vector<std::shared_ptr<MNL::MnMesh>> m_lstMeshes;
	std::vector<std::shared_ptr<MNL::MnMeshTextureCombination>> m_lstTextures;
	std::vector<std::shared_ptr<MNL::MnMaterial>> m_lstMaterials;
	std::vector<std::shared_ptr<MNL::MnLightSource>> m_lstLights;
};

