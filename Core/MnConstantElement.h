#pragma once
#include <d3d11.h>

namespace MNL
{
	enum MnConstantElementType
	{
		MN_CONSTANT_ELEMENT_TYPE_NONE,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT1,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT2,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT3,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT4,
		MN_CONSTANT_ELEMENT_TYPE_MATRIX33,
		MN_CONSTANT_ELEMENT_TYPE_MATRIX44,
	};
	/*
	@function represents one data type in cbuffer
	@include stores MnConstantElementType, DXGI_FORMAT, byte size of representing type
	*/
	class MnConstantElement
	{
	public:
		MnConstantElement(const MnConstantElementType& inputElementType, UINT index);
		~MnConstantElement();
		MnConstantElementType GetType() const;
		/*
		Get byte size of representing type. eg) MN_CONSTANT_ELEMENT_TYPE_FLOAT4 as sizeof(float)*4
		*/
		UINT GetByteSize() const;
		/*
		Get DXGI_FORMAT for D3D device context
		*/
		DXGI_FORMAT GetDXGIFormat() const;

	private:
		//prevent create with no type
		MnConstantElement();
		HRESULT _Init(const MnConstantElementType& constantElementType,UINT index);
		UINT _GetByteSizeOf(const MnConstantElementType& constantElementType);

	private:
		MnConstantElementType		m_type;
		UINT						m_byteSize;
		UINT						m_index;
	};
}