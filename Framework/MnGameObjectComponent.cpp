#include "MnGameObjectComponent.h"
#include "MnGameObject.h"
#include "MnGameWorld.h"
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

const MnGameObject* MnGameObjectComponent::GameObject() const
{
	return m_pAttatchedGameObject;
}
bool MnGameObjectComponent::IsAttatched() const
{
	return (m_pAttatchedGameObject != nullptr);
}
void MnGameObjectComponent::_SetAttatchedGameObject(MnGameObject* pGameObject)
{
	assert(pGameObject != nullptr);
	m_pAttatchedGameObject = pGameObject;
}
