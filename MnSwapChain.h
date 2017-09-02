#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	/*
	MnSwapChain is dependent to MnRenderWindow
	*/
	class MnSwapChain
	{
	public:
		MnSwapChain();
		~MnSwapChain();

		HRESULT Init(const MnDisplayMode& displayMode,
			bool isVsync,
			const CPD3DDevice cpDevice,
			UINT numBuffers,
			HWND hWnd,
			bool isWindowed);

		/*
		Set swap chain's fullscreen state
		@param true as fullscreen mode, false as windowed 
		*/
		HRESULT ToggleFullscreen(bool IsFullscreen);
		HRESULT Resize(UINT width, UINT height);

		bool IsVsync() const;
		const CPD3DTexture2D GetBackBuffer() const;
		const CPDXGISwapChain GetSwapChain() const;

	private:
		HRESULT _InitSwapChain(HWND hWnd, 
			bool isWindowed, 
			UINT numBuffers, 
			bool isVsync, 
			const MnDisplayMode& displayMode, 
			CPD3DDevice cpDevice, 
			CPDXGIFactory cpDXGIFactory);


	private:
		HWND m_outputWindow;
		bool m_isVsync;
		UINT m_numBuffers;
		DXGI_SWAP_CHAIN_DESC m_swapChainDesc;
		CPDXGISwapChain m_cpSwapChain;
		CPD3DTexture2D m_backBuffer;
	};
}