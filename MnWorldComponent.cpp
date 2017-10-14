#include "Framework\MnWorldComponent.h"
#include <cassert>

using namespace MNL;

MnWorldComponent::MnWorldComponent():
	m_pAttatchedWorld(nullptr)
{
}


MnWorldComponent::~MnWorldComponent()
{
}


std::string MnWorldComponent::GetComponentName() const
{
	return typeid(*this).name();
}

template <class T>
std::shared_ptr<T> MnWorldComponent::GetComponent()
{
	assert(m_pAttatchedWorld != nullptr);
	return m_pAttatchedWorld->GetComponent<T>();
}

MnGameWorld* MnWorldComponent::GameWorld() const
{
	return m_pAttatchedWorld;
}

void MnWorldComponent::_SetAttatchedWorld(MnGameWorld* pGameWorld)
{
	assert(pGameWorld != nullptr);
	m_pAttatchedWorld = pGameWorld;
}