#include "MnConstantElement.h"

using namespace MNL;

MnConstantElement::MnConstantElement():m_byteSize(0),m_type(MN_CONSTANT_ELEMENT_TYPE_NONE)
{
}


MnConstantElement::~MnConstantElement()
{
}
MnConstantElement::MnConstantElement(const MnConstantElementType& constantElementType) :m_byteSize(0), m_type(MN_CONSTANT_ELEMENT_TYPE_NONE)
{
	HRESULT result = _Init(constantElementType);
	if (FAILED(result))
	{
		//error log
	}
}
MnConstantElementType MnConstantElement::GetType() const
{
	return m_type;
}
UINT MnConstantElement::GetByteSize() const
{
	return m_byteSize;
}
	
HRESULT MnConstantElement::_Init(const MnConstantElementType& constantElementType)
{
	if (constantElementType == MN_CONSTANT_ELEMENT_TYPE_NONE)
	{
		//error log here
		return E_FAIL;
	}

	m_type = constantElementType;
	m_byteSize = _GetByteSizeOf(constantElementType);

	return S_OK;
}
UINT MnConstantElement::_GetByteSizeOf(const MnConstantElementType& constantElementType)
{
	UINT byteSize = 0;
	switch (constantElementType)
	{
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT1: byteSize = sizeof(float);  break;
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT2: byteSize = sizeof(float)*2;  break;
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT3: byteSize = sizeof(float)*3;  break;
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT4: byteSize = sizeof(float)*4;  break;
	case MN_CONSTANT_ELEMENT_TYPE_MATRIX: byteSize = sizeof(float)*64;  break;
	}
	return byteSize;
}