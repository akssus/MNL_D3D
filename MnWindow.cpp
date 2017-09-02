#include "MnWindow.h"

using namespace MNL;

MnWindow::MnWindow()
{
	m_hInstance = 0;
	m_cmdShow = 0;
	m_hWnd = 0;
}

MnWindow::~MnWindow()
{
	Shutdown();
};

HRESULT MnWindow::Create(HINSTANCE hInstance, int nCmdShow, std::wstring windowName, std::wstring className, float x, float y, float width, float height, WNDPROC WndProc)
{
	m_hInstance = hInstance;
	m_cmdShow = nCmdShow;

	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc = WndProc;
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.hInstance = m_hInstance;
	m_wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wndClass.lpszMenuName = NULL;
	m_wndClass.lpszClassName = className.c_str();
	if (!RegisterClass(&m_wndClass))
	{
		return E_FAIL;
	}

	m_hWnd = CreateWindow(className.c_str(), windowName.c_str(), WS_OVERLAPPEDWINDOW,
		x, y, width, height,
		NULL, NULL, m_hInstance, NULL);
	ShowWindow(m_hWnd, m_cmdShow);

	return S_OK;
}

void MnWindow::Shutdown()
{

}

HWND& MnWindow::GetWindowHandle()
{
	return m_hWnd;
}

RECT MnWindow::GetWindowRect()
{
	RECT windowRect;
	GetClientRect(m_hWnd, &windowRect);
	return windowRect;
}