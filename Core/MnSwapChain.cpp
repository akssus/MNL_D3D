#include "MnSwapChain.h"

using namespace MNL;

MnSwapChain::MnSwapChain():m_isVsync(false),m_numBuffers(0),m_outputWindow(0)
{
	ZeroMemory(&m_swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
}


MnSwapChain::~MnSwapChain()
{
}

HRESULT MnSwapChain::Init(
	const MnDisplayMode& displayMode,
	bool isVsync,
	const CPD3DDevice cpDevice, 
	UINT numBuffers,
	HWND hWnd,
	bool isWindowed)
{
	m_outputWindow = hWnd;
	m_isVsync = isVsync;

	CPDXGIFactory cpDXGIFactory;
	HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)cpDXGIFactory.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	
	result = _InitSwapChain(hWnd, isWindowed, numBuffers, isVsync, displayMode, cpDevice, cpDXGIFactory);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MnSwapChain::_InitSwapChain(HWND hWnd, bool isWindowed, UINT numBuffers, bool isVsync, const MnDisplayMode& displayMode, CPD3DDevice cpDevice, CPDXGIFactory cpDXGIFactory)
{
	m_numBuffers = numBuffers;

	//initialize partially specified swap chain desription
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.Windowed = isWindowed;
	swapChainDesc.BufferCount = numBuffers;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	if (isVsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = displayMode.numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = displayMode.denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDesc.BufferDesc.Width = displayMode.width;
	swapChainDesc.BufferDesc.Height = displayMode.height;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	//create actual swap chain
	HRESULT result = cpDXGIFactory->CreateSwapChain(cpDevice.Get(), &swapChainDesc, m_cpSwapChain.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	//set swap chain description
	m_swapChainDesc = swapChainDesc;

	//set m_backBuffer as swapChain's back buffer(ID3D11Texture2D)
	result = m_cpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_backBuffer.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}

HRESULT MnSwapChain::ToggleFullscreen(bool IsFullscreen)
{
	//nullptr as current swap chain
	HRESULT result = m_cpSwapChain->SetFullscreenState(IsFullscreen, nullptr);
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}
HRESULT MnSwapChain::Resize(UINT width, UINT height)
{
	m_swapChainDesc.BufferDesc.Width = width;
	m_swapChainDesc.BufferDesc.Height = height;
	HRESULT result = m_cpSwapChain->ResizeBuffers(m_numBuffers, width, height, m_swapChainDesc.BufferDesc.Format, m_swapChainDesc.Flags);

	return S_OK;
}
bool MnSwapChain::IsVsync() const
{
	return m_isVsync;
}
const CPD3DTexture2D MnSwapChain::GetBackBuffer() const
{
	return m_backBuffer;
}
const CPDXGISwapChain MnSwapChain::GetSwapChain() const
{
	return m_cpSwapChain;
}
