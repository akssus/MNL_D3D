#include "MnHardware.h"
#include "MnLog.h"
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
			MnLog::MB_InitFailed(MN_VAR_INFO(EnumAdapters));
			return enumResult;
		}
		//create video adapter instance
		MnVideoAdapter videoAdapter;
		result = videoAdapter.Init(cpAdapter);
		if (FAILED(result))
		{
			MnLog::MB_InitFailed(MN_VAR_INFO(MnVideoAdapter));
			return result;
		}
		//add to video adapter list
		m_videoAdapters.push_back(videoAdapter);
		adapterIndex++;
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

D3D_FEATURE_LEVEL MnHardware::GetMaxSupportedFeatrueLevel(UINT adapterIndex) const
{
	return m_videoAdapters[adapterIndex].GetMaxSupportedFeatureLevel();
}