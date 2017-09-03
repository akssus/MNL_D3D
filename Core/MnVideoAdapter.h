#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"
#include "MnDisplayDevice.h"

namespace MNL
{
	/*
	one IDXGIAdapter represnets one MnVideoAdapter instance
	*/
	class MnVideoAdapter
	{
	public:
		MnVideoAdapter();
		~MnVideoAdapter();

		HRESULT Init(CPDXGIAdapter cpAdapter);

		std::wstring GetName() const;
		UINT GetMemorySize() const;
		UINT GetNumDisplays();
		const CPDXGIAdapter GetInterface() const;
		const MnDisplayDevice GetDisplayDevice(int index) const;
		D3D_FEATURE_LEVEL GetMaxSupportedFeatureLevel() const;

	private:
		HRESULT _InitMaxSupportedFeatureLevel(CPDXGIAdapter cpAdapter);

	private:
		std::wstring		m_adapterName;
		UINT				m_videoMemorySize;
		CPDXGIAdapter		m_cpDXGIAdapter;
		DXGI_ADAPTER_DESC	m_desc;
		D3D_FEATURE_LEVEL	m_maxFeatureLevel;
		std::vector<MnDisplayDevice> m_displayDevices;
	};
}