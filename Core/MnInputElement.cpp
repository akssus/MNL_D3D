#include "MnInputElement.h"

using namespace MNL;

MnInputElement::MnInputElement():m_type(MN_INPUT_ELEMENT_TYPE_NONE),
								 m_byteSize(0), 
								 m_format(DXGI_FORMAT_UNKNOWN)
{
}

MnInputElement::MnInputElement(std::string semanticName, const MnInputElementType& inputElementType, UINT index) : 
	m_type(MN_INPUT_ELEMENT_TYPE_NONE),																			 
	m_byteSize(0),																 
	m_format(DXGI_FORMAT_UNKNOWN)
{
	_Init(semanticName, inputElementType,index);
}

MnInputElement::~MnInputElement()
{
}

bool MnInputElement::_Init(std::string semanticName, const MnInputElementType& inputElementType,UINT index)
{
	if (inputElementType == MN_INPUT_ELEMENT_TYPE_NONE)
	{
		//error log here
		return false;
	}

	m_semanticName = semanticName;
	m_type = inputElementType;
	m_format = _ConvertToDXGIFormat(inputElementType);
	m_byteSize = _GetByteSizeOf(inputElementType);
	m_index = index;

	return true;
}

const std::string& MnInputElement::GetSemanticName() const
{
	return m_semanticName;
}
MnInputElementType MnInputElement::GetType() const
{
	return m_type;
}
UINT MnInputElement::GetByteSize() const
{
	return m_byteSize;
}
DXGI_FORMAT MnInputElement::GetDXGIFormat() const
{
	return m_format;
}

UINT MnInputElement::GetIndex() const
{
	return m_index;
}

DXGI_FORMAT MnInputElement::_ConvertToDXGIFormat(const MnInputElementType& inputElementType)
{
	DXGI_FORMAT format;
	switch (inputElementType)
	{
	case MN_INPUT_ELEMENT_TYPE_FLOAT1:
		format = DXGI_FORMAT_R32_FLOAT;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT2:
		format = DXGI_FORMAT_R32G32_FLOAT;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT3:
		format = DXGI_FORMAT_R32G32B32_FLOAT;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT4:
		format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	}
	return format;
}
UINT MnInputElement::_GetByteSizeOf(const MnInputElementType& inputElementType)
{
	UINT byteSize = 0;
	switch (inputElementType)
	{
	case MN_INPUT_ELEMENT_TYPE_FLOAT1:
		byteSize = sizeof(float);
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT2:
		byteSize = sizeof(float) * 2;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT3:
		byteSize = sizeof(float) * 3;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT4:
		byteSize = sizeof(float) * 4;
		break;
	}
	return byteSize;
}