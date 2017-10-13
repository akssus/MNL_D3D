#include "Framework\LightList.h"

using namespace MNL;

LightList::LightList()
{
}


LightList::~LightList()
{
}


void LightList::AddLight(const std::shared_ptr<MnLightSource>& spLight)
{
	m_lstLights.push_back(spLight);
}
void LightList::RemoveLight(int index)
{
	assert(index >= 0 && index < m_lstLights.size());
	m_lstLights.erase(m_lstLights.begin() + index);
}
void LightList::ClearLights()
{
	m_lstLights.clear();
}

std::vector<std::shared_ptr<MnLightSource>>& LightList::GetLights()
{
	return m_lstLights;
}
std::shared_ptr<MnLightSource>& LightList::GetLight(int index)
{
	assert(index >= 0 && index < m_lstLights.size());
	return m_lstLights[index];
}