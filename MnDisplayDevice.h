#pragma once

#include <d3d11.h>
#include <vector>
#include "MNL.h"

namespace MNL
{
	struct MnDisplayMode
	{
		UINT width, height;
		UINT numerator, denominator;
	};
	class MnDisplayDevice
	{
	public:
		MnDisplayDevice();
		~MnDisplayDevice();
		/*
		Initialize and get display modes from device
		*/
		HRESULT Init(CPDXGIOutput cpOutput);

		const CPDXGIOutput GetInterface() const;
		/*
		Get closest display mode in the supported resolutions
		*/
		MnDisplayMode GetClosestMode(UINT width, UINT height, UINT numerator, UINT denominator) const;


		/*
		check whether display device supports the resolution
		@return false if display device does not support
		*/
		bool IsSupportResolutionOf(UINT width, UINT height) const;

		UINT GetNumDisplayModes() const;


	private:
		std::vector<DXGI_MODE_DESC> m_displayModeDescs;
		std::vector<MnDisplayMode>  m_displayModes;
		UINT						m_numDisplayModes;
		CPDXGIOutput				m_cpDXGIOutput;
	};
}