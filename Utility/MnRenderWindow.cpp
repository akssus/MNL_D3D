#include "MnRenderWindow.h"

using namespace MNL;

MnRenderWindow::MnRenderWindow():m_isWindowed(true)
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
	const MnHardware& hardwareInfo,
	bool useDefaultDevice,
	UINT numerator, UINT denominator,
	bool isVsync,
	bool isWindowed,
	UINT numBuffers,
	const CPD3DDevice cpDevice,
	const CPD3DDeviceContext cpDeviceContext)
{
	//initialize window
	HRESULT result = _InitWindow(hInstance, nCmdShow, windowName, className, x, y, width, height, WndProc);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	//initialize swap buffer
	result = _InitSwapChain(hardwareInfo, useDefaultDevice, width,height, numerator, denominator, isVsync, isWindowed, numBuffers, cpDevice, cpDeviceContext);
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
HRESULT MnRenderWindow::_InitWindow(HINSTANCE hInstance,
	int nCmdShow,
	std::wstring windowName,
	std::wstring className,
	float x, float y,
	float width, float height,
	WNDPROC WndProc)
{
	HRESULT result = m_window.Create(hInstance, nCmdShow, windowName, className, x, y, width, height, WndProc);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}
HRESULT MnRenderWindow::_InitSwapChain(const MnHardware& hardwareInfo,
	bool useDefaultDevice,
	float width, float height,
	UINT numerator, UINT denominator,
	bool isVsync,
	bool isWindowed,
	UINT numBuffers,
	const CPD3DDevice cpD3DDevice,
	const CPD3DDeviceContext cpD3DDeviceContext)
{
	//handle display devices(monitors)
	MnDisplayDevice displayDevice = hardwareInfo.GetVideoAdapter(0).GetDisplayDevice(0);
	if (!useDefaultDevice)
	{
		//deal with multiple display devices... idk for now
	}

	//get closest display mode in the supported display modes
	MnDisplayMode closestMode = displayDevice.GetClosestMode(width, height, numerator, denominator);

	//initialize swap chain
	HRESULT result = m_swapChain.Init(closestMode, isVsync, cpD3DDevice, numBuffers, m_window.GetWindowHandle(), isWindowed);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}
const HWND MnRenderWindow::GetWindowHandle() const
{
	return m_window.GetWindowHandle();
}
const CPD3DRenderTargetView& MnRenderWindow::GetBackBufferView() const
{
	return m_backBufferView.GetRenderTargetView();
}

void MnRenderWindow::Resize(UINT width, UINT height)
{
	HRESULT result = m_swapChain.Resize(width, height);
	if (FAILED(result))
	{
		//error msg
	}
}
void MnRenderWindow::SetFullscreen()
{
	m_swapChain.ToggleFullscreen(true);
}
void MnRenderWindow::SetWindowed()
{
	m_swapChain.ToggleFullscreen(false);
}

void MnRenderWindow::SwapBuffers()
{
	if (m_swapChain.IsVsync())
	{
		m_swapChain.GetSwapChain()->Present(1, 0);
	}
	else
	{
		m_swapChain.GetSwapChain()->Present(0, 0);
	}
}