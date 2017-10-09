#pragma once
#include <d3d11.h>
#include <string>
#include <memory>
#include "Core\MnTypedefs.h"
#include "Core\MnHardware.h"
#include "Core\MnRenderTargetView.h"
#include "Core\MnSwapChain.h"
#include "Core\MnWindow.h"
#include "Core\MnRenderAPI.h"
#include "Core\MnViewport.h"
#include "Core\MnDepthStencilBuffer.h"


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
			const MnHardware& hardwareInfo,
			bool useDefaultDevice,
			UINT numerator, UINT denominator,
			bool isVsync,
			bool isWindowed,
			UINT numBuffers,
			const CPD3DDevice cpD3DDevice,
			const CPD3DDeviceContext cpD3DDeviceContext
		);
		
		/*
		Resize does not resize depth stencil buffer. That is not MnRednerWindow's responsibility
		*/
		const HWND GetWindowHandle() const;

		/**
		@brief 백버퍼의 렌더타겟버퍼와 뎁스스텐실버퍼를 클리어한다.
		*/
		void ClearBackBuffer(MnRenderAPI& renderAPI, DirectX::SimpleMath::Color color = { 0.0f,0.0f,0.0f,0.0f });

		/**
		@brief 백버퍼의 렌더타겟뷰를 반환한다.
		*/
		CPD3DRenderTargetView GetBackBufferRenderTargetView() const;

		/**
		@brief 백버퍼의 뎁스스텐실뷰를 반환한다.
		*/
		CPD3DDepthStencilView GetBackBufferDepthStencilView() const;

		/**
		@brief 현재 윈도우의 전체 화면에 해당하는 뷰포트를 반환한다.
		*/
		D3D11_VIEWPORT GetWindowViewport() const;

		void Resize(UINT width, UINT height);
		void SetFullscreen();
		void SetWindowed();
		
		/*
		@return DXGI_ERROR_DEVICE_REMOVED or DXGI_ERROR_DEVICE_RESET if device lost event happen
		*/
		HRESULT SwapBuffers();

	private:
		HRESULT _InitWindow(HINSTANCE hInstance,
			int nCmdShow,
			std::wstring windowName,
			std::wstring className,
			float x, float y,
			float width, float height,
			WNDPROC WndProc);
		HRESULT _InitSwapChain(const MnHardware& hardwareInfo,
			bool useDefaultDevice,
			float width, float height,
			UINT numerator, UINT denominator,
			bool isVsync,
			bool isWindowed,
			UINT numBuffers,
			const CPD3DDevice cpD3DDevice,
			const CPD3DDeviceContext cpD3DDeviceContext);

	private:
		MnWindow m_window;
		MnSwapChain	m_swapChain;
		bool m_isWindowed;

		MnRenderTargetView	m_backBufferView;
		MnDepthStencilBuffer m_depthStencilBuffer;
	};
}