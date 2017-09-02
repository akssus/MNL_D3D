#pragma once
#include <d3d11.h>
#include "MNL.h"

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
		const MnDisplayDevice GetDisplay(int index);

	private:
		std::wstring		m_adapterName;
		UINT				m_videoMemorySize;
		CPDXGIAdapter		m_cpDXGIAdapter;
		DXGI_ADAPTER_DESC	m_desc;
		std::vector<MnDisplayDevice> m_displayDevices;
	};
}