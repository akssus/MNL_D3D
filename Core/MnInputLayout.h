#pragma once
#include <d3d11.h>
#include <memory>
#include "MnTypedefs.h"
#include "MnVertexShader.h"
#include "MnCustomVertexType.h"

namespace MNL
{
	class MnInputLayout
	{
	public:
		MnInputLayout();
		~MnInputLayout();

		/*
		Initialize input layout
		@return false if failed to initialize
		*/
		bool Init(CPD3DDevice cpD3DDevice, const std::shared_ptr<MnCustomVertexType> pCustomVertexType, const std::shared_ptr<MnVertexShader> pVertexShader);
		CPD3DInputLayout GetInputLayout() const;

	private:
		D3D11_INPUT_ELEMENT_DESC _CreateInputElementDesc(const MnInputElement& inputElement);

	private:
		CPD3DInputLayout m_inputLayout;
	};
}