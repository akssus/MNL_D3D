#include "MnSwapChain.h"

using namespace MNL;

MnSwapChain::MnSwapChain()
{
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
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.Windowed = isWindowed;
	swapChainDesc.BufferCount = numBuffers;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 0;
	swapChainDesc.SampleDesc.Quality = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
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
	swapChainDesc.BufferDesc.Height = displayMode.width;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	HRESULT result = cpDXGIFactory->CreateSwapChain(cpDevice.Get(), &swapChainDesc, m_cpSwapChain.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	m_swapChainDesc = swapChainDesc;

	HRESULT result = m_cpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_backBuffer.ReleaseAndGetAddressOf());
	if (FAILED(result))
	{
		//error log
		return E_FAIL;
	}
	return S_OK;
}

CPD3DTexture2D MnSwapChain::GetBackBuffer()
{
	return m_backBuffer;
}
