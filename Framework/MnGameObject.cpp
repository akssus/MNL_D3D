#include "MnGameObject.h"
#include <cassert>

using namespace MNL;

MnGameObject::MnGameObject()
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

template <class T>
std::shared_ptr<T> MnGameObject::GetComponent()
{
	std::string key = typeid(T).name();
	if (m_tblComponenets.count(key) == 0)
	{
		return nullptr;
	}
	//다운캐스팅 실패시 자동으로 nullptr 반환
	return std::dynamic_pointer_cast<T>(m_tblComponenets[key]);
}