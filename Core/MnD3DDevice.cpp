#include "MnD3DDevice.h"
#include "MnLog.h"

using namespace MNL;

MnD3DDevice::MnD3DDevice()
{
}


MnD3DDevice::~MnD3DDevice()
{
}

HRESULT MnD3DDevice::Init(const MnHardware& hardwareInfo, bool useDefaultAdapter)
{
	CPDXGIAdapter adapter = nullptr;
	D3D_FEATURE_LEVEL maxFeatureLevel = hardwareInfo.GetMaxSupportedFeatrueLevel(0);
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
	if (!useDefaultAdapter)
	{
		UINT numAdapters = hardwareInfo.GetNumVideoAdapters();
		//deal with multiple VGA. idk how to now
		adapter = hardwareInfo.GetVideoAdapter(0).GetInterface();
		driverType = D3D_DRIVER_TYPE_UNKNOWN;
	}
#ifdef _DEBUG
	HRESULT deviceCreated = D3D11CreateDevice(	
		adapter.Get(),
		driverType,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		&maxFeatureLevel,
		1,
		D3D11_SDK_VERSION,
		m_cpD3DDevice.ReleaseAndGetAddressOf(),
		nullptr,
		m_cpD3DDeviceContext.ReleaseAndGetAddressOf()
	);
#else
	HRESULT deviceCreated = D3D11CreateDevice(
		adapter.Get(),
		driverType,
		nullptr,
		0,
		&maxFeatureLevel,
		1,
		D3D11_SDK_VERSION,
		m_cpD3DDevice.ReleaseAndGetAddressOf(),
		nullptr,
		m_cpD3DDeviceContext.ReleaseAndGetAddressOf()
	);
#endif
	if (FAILED(deviceCreated))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnD3DDevice));
		return deviceCreated;
	}
	return S_OK;
}

CPD3DDevice MnD3DDevice::GetDevice() const
{
	return m_cpD3DDevice;
}
CPD3DDeviceContext MnD3DDevice::GetDeviceContext() const
{
	return m_cpD3DDeviceContext;
}