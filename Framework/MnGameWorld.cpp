#include "MnGameWorld.h"
#include <cassert>

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

void MnGameWorld::OnInit()
{
	//nothing
}

void MnGameWorld::AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent)
{
	assert(spComponent != nullptr);
	std::string key = spComponent->GetComponentName();
	spComponent->_SetAttatchedWorld(this);
	m_tblComponents[key] = spComponent;
}

template <class T>
std::shared_ptr<T>& MnGameWorld::GetComponent()
{
	std::string key = typeid(T).name();
	if (m_tblComponents.count(key) == 0)
	{
		return nullptr;
	}
	return std::dynamic_pointer_cast<T>(m_tblComponents[key]);
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