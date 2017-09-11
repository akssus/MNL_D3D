#include <memory>
#include "MnCustomVertexType.h"

using namespace MNL;

MnCustomVertexType::MnCustomVertexType():m_totalByteSize(0),m_flags(0)
{
}


MnCustomVertexType::~MnCustomVertexType()
{
}

void MnCustomVertexType::AddInputElement(const MnInputElement& inputElement)
{
	m_inputElements.push_back(inputElement);
	m_totalByteSize += inputElement.GetByteSize();

	UINT inputIndex = inputElement.GetIndex();
	_SetFlag(inputElement.GetSemanticName(), inputIndex);
}
void MnCustomVertexType::_SetFlag(std::string semanticName, UINT index)
{
	if (semanticName == "POSITION")
	{
		switch (index)
		{
		case 0: m_flags |= MN_CVF_POSITION0; break;
		case 1: m_flags |= MN_CVF_POSITION1; break;
		case 2: m_flags |= MN_CVF_POSITION2; break;
		case 3: m_flags |= MN_CVF_POSITION3; break;
		}
	}
	else if (semanticName == "NORMAL")
	{
		switch (index)
		{
		case 0: m_flags |= MN_CVF_NORMAL0; break;
		case 1: m_flags |= MN_CVF_NORMAL1; break;
		case 2: m_flags |= MN_CVF_NORMAL2; break;
		case 3: m_flags |= MN_CVF_NORMAL3; break;
		}
	}
	else if (semanticName == "TEXCOORD")
	{
		switch (index)
		{
		case 0: m_flags |= MN_CVF_TEXCOORD0; break;
		case 1: m_flags |= MN_CVF_TEXCOORD1; break;
		case 2: m_flags |= MN_CVF_TEXCOORD2; break;
		case 3: m_flags |= MN_CVF_TEXCOORD3; break;
		}
	}
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
const UINT16& MnCustomVertexType::GetFlags() const
{
	return m_flags;
}