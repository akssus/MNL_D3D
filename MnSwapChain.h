#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
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

		CPD3DTexture2D GetBackBuffer();

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
		DXGI_SWAP_CHAIN_DESC m_swapChainDesc;
		CPDXGISwapChain m_cpSwapChain;
		CPD3DTexture2D m_backBuffer;
	};
}