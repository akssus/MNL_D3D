#include "MnInputElement.h"

using namespace MNL;

MnInputElement::MnInputElement():m_type(MN_INPUT_ELEMENT_TYPE_NONE),
								 m_byteSize(0)
{
}

MnInputElement::MnInputElement(std::string semanticName, MnInputElementType& inputElementType) : m_type(MN_INPUT_ELEMENT_TYPE_NONE),
																								 m_byteSize(0)
{
	_Init(semanticName, inputElementType);
}

MnInputElement::~MnInputElement()
{
}

bool MnInputElement::_Init(std::string semanticName, MnInputElementType& inputElementType)
{
	ZeroMemory(&m_desc, sizeof(D3D11_INPUT_ELEMENT_DESC));
	return _SetDesc(semanticName, inputElementType);
}

std::string	MnInputElement::GetSemanticName() const
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
D3D11_INPUT_ELEMENT_DESC MnInputElement::GetDesc() const
{
	return m_desc;
}
DXGI_FORMAT MnInputElement::GetDXGIFormat() const
{
	return m_desc.Format;
}

bool MnInputElement::_SetDesc(std::string semanticName, MnInputElementType& inputElementType)
{
	if (inputElementType == MN_INPUT_ELEMENT_TYPE_NONE)
	{
		//error log here
		return false;
	}
	_SetFormat(inputElementType, m_desc);
	m_desc.SemanticName = semanticName.c_str();
	m_desc.SemanticIndex = 0;
	m_desc.InputSlot = 0;
	m_desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	m_desc.InstanceDataStepRate = 0;
	m_desc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	return true;
}

void MnInputElement::_SetFormat(MnInputElementType& inputElementType, D3D11_INPUT_ELEMENT_DESC& inputElementDesc)
{
	switch (inputElementType)
	{
	case MN_INPUT_ELEMENT_TYPE_FLOAT1:
		inputElementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		m_byteSize = sizeof(float);
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT2:
		inputElementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		m_byteSize = sizeof(float) * 2;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT3:
		inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		m_byteSize = sizeof(float) * 3;
		break;
	case MN_INPUT_ELEMENT_TYPE_FLOAT4:
		inputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_byteSize = sizeof(float) * 4;
		break;
	}
}