#include "MnConstantElement.h"

using namespace MNL;

MnConstantElement::MnConstantElement()
{
}


MnConstantElement::~MnConstantElement()
{
}
MnConstantElement::MnConstantElement(const MnConstantElementType& constantElementType,UINT index)
{
	HRESULT result = _Init(constantElementType,index);
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
	
HRESULT MnConstantElement::_Init(const MnConstantElementType& constantElementType,UINT index)
{
	if (constantElementType == MN_CONSTANT_ELEMENT_TYPE_NONE)
	{
		//error log here
		return E_FAIL;
	}

	m_type = constantElementType;
	m_byteSize = _GetByteSizeOf(constantElementType);
	m_index = index;

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