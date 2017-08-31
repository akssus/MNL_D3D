#pragma once
#include <d3d11.h>
#include <string>
#include "MNL.h"


namespace MNL
{
	enum MnInputElementType
	{
		MN_INPUT_ELEMENT_TYPE_NONE,
		MN_INPUT_ELEMENT_TYPE_FLOAT1,
		MN_INPUT_ELEMENT_TYPE_FLOAT2,
		MN_INPUT_ELEMENT_TYPE_FLOAT3,
		MN_INPUT_ELEMENT_TYPE_FLOAT4,
	};
	/*
	MnInputElement represents a vertex element in IA and InputLayout
	*/
	class MnInputElement
	{
	public:
		MnInputElement(std::string semanticName, MnInputElementType& inputElementType);
		~MnInputElement();

		std::string	GetSemanticName() const;
		MnInputElementType GetType() const;
		UINT GetByteSize() const;
		D3D11_INPUT_ELEMENT_DESC GetDesc() const;
		DXGI_FORMAT GetDXGIFormat() const;

	private:
		MnInputElement();
		bool _Init(std::string semanticName, MnInputElementType& inputElementType);
		bool _SetDesc(std::string semanticName, MnInputElementType& inputElementType);
		void _SetFormat(MnInputElementType& inputElementType, D3D11_INPUT_ELEMENT_DESC& inputElementDesc);

	private:
		D3D11_INPUT_ELEMENT_DESC	m_desc;
		std::string					m_semanticName;
		MnInputElementType			m_type;
		UINT						m_byteSize;
	};

}