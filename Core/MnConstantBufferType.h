/**
@class MnConstantBufferType
@brief 상수버퍼 내 데이터타입의 컨테이너 역할을 하는 클래스.
@author Akssus
@section 개요
MnConstantElement 객체 리스트를 가지고 상수버퍼의 struct 역할을 한다.

*/

#pragma once
#include <d3d11.h>
#include <vector>
#include "MnConstantElement.h"

namespace MNL
{
	class MnConstantBufferType
	{
	public:
		MnConstantBufferType();
		~MnConstantBufferType();

		/**
		* Add a input element to description. input layout will be placed by adding order
		*/
		void AddConstantElement(const MnConstantElement& inputElement);
		/**
		Get a input element
		@param index of the input elemenet
		*/
		const MnConstantElement& GetElement(UINT index) const;
		/**
		@return total byte size of whole constant elements
		*/
		UINT TotalByteSize() const;

		/**
		@return byte size with multiple of 16
		*/
		UINT PaddedByteSize() const;
		
		/**
		@return count of input elements
		*/
		UINT NumElements() const;

	private:
		std::vector<MnConstantElement> m_constantElements;
		UINT m_totalByteSize;
	};
}
