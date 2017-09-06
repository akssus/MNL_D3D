#pragma once
#include <d3d11.h>
#include <string>
#include "MnTypedefs.h"


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
		MnInputElement(std::string semanticName, const MnInputElementType& inputElementType,UINT index);
		~MnInputElement();

		const std::string& GetSemanticName() const;
		MnInputElementType GetType() const;
		UINT GetByteSize() const;
		DXGI_FORMAT GetDXGIFormat() const;
		UINT GetIndex() const;

	private:
		MnInputElement();
		bool _Init(std::string semanticName, const MnInputElementType& inputElementType,UINT index);
		DXGI_FORMAT _ConvertToDXGIFormat(const MnInputElementType& inputElementType);
		UINT _GetByteSizeOf(const MnInputElementType& inputElementType);

	private:
		std::string					m_semanticName;
		MnInputElementType			m_type;
		DXGI_FORMAT					m_format;
		UINT						m_byteSize;
		UINT						m_index;
	};

}