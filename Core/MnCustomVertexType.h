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
	Size of semantics:
	POSITION : float3
	NORMAL : float3
	TEXCOORD : float2
	OPTION flags is optional for future use
	*/
	enum MN_CUSTOM_VERTEX_FLAG
	{
		MN_CVF_POSITION0 = 0x8000,
		MN_CVF_POSITION1 = 0x4000,
		MN_CVF_POSITION2 = 0x2000,
		MN_CVF_POSITION3 = 0x1000,
		MN_CVF_NORMAL0 = 0x0800,
		MN_CVF_NORMAL1 = 0x0400,
		MN_CVF_NORMAL2 = 0x0200,
		MN_CVF_NORMAL3 = 0x0100,
		MN_CVF_TEXCOORD0 = 0x0080,
		MN_CVF_TEXCOORD1 = 0x0040,
		MN_CVF_TEXCOORD2 = 0x0020,
		MN_CVF_TEXCOORD3 = 0x0010,
		MN_CVF_OPTION0 = 0x0008,
		MN_CVF_OPTION1 = 0x0004,
		MN_CVF_OPTION2 = 0x0002,
		MN_CVF_OPTION3 = 0x0001,
	};
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

		const UINT16& GetFlags() const;

	private:
		void _SetFlag(std::string semanticName, UINT index);

	private:
		std::vector<MnInputElement> m_inputElements;
		UINT						m_totalByteSize;
		/**
		 0x   F     F    F     F
		     POS  NORM  TEX   OPT
		*/
		UINT16						m_flags;
	};
}