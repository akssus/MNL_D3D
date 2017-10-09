#include "MnConstantElement.h"
#include "MnLog.h"

using namespace MNL;

MnConstantElement::MnConstantElement():m_byteSize(0),m_type(MN_CONSTANT_ELEMENT_TYPE_NONE)
{
}


MnConstantElement::~MnConstantElement()
{
}
MnConstantElement::MnConstantElement(const MN_CONSTANT_ELEMENT_TYPE& constantElementType) :m_byteSize(0), m_type(MN_CONSTANT_ELEMENT_TYPE_NONE)
{
	HRESULT result = _Init(constantElementType);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnConstantElement));
	}
}
MN_CONSTANT_ELEMENT_TYPE MnConstantElement::GetType() const
{
	return m_type;
}
UINT MnConstantElement::GetByteSize() const
{
	return m_byteSize;
}
	
HRESULT MnConstantElement::_Init(const MN_CONSTANT_ELEMENT_TYPE& constantElementType)
{
	if (constantElementType == MN_CONSTANT_ELEMENT_TYPE_NONE)
	{
		MnLog::MB_IsNull(MN_VAR_INFO(constantElementType));
		return E_FAIL;
	}

	m_type = constantElementType;
	m_byteSize = _GetByteSizeOf(constantElementType);

	return S_OK;
}
UINT MnConstantElement::_GetByteSizeOf(const MN_CONSTANT_ELEMENT_TYPE& constantElementType)
{
	UINT byteSize = 0;
	switch (constantElementType)
	{
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT1: byteSize = sizeof(float);  break;
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT2: byteSize = sizeof(float)*2;  break;
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT3: byteSize = sizeof(float)*3;  break;
	case MN_CONSTANT_ELEMENT_TYPE_FLOAT4: byteSize = sizeof(float)*4;  break;
	case MN_CONSTANT_ELEMENT_TYPE_MATRIX: byteSize = sizeof(float)*16;  break;
	case MN_CONSTANT_ELEMENT_TYPE_UINT: byteSize = sizeof(UINT);  break;
	}
	return byteSize;
}