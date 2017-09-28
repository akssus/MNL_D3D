#pragma once
#include <d3d11.h>
#include <vector>
#include "MnConstantElement.h"

namespace MNL
{
	/*
	@function store MnConstantElement and desribe a cbuffer, get total byte size and number of elements
	@include series of constant elements, total byte size
	*/
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

		/*
		@return byte size with multiple of 16
		*/
		UINT PaddedByteSize() const;
		/**
		@return count of input elements
		*/
		UINT NumElements() const;

	private:
		std::vector<MnConstantElement> m_constantElements;
		UINT							m_totalByteSize;
	};
}
