#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>
#include "MNL.h"


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
		MnInputElement GetElement(UINT index) const;
		/**
		@return total byte size of whole input elements
		*/
		UINT TotalByteSize() const;
		/**
		@return count of input elements
		*/
		UINT NumElements() const;


		/**
		Create input layout according to inner structure
		@return created input layout pointer
		*/
		CPD3DInputLayout CreateInputLayout(CPD3DDevice cpDevice, std::shared_ptr<MnVertexShader> pVertexShader);

	private:
		std::vector<MnInputElement> m_inputElements;
		UINT						m_totalByteSize;
	};
}