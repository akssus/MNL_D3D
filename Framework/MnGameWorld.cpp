#include "MnGameWorld.h"
#include <memory>
#include <cassert>
#include "Renderer.h"
#include "CameraList.h"
#include "ShaderList.h"
#include "LightList.h"
#include "MeshAnimationController.h"

using namespace DirectX::SimpleMath;
using namespace MNL;

MnGameWorld::MnGameWorld() :
	m_screenWidth(0.0f),
	m_screenHeight(0.0f)
{
	_Init();
	OnInit();
}


MnGameWorld::~MnGameWorld()
{
}

void MnGameWorld::_Init()
{
	m_idAllocator.SetRange(0, 1000);
}

void MnGameWorld::Update()
{
	OnUpdate();
}

void MnGameWorld::OnInit()
{

}

void MnGameWorld::OnUpdate()
{
	//테스트용 임시
	//@todo 수정바람. 전부.
	for (auto& gameObject : m_lstGameObjects)
	{
		auto& shaders = GetComponent<ShaderList>()->GetShaders();
		for (auto& shader : shaders)
		{
			shader.second->AddObjectsToQueue(gameObject.second);
		}
		auto animController = gameObject.second->GetComponent<MeshAnimationController>();
		if (animController != nullptr)
		{
			animController->UpdateBones();
		}
	}
}

void MnGameWorld::AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent)
{
	assert(spComponent != nullptr);
	std::string key = spComponent->GetComponentName();
	spComponent->_SetAttatchedWorld(this);
	m_tblComponents[key] = spComponent;
}

int MnGameWorld::AllocateGameObjectID()
{
	return m_idAllocator.Allocate();
}

std::map<int, std::shared_ptr<MnGameObject>>& MnGameWorld::GetGameObjects() 
{
	return m_lstGameObjects;
}

void MnGameWorld::AddGameObject(const std::shared_ptr<MnGameObject>& spGameObject)
{
	AddGameObject(spGameObject, AllocateGameObjectID());
}
void MnGameWorld::AddGameObject(const std::shared_ptr<MnGameObject>& spGameObject, int id)
{
	m_lstGameObjects[id] = spGameObject;
	m_idAllocator.Register(id);
}


void MnGameWorld::RemoveGameObject(int id)
{
	m_lstGameObjects.erase(id);
	m_idAllocator.Deallocate(id);
}

std::shared_ptr<MnGameObject> MnGameWorld::GetGameObject(int id) 
{
	if (m_lstGameObjects.count(id) == 0)
	{
		return nullptr;
	}
	return m_lstGameObjects[id];
}


std::vector<std::shared_ptr<MnGameObject>> MnGameWorld::GetGameObjectsByTag(const std::string& tag) const
{
	std::vector<std::shared_ptr<MnGameObject>> retLst;
	for (auto& objPair : m_lstGameObjects)
	{
		auto spObject = objPair.second;
		auto objTag = spObject->GetTag();
		if (objTag == tag)
		{
			retLst.push_back(spObject);
		}
	}
	return retLst;
}

void MnGameWorld::SetMainCamera(const std::shared_ptr<MnCamera>& spCamera)
{
	assert(spCamera != nullptr);
	m_spMainCamera = spCamera;
}

const std::shared_ptr<MnCamera>& MnGameWorld::GetMainCamera() const
{
	return m_spMainCamera;
}


void MnGameWorld::SetScreenSize(float width, float height)
{
	m_screenWidth = width;
	m_screenHeight = height;
}
void MnGameWorld::SetScreenSize(const DirectX::SimpleMath::Vector2& size)
{
	m_screenWidth = size.x;
	m_screenHeight = size.y;
}
DirectX::SimpleMath::Vector2 MnGameWorld::GetScreenSize() const
{
	return Vector2(m_screenWidth, m_screenHeight);
}