#include "MnFramework.h"
#include "Core/MnLog.h"

using namespace MNL;

MnRenderAPI MnFramework::renderAPI;
MnTimer MnFramework::_timer;
MnTime MnFramework::_elapsedTime;

MnFramework::MnFramework():
	m_screenWidth(0),
	m_screenHeight(0)
{
}


MnFramework::~MnFramework()
{
}


HRESULT MnFramework::Init(HINSTANCE hInstance, WNDPROC messageHandler, float wndX, float wndY, float wndWidth, float wndHeight, const std::wstring& windowTitle)
{
	m_screenWidth = static_cast<UINT>(wndWidth);
	m_screenHeight = static_cast<UINT>(wndHeight);
	_timer.Start();

	//하드웨어 초기화
	HRESULT result = m_hardware.Init();
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_hardware));
		return result;
	}

	//렌더API 초기화
	result = renderAPI.Init(m_hardware, true);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(renderAPI));
		return result;
	}

	//렌더 윈도우 초기화
	result = m_renderWindow.Init(hInstance, SW_NORMAL, windowTitle, L"MNL", wndX, wndY, wndWidth, wndHeight, messageHandler,
		m_hardware, true, 1, 60, true, true, 1, renderAPI.GetD3DDevice(), renderAPI.GetD3DDeviceContext());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_renderWindow));
		return result;
	}

	//렌더타겟 백버퍼로 바인딩
	renderAPI.SetRenderTarget(m_renderWindow.GetBackBufferRenderTargetView(), m_renderWindow.GetBackBufferDepthStencilView());

	//뎁스 스텐실 스테이트 초기화
	result = m_depthStencilState.Init(renderAPI.GetD3DDevice(), true, true);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_depthStencilState));
		return result;
	}
	renderAPI.SetDepthStencilState(m_depthStencilState.GetState());

	//샘플러 스테이트 초기화
	result = m_samplerState.Init(renderAPI.GetD3DDevice());
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_samplerState));
		return result;
	}
	renderAPI.SetSamplerState(m_samplerState.GetSamplerState());

	//래스터라이저 스테이트 초기화
	result = m_rasterizerState.Init(renderAPI.GetD3DDevice(), D3D11_FILL_SOLID, true);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(MnFramework::m_rasterizerState));
		return result;
	}
	renderAPI.SetRasterizerState(m_rasterizerState.GetState());

	//뷰포트 초기화
	renderAPI.SetViewport(m_renderWindow.GetWindowViewport());

	result = OnInit();
	if (FAILED(result))
	{
		MnLog::MB_Failed(MN_VAR_INFO(MnFramework::OnInit()));
		return result;
	}
	
	return result;
}
int MnFramework::Execute()
{
	MSG wndMsg;
	ZeroMemory(&wndMsg, sizeof(MSG));
	while (wndMsg.message != WM_QUIT)
	{
		if (PeekMessage(&wndMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&wndMsg);
			DispatchMessage(&wndMsg);
		}
		else
		{
			_elapsedTime = _timer.GetElapsedTime();
			if (OnUpdate() == false)
			{
				//루프 종료
				return 0;
			}
		}
	}
	return 0;
}

HRESULT MnFramework::OnInit()
{
	return S_OK;
}

bool MnFramework::OnUpdate()
{
	return false;
}

const MnRenderWindow& MnFramework::GetRenderWindow() const
{
	return m_renderWindow;
}

void MnFramework::ClearBackBuffer(DirectX::SimpleMath::Color color)
{
	m_renderWindow.ClearBackBuffer(renderAPI, color);
}
void MnFramework::SwapBuffers()
{
	m_renderWindow.SwapBuffers();
}

void MnFramework::SetFullScreen(bool isFullscreen)
{

}
bool MnFramework::IsFullScreen() const
{
	return false;
}

void MnFramework::SetCullMode(bool isCCW)
{

}
bool MnFramework::IsCullModeCCW() const
{
	return false;
}

void MnFramework::SetVSync(bool isVsync)
{

}
bool MnFramework::IsVSync() const
{
	return false;
}

void MnFramework::SetDepthEnable(bool isEnable)
{

}
bool MnFramework::IsDepthEnable() const
{
	return false;
}

void MnFramework::SetStencilEnable(bool isEnable)
{

}
bool MnFramework::IsStencilEnable() const
{
	return false;
}

UINT MnFramework::GetScreenWidth() const
{
	return m_screenWidth;
}
UINT MnFramework::GetScreenHeight() const
{
	return m_screenHeight;
}

MnTime MnFramework::GetElapsedTime()
{
	return _elapsedTime;
}

void MnFramework::SetTimeScale(float scale)
{
	_timer.SetTimeScale(scale);
}