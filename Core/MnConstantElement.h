/**
@class MnConstantElement
@brief 상수버퍼 내 데이터타입 단위
@author Akssus
@section 개요
MnConstantBufferType 에 소속되어 하나의 데이터타입을 나타내는 단위 객체.
상수 버퍼의 참조 및 업데이트가 여러곳에서 실행될 경우 상수버퍼의 데이터 스트럭쳐(struct)를 일일히 알아야 하는 번거로움을 피하기 위해 만들어졌다.\n
오직 주어진 기본형들만이 사용 가능하며 상수버퍼 내에서 쓰이는 FLOAT, MATRIX, UINT 등을 쓸 수 있고 이는 MN_CONSTANT_ELEMENT_TYPE 으로 정의된다.
*/


#pragma once
#include <d3d11.h>
#include <string>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	/**
	@brief 요소의 데이터타입을 정의하는 열거형. 정상적으로 초기화 되지 않은 요소는 MN_CONSTANT_ELEMENT_TYPE_NONE 값을 가진다.
	*/
	enum MN_CONSTANT_ELEMENT_TYPE
	{
		MN_CONSTANT_ELEMENT_TYPE_NONE,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT1,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT2,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT3,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT4,
		MN_CONSTANT_ELEMENT_TYPE_MATRIX,
		MN_CONSTANT_ELEMENT_TYPE_UINT,
	};
	class MnConstantElement
	{
	public:
		MnConstantElement(const MN_CONSTANT_ELEMENT_TYPE& inputElementType);
		~MnConstantElement();

		/**
		@brief 요소의 element type을 반환한다.
		*/
		MN_CONSTANT_ELEMENT_TYPE GetType() const;
		/**
		@brief 요소의 바이트 사이즈를 반환한다. 예) MN_CONSTANT_ELEMENT_TYPE_FLOAT4 은 sizeof(float)*4 를 반환한다.
		*/
		UINT GetByteSize() const;

	private:
		/**
		@brief 
		*/
		MnConstantElement();
		HRESULT _Init(const MN_CONSTANT_ELEMENT_TYPE& constantElementType);
		UINT _GetByteSizeOf(const MN_CONSTANT_ELEMENT_TYPE& constantElementType);

	private:
		std::string					m_name;
		MN_CONSTANT_ELEMENT_TYPE	m_type;
		UINT						m_byteSize;
	};
}