#include "MnGameObjectComponent.h"
#include "MnGameObject.h"
#include <cassert>

using namespace MNL;

MnGameObjectComponent::MnGameObjectComponent()
	: m_pAttatchedGameObject(nullptr)
{
}


MnGameObjectComponent::~MnGameObjectComponent()
{
}


std::string MnGameObjectComponent::GetComponentName() const
{
	return typeid(*this).name();
}

template <class T>
std::shared_ptr<T> MnGameObjectComponent::GetComponent()
{
	assert(m_pAttatchedGameObject != nullptr);
	return m_pAttatchedGameObject->GetComponent<T>();
}

const MnGameObject* MnGameObjectComponent::GameObject() const
{
	return m_pAttatchedGameObject;
}

void MnGameObjectComponent::_SetAttatchedGameObject(MnGameObject* pGameObject)
{
	assert(pGameObject != nullptr);
	m_pAttatchedGameObject = pGameObject;
}