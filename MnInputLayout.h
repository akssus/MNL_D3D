#pragma once
#include <d3d11.h>
#include <memory>
#include "MNL.h"

namespace MNL
{
	class MnInputLayout
	{
	public:
		MnInputLayout();
		~MnInputLayout();

		void Init(CPD3DDevice cpD3DDevice,std::shared_ptr<MnCustomVertexType> pCustomVertexType, std::shared_ptr<MnVertexShader> pVertexShader);
		CPD3DInputLayout GetInputLayout() const;

	private:
		CPD3DInputLayout m_inputLayout;
	};
}