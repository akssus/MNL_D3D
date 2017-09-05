#include <Windows.h>
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core\MNL_Core.h"
#include "Utility\MNL_Utility.h"

using namespace DirectX::SimpleMath;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	//initialize
	MNL::MnHardware hardware;
	HRESULT result = hardware.Init();
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	MNL::MnRenderAPI renderAPI;
	result = renderAPI.Init(hardware, true);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	MNL::MnRenderWindow renderWindow;
	result = renderWindow.Init(hInstance, nCmdShow, L"MNL", L"MNL", 100, 100, 1024, 768, WndProc,
		hardware, true, 1, 60, false, true, 1, renderAPI.GetD3DDevice()->GetDevice(), renderAPI.GetD3DDevice()->GetDeviceContext());
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	//init depth stencil buffer
	MNL::MnDepthStencilBuffer depthStencilBuffer;
	result = depthStencilBuffer.Init(renderAPI.GetD3DDevice()->GetDevice(), 1024, 768);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetRenderTarget(renderWindow.GetBackBufferView(), depthStencilBuffer.GetDepthStencilView());

	//init depth stencil state
	MNL::MnDepthStencilState depthStencilState;
	result = depthStencilState.Init(renderAPI.GetD3DDevice()->GetDevice(), true, true);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetDepthStencilState(depthStencilState.GetState());

	//init rasterizer state
	MNL::MnRasterizerState rasterizerState;
	result = rasterizerState.Init(renderAPI.GetD3DDevice()->GetDevice(), D3D11_FILL_SOLID, false);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetRasterizerState(rasterizerState.GetState());

	//init viewport
	MNL::MnViewport viewport;
	result = viewport.Init(0, 0, 1024, 768);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetViewport(viewport.GetViewport());

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
			renderAPI.ClearRenderTargets(renderWindow.GetBackBufferView(), depthStencilBuffer.GetDepthStencilView(), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			//render here
			renderWindow.SwapBuffers();
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
