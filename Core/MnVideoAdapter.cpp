#include "MnVideoAdapter.h"
#include "MnLog.h"

using namespace MNL;

MnVideoAdapter::MnVideoAdapter():m_maxFeatureLevel(D3D_FEATURE_LEVEL_9_1),m_videoMemorySize(0)
{
	ZeroMemory(&m_desc, sizeof(DXGI_ADAPTER_DESC));
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
			MnLog::MB_InitFailed(MN_VAR_INFO(EnumOutputs));
			return enumResult;
		}
		//create display instance
		MnDisplayDevice displayDevice;
		result = displayDevice.Init(cpDisplay);
		if (FAILED(result))
		{
			MnLog::MB_InitFailed(MN_VAR_INFO(MnDisplayDevice));
			return result;
		}
		//add to display list
		m_displayDevices.push_back(displayDevice);
		index++;
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

	//get max supported GPU feature level
	result = _InitMaxSupportedFeatureLevel(cpAdapter);
	if (FAILED(result))
	{
		//warning log
	}

	return S_OK;
}

HRESULT MnVideoAdapter::_InitMaxSupportedFeatureLevel(CPDXGIAdapter cpAdapter)
{
	D3D_FEATURE_LEVEL maxSupportedFeatureLevel = D3D_FEATURE_LEVEL_9_1;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	HRESULT result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 6, D3D11_SDK_VERSION, nullptr, &maxSupportedFeatureLevel, nullptr);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(D3D11CreateDevice));
		return result;
	}
	m_maxFeatureLevel = maxSupportedFeatureLevel;
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

D3D_FEATURE_LEVEL MnVideoAdapter::GetMaxSupportedFeatureLevel() const
{
	return m_maxFeatureLevel;
}