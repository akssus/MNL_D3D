#include <memory>
#include "MnCustomVertexType.h"

using namespace MNL;

MnCustomVertexType::MnCustomVertexType():m_totalByteSize(0)
{
}


MnCustomVertexType::~MnCustomVertexType()
{
}

void MnCustomVertexType::AddInputElement(const MnInputElement& inputElement)
{
	m_inputElements.push_back(inputElement);
	m_totalByteSize += inputElement.GetByteSize();
}

const MnInputElement& MnCustomVertexType::GetElement(UINT index) const
{
	return m_inputElements[index];
}
UINT MnCustomVertexType::TotalByteSize() const
{
	return m_totalByteSize;
}
UINT MnCustomVertexType::NumElements() const
{
	return m_inputElements.size();
}