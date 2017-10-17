#pragma once
#include <vector>
#include "Framework\MnFramework.h"
#include "Core\MNL_Core.h"
#include "Render\MNL_Render.h"
#include "Utility\MNL_Utility.h"
#include "Framework\MnGameWorld.h"
#include "Framework\MnGameObject.h"


class TestGame : public MNL::MnFramework
{
public:
	TestGame();
	~TestGame();

	HRESULT OnInit();
	bool OnUpdate();

private:
	MNL::MnGameWorld m_gameWorld;
	MNL::MnResourcePool m_resourcePool;
};

