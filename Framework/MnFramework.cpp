#include "MnFramework.h"
#include "Core/MnLog.h"

using namespace MNL;

MnRenderAPI MnFramework::renderAPI;
MnTimer MnFramework::_timer;
MnTime MnFramework::_elapsedTime;
MnDepthStencilState MnFramework::m_depthStencilStateWithDepth;
MnDepthStencilState MnFramework::m_depthStencilStateWithoutDepth;
MnBlendState MnFramework::m_blendStateWithAlpha;
MnBlendState MnFramework::m_blendStateWithoutAlpha;
bool MnFramework::_depthEnabled = true;
bool MnFramework::_alphaEnabled = true;
bool MnFramework::_fullScreenEnabled = false;
bool MnFramework::_isCCW = true;
bool MnFramework::_isVsync = true;
bool MnFramework::_stencilEnabled = true;


MnFramework::MnFramework():
	m_windowWidth(0),
	m_windowHeight(0)
{
}


MnFramework::~MnFramework()
{
}


HRESULT MnFramework::Init(HINSTANCE hInstance, WNDPROC messageHandler, float wndX, float wndY, float wndWidth, float wndHeight, const std::wstring& windowTitle)
{
	m_windowWidth = static_cast<UINT>(wndWidth);
	m_windowHeight = static_cast<UINT>(wndHeight);
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

	//뎁스 스텐실 스테이트 초기화. 디폴트로 뎁스테스트 on
	result = m_depthStencilStateWithDepth.Init(renderAPI.GetD3DDevice(), true, true);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_depthStencilStateWithDepth));
		return result;
	}
	renderAPI.SetDepthStencilState(m_depthStencilStateWithDepth.GetState());

	//뎁스테스트 off
	result = m_depthStencilStateWithoutDepth.Init(renderAPI.GetD3DDevice(), false, true);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_depthStencilStateWithoutDepth));
		return result;
	}

	//블렌드 스테이트 초기화. 디폴트로 알파 블렌딩 on
	result = m_blendStateWithAlpha.Init(renderAPI.GetD3DDevice(), true);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_blendStateWithAlpha));
		return result;
	}
	renderAPI.SetBlendState(m_blendStateWithAlpha.GetState());

	//알파 블렌딩 off
	result = m_blendStateWithoutAlpha.Init(renderAPI.GetD3DDevice(), false);
	if (FAILED(result))
	{
		MnLog::MB_InitFailed(MN_VAR_INFO(m_blendStateWithoutAlpha));
		return result;
	}
	

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

void MnFramework::SetDepthTestEnable(bool isEnable)
{
	if (isEnable)
	{
		renderAPI.SetDepthStencilState(m_depthStencilStateWithDepth.GetState());
		_depthEnabled = true;
	}
	else
	{
		renderAPI.SetDepthStencilState(m_depthStencilStateWithoutDepth.GetState());
		_depthEnabled = false;
	}
}
bool MnFramework::IsDepthTestEnabled()
{
	return _depthEnabled;
}

void MnFramework::SetAlphaBlendiingEnable(bool isEnable)
{
	if (isEnable)
	{
		renderAPI.SetBlendState(m_blendStateWithAlpha.GetState());
		_alphaEnabled = true;
	}
	else
	{
		renderAPI.SetBlendState(m_blendStateWithoutAlpha.GetState());
		_alphaEnabled = false;
	}
}
bool MnFramework::IsAlphaBlendingEnabled()
{
	return _alphaEnabled;
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

void MnFramework::SetStencilEnable(bool isEnable)
{

}
bool MnFramework::IsStencilEnable() const
{
	return false;
}

UINT MnFramework::GetWindowWidth() const
{
	return m_windowWidth;
}
UINT MnFramework::GetWindowHeight() const
{
	return m_windowHeight;
}

MnTime MnFramework::GetElapsedTime()
{
	return _elapsedTime;
}

void MnFramework::SetTimeScale(float scale)
{
	_timer.SetTimeScale(scale);
}