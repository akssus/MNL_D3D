#include "MnConstantBufferType.h"

using namespace MNL;

MnConstantBufferType::MnConstantBufferType()
{
}


MnConstantBufferType::~MnConstantBufferType()
{
}

void MnConstantBufferType::AddConstantElement(const MnConstantElement& inputElement)
{
	m_constantElements.push_back(inputElement);
}
MnConstantElement MnConstantBufferType::GetElement(UINT index) const
{
	return m_constantElements[index];
}

UINT MnConstantBufferType::TotalByteSize() const
{
	return m_totalByteSize;
}
UINT MnConstantBufferType::NumElements() const
{
	return m_constantElements.size();
}