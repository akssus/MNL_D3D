#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <string>
#include <vector>

namespace MNL
{
	typedef Microsoft::WRL::ComPtr<ID3D11Device>			CPD3DDevice;
	typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext>		CPD3DDeviceContext;
	typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	CPD3DRenderTargetView;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilState> CPD3DDepthStencilState;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	CPD3DDepthStencilView;
	typedef Microsoft::WRL::ComPtr<ID3D11RasterizerState>	CPD3DRasterizerState;

	typedef Microsoft::WRL::ComPtr<IDXGISwapChain>		CPDXGISwapChain;
	typedef Microsoft::WRL::ComPtr<IDXGIAdapter>		CPDXGIAdapter;
	typedef Microsoft::WRL::ComPtr<IDXGIOutput>			CPDXGIOutput;

	class D3D
	{
	private:
		struct _WindowInfo
		{
			HWND hWnd;
			UINT screenWidth;
			UINT screenHeight;
		};
		struct _DisplayMode
		{
			UINT resolutionWidth;
			UINT resolutionHeight;
			UINT refreshRateNumerator;
			UINT refreshRateDenominator;
		};
		struct _HardwareInfo
		{
			std::wstring adapterName;
			UINT videoMemorySize;
			D3D_FEATURE_LEVEL maxSupportedFeatureLevel;
			UINT numDisplayModes;
			std::vector<_DisplayMode> displayModes;
		};
		struct _ClearColor
		{
			FLOAT r, g, b, a;
		};
	public:
		D3D();
		~D3D();

		/*
		Initialize Direct3D11 device and device context
		@return false if failed to initialize
		*/
		BOOL Init(UINT screenWidth, UINT screenHeight, HWND hWnd, HINSTANCE hInstance, BOOL isWindowed);

		/*
		Destroy and release stuff
		*/
		void Destroy();

		/*
		Get device comptr pointer
		@return ComPtr of ID3D11Device
		*/
		CPD3DDevice			GetDevice();

		/*
		Get device context comptr pointer
		@return ComPtr of ID3D11DeviceContext
		*/
		CPD3DDeviceContext	GetDeviceContext();

		/*
		Set viewport to draw
		*/
		BOOL SetViewport(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom);
		void SetClearColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a);

		void EnableZBuffer();
		void DisableZBuffer();

		void BeginScene();
		void EndScene();

/**************************************************
		Initializing methods
**************************************************/
	private:
		BOOL _InitDXGI();
		BOOL _InitSwapChain();
		BOOL _InitDepthStencil();
		BOOL _InitRasterizer();
		BOOL _InitViewport(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom);

/**************************************************
		Misc flags
**************************************************/
	private:
		BOOL					m_isWindowed;
		BOOL					m_isInitialized;
/*************************************************
		Application params
**************************************************/
	private:
		_WindowInfo				m_windowInfo;
		HINSTANCE				m_hWindowInstance;
		_HardwareInfo			m_hardwareInfo;
		_DisplayMode			m_currentDisplayMode;
		_ClearColor				m_clearColor;

/**************************************************
		D3D interfaces
**************************************************/
	private:
		CPD3DDevice				m_pDevice;
		CPD3DDeviceContext		m_pDeviceContext;

		CPDXGISwapChain			m_pSwapChain;
		CPD3DRenderTargetView	m_pRenderTargetView;

		CPD3DDepthStencilState	m_pOnlyStencilState;
		CPD3DDepthStencilState	m_pDepthStencilState;
		CPD3DDepthStencilView	m_pDepthStencilView;

		CPD3DRasterizerState	m_pRasterizerState;

		CPDXGIAdapter			m_pAdapter;
		CPDXGIOutput			m_pOutput;

	};
}