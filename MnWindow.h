#pragma once

#include <Windows.h>
#include <string>
#include <functional>

namespace MNL
{
	class MnWindow
	{
	public:
		MnWindow();
		~MnWindow();

		HRESULT	Create(HINSTANCE hInstance, int nCmdShow, 
					 std::wstring windowName, std::wstring className,
					 float x,		float y, 
					 float width,	float height, 
					 WNDPROC WndProc);
		void	Shutdown();

		const HWND	GetWindowHandle() const;
		RECT	GetWindowRect() const;

	private:
		HWND		m_hWnd;
		WNDCLASS	m_wndClass;
		HINSTANCE	m_hInstance;
		int			m_cmdShow;
	};
}