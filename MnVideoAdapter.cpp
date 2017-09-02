#include "MnVideoAdapter.h"

using namespace MNL;

MnVideoAdapter::MnVideoAdapter()
{
}


MnVideoAdapter::~MnVideoAdapter()
{
}


HRESULT MnVideoAdapter::Init(CPDXGIAdapter cpAdapter)
{
	m_cpDXGIAdapter = cpAdapter;
	
	HRESULT result = E_FAIL;
	//search available displays
	UINT index = 0;
	while (1)
	{
		CPDXGIOutput cpDisplay;
		HRESULT enumResult = cpAdapter->EnumOutputs(index, cpDisplay.ReleaseAndGetAddressOf());
		//if no more adapters then quit loop
		if (enumResult == DXGI_ERROR_NOT_FOUND)
		{
			break;
		}
		else if (FAILED(enumResult))
		{
			//error log
			return E_FAIL;
		}
		//create display instance
		MnDisplayDevice displayDevice;
		result = displayDevice.Init(cpDisplay);
		if (FAILED(result))
		{
			//error log
			return E_FAIL;
		}
		
		result = cpAdapter->GetDesc(&m_desc);
		if (FAILED(result))
		{
			//warning log
		}
		//get adapter name
		m_adapterName = m_desc.Description;
		//get video memory size as MB
		m_videoMemorySize = m_desc.DedicatedVideoMemory / 1024 / 1024;
		//add to display list
		m_displayDevices.push_back(displayDevice);
	}

	return S_OK;
}

std::wstring MnVideoAdapter::GetName() const
{
	return m_adapterName;
}
UINT MnVideoAdapter::GetMemorySize() const
{
	return m_videoMemorySize;
}
UINT MnVideoAdapter::GetNumDisplays()
{
	return m_displayDevices.size();
}
const CPDXGIAdapter MnVideoAdapter::GetInterface() const
{
	return m_cpDXGIAdapter;
}
const MnDisplayDevice MnVideoAdapter::GetDisplayDevice(int index) const
{
	return m_displayDevices[index];
}