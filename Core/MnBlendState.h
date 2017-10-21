#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnBlendState
	{
	public:
		MnBlendState();
		~MnBlendState();

		HRESULT Init(const CPD3DDevice& cpDevice, bool alphaTestEnable);
		
		const CPD3DBlendState& GetState() const;

	private:
		CPD3DBlendState m_cpBlendState;
	};
}
