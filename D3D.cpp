#include "D3D.h"
#include <wrl\client.h>
#include <memory>

using namespace MNL;
using namespace Microsoft::WRL;

D3D::D3D()
{
	ZeroMemory(&m_windowInfo, sizeof(_WindowInfo));
	ZeroMemory(&m_hardwareInfo, sizeof(_HardwareInfo));
	ZeroMemory(&m_currentDisplayMode, sizeof(_DisplayMode));
	ZeroMemory(&m_clearColor, sizeof(_ClearColor));
	m_isWindowed = true;
	m_isInitialized = false;
}


D3D::~D3D()
{
}


BOOL D3D::Init(UINT screenWidth, UINT screenHeight, HWND hWnd, HINSTANCE hInstance, BOOL isWindowed)
{
	bool result = false;
	
	//screenWidth /= 2;
	m_windowInfo.hWnd = hWnd;
	m_windowInfo.screenWidth = screenWidth;
	m_windowInfo.screenHeight = screenHeight;
	m_isWindowed = isWindowed;
	m_hWindowInstance = hInstance;

	result = _InitDXGI();
	if (!result)
	{
		return false;
	}

	result = _InitSwapChain();
	if (!result)
	{
		return false;
	}

	result = _InitDepthStencil();
	if (!result)
	{
		return false;
	}

	result = _InitRasterizer();
	if (!result)
	{
		return false;
	}
	result = _InitViewport(0.0f, 0.0f, screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	m_isInitialized = true;
	return true;
}
void D3D::Destroy()
{

}


BOOL D3D::_InitDXGI()
{
	HRESULT result;
	
	_HardwareInfo hardwareInfo;
	ZeroMemory(&hardwareInfo, sizeof(_HardwareInfo));

	//create 
	ComPtr<IDXGIFactory> pFactory;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(result))
	{
		//error log
		return false;
	}

	ComPtr<IDXGIAdapter> pAdapter;
	result = pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(result))
	{
		//error log
		return false;
	}

	ComPtr<IDXGIOutput> pOutput;
	result = pAdapter->EnumOutputs(0, &pOutput);
	if (FAILED(result))
	{
		//error log
		return false;
	}

	//find how many display modes(monitor mode) are available
	UINT numMonitors= 0;
	result = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numMonitors, nullptr);
	if (FAILED(result))
	{
		//error log
		return false;
	}
	//get descriptions of display modes
	DXGI_MODE_DESC* displayModeDescs = new DXGI_MODE_DESC[numMonitors];
	result = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numMonitors, displayModeDescs);
	if (FAILED(result))
	{
		//error log
		return false;
	}
	//add display mode informations
	hardwareInfo.numDisplayModes = numMonitors;
	hardwareInfo.displayModes.resize(numMonitors);
	for (int i=0;i<numMonitors;++i)
	{
		_DisplayMode& displayMode = hardwareInfo.displayModes[i];
		DXGI_MODE_DESC displayModeDesc = displayModeDescs[i];
		displayMode.refreshRateNumerator = displayModeDesc.RefreshRate.Numerator;
		displayMode.refreshRateDenominator = displayModeDesc.RefreshRate.Denominator;
		displayMode.resolutionWidth = displayModeDesc.Width;
		displayMode.resolutionHeight = displayModeDesc.Height;

		//find currently being used display mode
		if (m_windowInfo.screenWidth == displayModeDesc.Width &&
			m_windowInfo.screenHeight == displayModeDesc.Height)
		{
			m_currentDisplayMode = displayMode;
		}
	}
	delete[] displayModeDescs;
	

	//get adapter(VGA) information
	DXGI_ADAPTER_DESC VGADesc;
	result = pAdapter->GetDesc(&VGADesc);
	if (FAILED(result))
	{
		//error log
		return false;
	}

	hardwareInfo.videoMemorySize = VGADesc.DedicatedVideoMemory / 1024 / 1024; //byte to MB
	hardwareInfo.adapterName = VGADesc.Description;

	//confirm hardware information
	m_hardwareInfo = hardwareInfo;

	m_pAdapter = pAdapter;
	m_pOutput = pOutput;

	return true;
}
BOOL D3D::_InitSwapChain()
{
	HRESULT result = E_FAIL;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = m_windowInfo.screenWidth;
	swapChainDesc.BufferDesc.Height = m_windowInfo.screenHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = m_currentDisplayMode.refreshRateNumerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = m_currentDisplayMode.refreshRateDenominator;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Flags = 0;
	swapChainDesc.OutputWindow = m_windowInfo.hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = m_isWindowed;

	//get max surported feature level
	D3D_FEATURE_LEVEL maxSupportedFeatureLevel = D3D_FEATURE_LEVEL_9_1;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 6, D3D11_SDK_VERSION, nullptr, &maxSupportedFeatureLevel, nullptr);
	if (FAILED(result))
	{
		return false;
	}
	m_hardwareInfo.maxSupportedFeatureLevel = maxSupportedFeatureLevel;

	//create device and swapChain
	result = D3D11CreateDeviceAndSwapChain(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 
		0, 
		&maxSupportedFeatureLevel, 
		1, 
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&m_pSwapChain, 
		&m_pDevice,
		nullptr,
		&m_pDeviceContext
	);
	if (FAILED(result))
	{
		return false;
	}

	//create back buffer
	ComPtr<ID3D11Texture2D> backBuffer;
	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//create render target view
	result = m_pDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_pRenderTargetView);
	if (FAILED(result))
	{
		return false;
	}
	//set render target view
	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), nullptr);

	return true;
}
BOOL D3D::_InitDepthStencil()
{
	HRESULT result = E_FAIL;

	//set depth stencil buffer desciption
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
	ZeroMemory(&depthStencilBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilBufferDesc.Width = m_windowInfo.screenWidth;
	depthStencilBufferDesc.Height = m_windowInfo.screenHeight;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.MiscFlags = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;

	//create texture2D for depth stencil buffer
	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	result = m_pDevice->CreateTexture2D(&depthStencilBufferDesc, nullptr, &depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//set depth stencil test parameters
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	//create depth stencil state
	result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
	if (FAILED(result))
	{
		return false;
	}
	//set depth stencil state to out merger
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);

	//set stencil test without z buffer parameters
	D3D11_DEPTH_STENCIL_DESC onlyStencilDesc;
	ZeroMemory(&onlyStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	onlyStencilDesc.DepthEnable = false;
	onlyStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	onlyStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	onlyStencilDesc.StencilEnable = true;
	onlyStencilDesc.StencilReadMask = 0xFF;
	onlyStencilDesc.StencilWriteMask = 0xFF;

	onlyStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	onlyStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	onlyStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	onlyStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	onlyStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	onlyStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	onlyStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	onlyStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	onlyStencilDesc.StencilEnable = true;
	onlyStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	onlyStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	//create depth stencil state
	result = m_pDevice->CreateDepthStencilState(&onlyStencilDesc, &m_pOnlyStencilState);
	if (FAILED(result))
	{
		return false;
	}

	//set depth stencil view description
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	depthStencilViewDesc.Flags = 0;
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_pDevice->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(result))
	{
		return false;
	}

	//set depth stencil view to out merger
	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());

	return true;
}
BOOL D3D::_InitRasterizer()
{
	HRESULT result = E_FAIL;

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0;

	//create rasterizer state
	result = m_pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
	if (FAILED(result))
	{
		return false;
	}

	//set rasterizer state
	m_pDeviceContext->RSSetState(m_pRasterizerState.Get());

	return true;
}
BOOL D3D::_InitViewport(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom)
{
	if (left > right || top > bottom)
	{
		return false;
	}
	FLOAT width = right - left;
	FLOAT height = bottom - top;
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = width;
	viewport.Height = height;
	viewport.TopLeftX = left;
	viewport.TopLeftY = top;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pDeviceContext->RSSetViewports(1, &viewport);

	return true;
}

CPD3DDevice	D3D::GetDevice()
{
	return m_pDevice;
}
CPD3DDeviceContext D3D::GetDeviceContext()
{
	return m_pDeviceContext;
}
BOOL D3D::SetViewport(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom)
{
	return _InitViewport(left, top, right, bottom);
}
void D3D::SetClearColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	m_clearColor.r = r;
	m_clearColor.g = g;
	m_clearColor.b = b;
	m_clearColor.a = a;
}
void D3D::EnableZBuffer()
{
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);
}
void D3D::DisableZBuffer()
{
	m_pDeviceContext->OMSetDepthStencilState(m_pOnlyStencilState.Get(), 1);
}

void D3D::BeginScene()
{
	FLOAT clearColor[4] = { 
		m_clearColor.r,
		m_clearColor.g,
		m_clearColor.b,
		m_clearColor.a
	};
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void D3D::EndScene()
{
	m_pSwapChain->Present(1, 0);
}