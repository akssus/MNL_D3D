#pragma once

#include <d3d11.h>
#include <vector>
#include "MNL.h"

namespace MNL
{
	class MnDisplayDevice
	{
	public:
		MnDisplayDevice();
		~MnDisplayDevice();


		bool IsSupportResolutionOf(UINT width, UINT height);

	private:
		std::vector<DXGI_MODE_DESC> m_displayModes;
		UINT						m_numDisplayModes;
	};
}