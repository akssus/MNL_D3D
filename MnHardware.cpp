#include "MnHardware.h"
#include <memory>

using namespace MNL;

MnHardware::MnHardware()
{
}


MnHardware::~MnHardware()
{
}
HRESULT	 MnHardware::Init()
{
	CPDXGIFactory cpFactory;
	HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)cpFactory.ReleaseAndGetAddressOf());

	//search available video adapters
	UINT adapterIndex = 0;
	while (1)
	{
		CPDXGIAdapter cpAdapter;
		HRESULT enumResult = cpFactory->EnumAdapters(adapterIndex, cpAdapter.ReleaseAndGetAddressOf());
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
		//create video adapter instance
		MnVideoAdapter videoAdapter;
		result = videoAdapter.Init(cpAdapter);
		if (FAILED(result))
		{
			//error log
			return E_FAIL;
		}
		//add to video adapter list
		m_videoAdapters.push_back(videoAdapter);
	}
	

	return S_OK;
}

UINT MnHardware::GetNumVideoAdapters() const
{
	return m_videoAdapters.size();
}
const MnVideoAdapter MnHardware::GetVideoAdapter(UINT index) const
{
	return m_videoAdapters[index];
}

D3D_FEATURE_LEVEL MnHardware::GetMaxSupportedFeatrueLevel() const
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
		//error log
	}

	return maxSupportedFeatureLevel;
}