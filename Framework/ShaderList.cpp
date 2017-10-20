#include "ShaderList.h"
#include <algorithm>

using namespace MNL;

ShaderList::ShaderList()
{
	_Init();
}


ShaderList::~ShaderList()
{
}

void ShaderList::_Init()
{
	m_idAllocator.SetRange(0, 100);
}

void ShaderList::AddShader(const std::shared_ptr<Shader>& spShader)
{
	assert(spShader != nullptr);
	auto id = m_idAllocator.Allocate();
	AddShader(spShader, id);
}

void ShaderList::AddShader(const std::shared_ptr<Shader>& spShader, int id)
{
	assert(spShader != nullptr);
	m_idAllocator.Register(id);
	spShader->_Init(GameWorld());
	spShader->SetID(id);
	m_lstShaders[id] = spShader;
	m_renderOrder.push_back(id);
	spShader->OnAttatched();
}

void ShaderList::RemoveShader(int id)
{
	m_lstShaders.erase(id);
	m_idAllocator.Deallocate(id);
	for (int i = 0; i < m_renderOrder.size(); ++i)
	{
		if (m_renderOrder[i] == id)
		{
			m_renderOrder.erase(m_renderOrder.begin() + i);
		}
	}
}

std::shared_ptr<Shader> ShaderList::GetShader(int id)
{
	if (m_lstShaders.count(id) == 0)
	{
		return nullptr;
	}
	return m_lstShaders[id];
}

std::map<int, std::shared_ptr<Shader>>& ShaderList::GetShaders()
{
	return m_lstShaders;
}


void ShaderList::SetRenderOrder(std::initializer_list<int> idOrder)
{
	m_renderOrder = idOrder;
}
const std::vector<int>& ShaderList::GetRenderOrder() const
{
	return m_renderOrder;
}
