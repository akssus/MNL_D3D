#include "MnGameWorld.h"
#include <cassert>

using namespace MNL;

MnGameWorld::MnGameWorld()
{
}


MnGameWorld::~MnGameWorld()
{
}


void MnGameWorld::AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent)
{
	assert(spComponent != nullptr);
	std::string key = spComponent->GetComponentName();
	spComponent->_SetAttatchedWorld(this);
	m_tblComponents[key] = spComponent;
}

template <class T>
std::shared_ptr<T> MnGameWorld::GetComponent()
{
	std::string key = typeid(T).name();
	if (m_tblComponents.count(key) == 0)
	{
		return nullptr;
	}
	return std::dynamic_pointer_cast<T>(m_tblComponents[key]);
}