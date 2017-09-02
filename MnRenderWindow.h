#pragma once
#include <d3d11.h>
#include <memory>
#include "MNL.h"

namespace MNL
{
	/*
	MnRenderWindow is reponsible for window creation, modifying and swapping buffers to the screen
	*/
	class MnRenderWindow
	{
	public:
		MnRenderWindow();
		~MnRenderWindow();
		
		/*
		Create a window instance and a swap chain
		@return S_OK if successfully initialized
		*/
		HRESULT Init(
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
			const CPD3DDevice cpD3DDevice,
			const CPD3DDeviceContext cpD3DDeviceContext
		);
		
		/*
		Resize does not resize depth stencil buffer. That is not MnRednerWindow's responsibility
		*/
		const HWND GetWindowHandle() const;
		const CPD3DRenderTargetView GetBackBufferView() const;

		void Resize(UINT width, UINT height);
		void SetFullscreen();
		void SetWindowed(UINT width, UINT height);
		
		
		void ClearBuffers();
		void SwapBuffers();


	private:
		MnWindow						m_window;
		MnSwapChain						m_swapChain;
		bool							m_isWindowed;

		MnRenderTargetView				m_backBufferView;
	};
}