/**
@class MNL::MnCustomVertexType
@brief 버텍스 구조체의 크기, 시맨틱 배치 등을 명세하는 객체. 실제 값은 가지고 있지 않는다.
@author Akssus
@section 개요
버텍스 셰이더와 버텍스 버퍼, 그리고 메시 읽기를 위해선 struct 구조체로 버텍스의 테이터타입을 정의해야 하는데, 
셰이더 혹은 메시 별로 버텍스의 구조가 다른 경우 쓸데없이 많은 구조체 정의가 필요하단 불편이 있다. \n
그러므로 버텍스의 구조가 어떠하며, 버텍스 한개당 메모리 크기는 얼마나 할당되는지, 내부에 시맨틱 구조는 어떻게 되어 있는지 명세할 클래스가 필요하다. \n
이를 구현한 것이 MnCustomVertexType 클래스이며 데이터타입의 "선언" 역할만을 하고 타입의 값을 내부에 갖지는 않는다. \n
즉, struct 역할을 대신 해주기도 하며 인풋 레이아웃의 역할도 같이 해준다.\n
\n
엘리먼트 추가 시 자동으로 POSITION, NORMAL, TEXCOORD 순으로 정렬된다.
*/


#include <memory>
#include <algorithm>
#include "MnCustomVertexType.h"

using namespace MNL;

MnCustomVertexType::MnCustomVertexType():m_totalByteSize(0),m_flags(0)
{
}


MnCustomVertexType::~MnCustomVertexType()
{
}

void MnCustomVertexType::AddInputElement(const MnInputElement& inputElement, MN_CUSTOM_VERTEX_FLAG flags)
{
	m_inputElements.push_back(inputElement);
	m_totalByteSize += inputElement.GetByteSize();

	_SetOptionalFlags(flags);
	_SortInputElements();
}
void MnCustomVertexType::AddInputElement(const MnInputElement& inputElement)
{
	m_inputElements.push_back(inputElement);
	m_totalByteSize += inputElement.GetByteSize();

	UINT inputIndex = inputElement.GetIndex();
	_SetFlag(inputElement.GetSemanticName(), inputIndex);
	_SortInputElements();
}
void MnCustomVertexType::_SetFlag(const std::string& semanticName, UINT index)
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
void MnCustomVertexType::_SetOptionalFlags(MN_CUSTOM_VERTEX_FLAG flags)
{
	m_flags |= flags;
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
void MnCustomVertexType::_SortInputElements()
{
	std::sort(m_inputElements.begin(), m_inputElements.end(), [](MnInputElement& inputElement_1, MnInputElement& inputElement_2) {
		if (inputElement_1.GetSemanticName() == "POSITION" && inputElement_2.GetSemanticName() == "NORMAL")
		{
			return true;
		}
		else if (inputElement_1.GetSemanticName() == "POSITION" && inputElement_2.GetSemanticName() == "TEXCOORD")
		{
			return true;
		}
		else if (inputElement_1.GetSemanticName() == "NORMAL" && inputElement_2.GetSemanticName() == "TEXCOORD")
		{
			return true;
		}
		else if (inputElement_1.GetSemanticName() == inputElement_2.GetSemanticName())
		{
			if (inputElement_1.GetIndex() < inputElement_2.GetIndex()) return true;
		}
		return false;
	});
}