#include "MnRenderWindow.h"
#include "Core/MnLog.h"

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
		MnLog::MB_InitFailed(MN_VAR_INFO(MnRenderWindow::m_backBufferView));
		return E_FAIL;
	}

	result = m_depthStencilBuffer.Init(cpDevice, width, height);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnRenderWindow::m_depthStencilBuffer));
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
		MnLog::MB_InitFailed(MN_VAR_INFO(m_window));
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
	MnDisplayMode closestMode = displayDevice.GetClosestMode(static_cast<UINT>(width), static_cast<UINT>(height), numerator, denominator);

	//initialize swap chain
	HRESULT result = m_swapChain.Init(closestMode, isVsync, cpD3DDevice, numBuffers, m_window.GetWindowHandle(), isWindowed);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_swapChain));
		return E_FAIL;
	}
	return S_OK;
}
const HWND MnRenderWindow::GetWindowHandle() const
{
	return m_window.GetWindowHandle();
}

void MnRenderWindow::ClearBackBuffer(MnRenderAPI& renderAPI, DirectX::SimpleMath::Color color)
{
	renderAPI.ClearRenderTargets(m_backBufferView.GetRenderTargetView(), m_depthStencilBuffer.GetDepthStencilView(), color);
}

CPD3DRenderTargetView MnRenderWindow::GetBackBufferRenderTargetView() const
{
	return m_backBufferView.GetRenderTargetView();
}
CPD3DDepthStencilView MnRenderWindow::GetBackBufferDepthStencilView() const
{
	return m_depthStencilBuffer.GetDepthStencilView();
}

D3D11_VIEWPORT MnRenderWindow::GetWindowViewport() const
{
	MnViewport viewport;
	auto wndRect = m_window.GetWindowRect();
	float width = wndRect.right - wndRect.left;
	float height = wndRect.bottom - wndRect.top;
	viewport.Init(0.0f, 0.0f, width, height);
	return viewport.GetViewport();
}

void MnRenderWindow::Resize(UINT width, UINT height)
{
	HRESULT result = m_swapChain.Resize(width, height);
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_VAR_INFO(m_swapChain.Resize));
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

HRESULT MnRenderWindow::SwapBuffers()
{
	HRESULT result = S_OK;
	if (m_swapChain.IsVsync())
	{
		result = m_swapChain.GetSwapChain()->Present(1, 0);
	}
	else
	{
		result = m_swapChain.GetSwapChain()->Present(0, 0);
	}
	return result;
}