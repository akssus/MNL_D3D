#include <Windows.h>
#include <d3d11.h>
#include <memory>
#include "DXTK\SimpleMath.h"
#include "TestGame.h"
#include "Core/MnLog.h"

using namespace DirectX::SimpleMath;
using namespace MNL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	TestGame testGame;
	HRESULT result = testGame.Init(hInstance, WndProc, 100, 100, 1024, 768, L"TestGame");
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(testGame));
		return 0;
	}
	/**************************************************************/

	return testGame.Execute();
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