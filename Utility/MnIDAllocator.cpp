#include "MnIDAllocator.h"
#include <assert.h>

using namespace MNL;

MnIDAllocator::MnIDAllocator(): 
	m_offset(0),
	m_length(0)
{
}


MnIDAllocator::~MnIDAllocator()
{
}

void MnIDAllocator::SetRange(int min, int max)
{
	assert(min <= max);
	assert(min >= 0);
	assert(max >= 0);
	m_offset = min;
	m_length = max - min + 1;
	m_idPool.resize(m_length,false);
}

int MnIDAllocator::Allocate() 
{
	for (int i = 0; i < m_length; ++i)
	{
		if (m_idPool[i] == false)
		{
			int id = i + m_offset;
			m_idPool[i] = true;
			return id;
		}
	}
}

void MnIDAllocator::Deallocate(int id)
{
	int index = id - m_offset;
	m_idPool[index] = false;
}

void MnIDAllocator::Register(int id)
{
	assert(m_offset <= id && id <= (m_offset + m_length));
	int index = id - m_offset;
	m_idPool[index] = true;
}