#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>
#include "MnTypedefs.h"
#include "MnInputElement.h"


namespace MNL
{
	/**
	MnCustomVertex holds vertex semantics, vertex structure
	*/
	class MnCustomVertexType
	{
	public:
		MnCustomVertexType();
		~MnCustomVertexType();
		
		/**
		* Add a input element to description. input layout will be placed by adding order
		*/
		void AddInputElement(const MnInputElement& inputElement);
		/**
		Get a input element
		@param index of the input elemenet
		*/
		const MnInputElement& GetElement(UINT index) const;
		/**
		@return total byte size of whole input elements
		*/
		UINT TotalByteSize() const;
		/**
		@return count of input elements
		*/
		UINT NumElements() const;

	private:
		std::vector<MnInputElement> m_inputElements;
		UINT						m_totalByteSize;
	};
}