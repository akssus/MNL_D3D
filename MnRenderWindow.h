#pragma once
#include <d3d11.h>
#include <memory>
#include "Window.h"
#include "MNL.h"

namespace MNL
{
	class MnRenderWindow
	{
	public:
		MnRenderWindow();
		~MnRenderWindow();
		
		void Init(	HINSTANCE hInstance, int nCmdShow,
					std::wstring windowName, std::wstring className,
					float x, float y,
					float width, float height,
					WNDPROC WndProc);
		
		void Resize(UINT width, UINT height);
		void SetFullscreen();
		void SetWindowed(UINT width, UINT height);
		
		
		void ClearBuffers();
		void SwapBuffers();


	private:
		Window							m_window;
		std::shared_ptr<MnD3DDevice>	m_pD3DDevice;
		CPDXGISwapChain					m_cpSwapChain;

		bool			m_isWindowed;
	};
}