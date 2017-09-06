#include "MnConstantBufferType.h"

using namespace MNL;

MnConstantBufferType::MnConstantBufferType():m_totalByteSize(0)
{
}


MnConstantBufferType::~MnConstantBufferType()
{
}

void MnConstantBufferType::AddConstantElement(const MnConstantElement& inputElement)
{
	m_constantElements.push_back(inputElement);
	m_totalByteSize += inputElement.GetByteSize();
}
const MnConstantElement& MnConstantBufferType::GetElement(UINT index) const
{
	return m_constantElements[index];
}

UINT MnConstantBufferType::TotalByteSize() const
{
	return m_totalByteSize;
}
UINT MnConstantBufferType::PaddedByteSize() const
{
	return 16 * std::ceil(m_totalByteSize / 16);
}
UINT MnConstantBufferType::NumElements() const
{
	return m_constantElements.size();
}