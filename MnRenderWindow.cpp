#include "MnRenderWindow.h"

using namespace MNL;

MnRenderWindow::MnRenderWindow()
{
}


MnRenderWindow::~MnRenderWindow()
{
}

HRESULT MnRenderWindow::Init(
	HINSTANCE hInstance,
	int nCmdShow,
	std::wstring windowName,
	std::wstring className,
	float x, float y,
	float width, float height,
	WNDPROC WndProc,
	bool isWindowed,
	const MnHardware& hardwareInfo,
	bool useDefaultDevice,
	UINT numerator, UINT denominator,
	bool isVsync,
	UINT numBuffers,
	const CPD3DDevice cpDevice,
	const CPD3DDeviceContext cpDeviceContext)
{
	//initialize window
	HRESULT result = m_window.Create(hInstance, nCmdShow, windowName, className, x, y, width, height, WndProc);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	//create instances
	//m_pSwapChain = std::make_shared<MnSwapChain>();
	
	//handle display devices(monitors)
	MnDisplayDevice displayDevice = hardwareInfo.GetDisplayDevice(0);
	if (useDefaultDevice)
	{
		UINT numDisplayDevices = hardwareInfo.GetNumDisplayDevices();
		for (int i = 0; i < numDisplayDevices; ++i)
		{
			//deal with multiple display devices... idk for now
		}
	}

	//get closest display mode in the supported display modes
	MnDisplayMode closestMode = displayDevice.GetClosestdMode(width, height, numerator, denominator);
	
	//initialize swap chain
	result = m_swapChain.Init(closestMode, isVsync, cpDevice, numBuffers, m_window.GetWindowHandle(), isWindowed);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	//create back buffer render target view
	CPD3DTexture2D cpBackBuffer = m_swapChain.GetBackBuffer();

	result = m_backBufferView.Init(cpDevice, cpBackBuffer, nullptr);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}

	return S_OK;
}