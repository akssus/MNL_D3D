#include <Windows.h>
#include "Window.h"
#include "D3D.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	MNL::Window window(hInstance, nCmdShow);
	if (window.Create(L"MNL_D3D", L"MNL_D3D", 100, 100, 1024, 768, WndProc) == false)
	{
		//error log
		return 0;
	}

	HWND hWnd = window.GetWindowHandle();

	MNL::D3D d3d;
	if (d3d.Init(1024, 768, hWnd, hInstance, true) == false)
	{
		return 0;
	}
	d3d.SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	MSG wndMsg;
	ZeroMemory(&wndMsg, sizeof(MSG));
	while (wndMsg.message != WM_QUIT)
	{
		if(PeekMessage(&wndMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&wndMsg);
			DispatchMessage(&wndMsg);
		}
		else
		{
			d3d.BeginScene();
			d3d.EndScene();
		}
	}


	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}
