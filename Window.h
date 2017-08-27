#pragma once


#include <Windows.h>
#include <string>
#include <functional>

namespace MNL
{
	class Window
	{
	public:
		Window(HINSTANCE hInstance, int nCmdShow);
		~Window();

		bool	Create(std::wstring windowName, std::wstring className, 
					 float x,		float y, 
					 float width,	float height, 
					 WNDPROC WndProc);
		void	Destroy();

		HWND&	GetWindowHandle();
		RECT	GetWindowRect();

	private:
		HWND		m_hWnd;
		WNDCLASS	m_wndClass;
		HINSTANCE	m_hInstance;
		int			m_cmdShow;
	};
}