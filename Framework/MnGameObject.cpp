#include "MnGameObject.h"
#include <cassert>

using namespace MNL;

MnGameObject::MnGameObject() : m_id(0)
{
}


MnGameObject::~MnGameObject()
{
}

void MnGameObject::AddComponent(const std::shared_ptr<MnGameObjectComponent>& spComponent)
{
	assert(spComponent != nullptr);
	std::string key = spComponent->GetComponentName();
	spComponent->_SetAttatchedGameObject(this);
	m_tblComponents[key] = spComponent;
}


void MnGameObject::SetTag(const std::string& tag)
{
	m_tag = tag;
}
std::string MnGameObject::GetTag() const
{
	return m_tag;
}

void MnGameObject::SetID(UINT id)
{
	m_id = id;
}
UINT MnGameObject::GetID() const
{
	return m_id;
}

MnGameWorld* MnGameObject::GameWorld() const
{
	return m_pGameWorld;
}

void MnGameObject::_SetGameWorld(MnGameWorld* pGameWorld)
{
	assert(pGameWorld != nullptr);
	m_pGameWorld = pGameWorld;
}