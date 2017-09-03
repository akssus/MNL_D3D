#pragma once
#include <d3d11.h>
#include <vector>
#include "MnTypedefs.h"
#include "MnVideoAdapter.h"
#include "MnDisplayDevice.h"

namespace MNL
{
	class MnHardware
	{
	public:
		MnHardware();
		~MnHardware();

		/*
		initialize hardware information
		*/
		HRESULT			Init();

		UINT				GetNumVideoAdapters() const;
		const MnVideoAdapter	GetVideoAdapter(UINT index) const;

		/*
		Get GPU's maximum supported feature level. 
		@return D3D_FEATURE_LEVEL_9_1 at minimum
		*/
		D3D_FEATURE_LEVEL GetMaxSupportedFeatrueLevel(UINT adapterIndex) const;
		

	private:
		std::vector<MnVideoAdapter>		m_videoAdapters;
	};
}
