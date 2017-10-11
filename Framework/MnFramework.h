/**
@class MnFramework
@brief 윈도우 생성과 D3D 장치 생성, 게임 루프를 실행한다.
@author Akssus
@section 개요
MNL 클래스들의 실제 인스턴싱과 초기화 과정을 처리한다. \n
또한 게임 루프를 가상함수로 제공하며 MnFramework 를 상속하여 실질적인 구현이 가능하다. \n
MNL 코어 객체들은 private으로 숨겨져 있으며, 프레임워크를 구체화 하는 사용자는 프레임워크가 제공하는 인터페이스만 사용 가능하다.\n
\n
Framework 수준의 객체들은 MnFramework에 상당히 의존적이며, MnFramework는 초기화 이후 게임 흐름에 관한 대부분의 기능을 제공한다. \n
또한 초기화가 되었다는 전제 하에 D3D 장치와 MnRenderAPI 에 대한 정적 참조를 제공한다.
*/

#pragma once
#include <d3d11.h>
#include "Core/MnTypedefs.h"
#include "Core/MnHardware.h"
#include "Core/MnRenderAPI.h"
#include "Core/MnDepthStencilState.h"
#include "Core/MnRasterizerState.h"
#include "Render/MnRenderWindow.h"
#include "Render/MnRenderer.h"
#include "Render/MnMesh.h"

namespace MNL
{
	class MnFramework
	{
	public:
		MnFramework();
		virtual ~MnFramework();

		/**
		@brief 프레임워크를 초기화하고 윈도우를 생성한다.
		@param hInstance Win32 프로그램 모듈 핸들
		@param messageHandler Win32 메시지 처리 콜백 함수
		@return 초기화 성공 여부
		*/
		virtual HRESULT Init(HINSTANCE hInstance, WNDPROC messageHandler, float wndX, float wndY, float wndWidth, float wndHeight, const std::wstring& windowTitle);

		/**
		@brief 게임 루프를 실행한다. 완전 가상 함수로서 반드시 상속해서 구현한다. 
		@return 루프 종료시 0을 반환해야 하며 이때 프로그램을 종료해야 한다.
		*/
		virtual int Execute();

		/**
		@brief 최초 초기화 시 호출되는 콜백함수
		@return 동작 성공시 S_OK 반환
		*/
		virtual HRESULT OnInit();

		/**
		@brief Execute 루프시 반복 실행되는 콜백함수.
		@return 종료시 false 반환
		*/
		virtual bool OnUpdate();

	protected:
		/**
		@brief 백버퍼를 초기화한다.
		@param color 백버퍼의 초기화 될 색상
		*/
		void ClearBackBuffer(DirectX::SimpleMath::Color color = { 0.0f,0.0f,0.0f,0.0f });

		/**
		@brief 백버퍼를 프론트버퍼로 스왑하여 화면에 출력한다.
		*/
		void SwapBuffers();

		/**
		@brief 해당 렌더러의 설정으로 파이프라인의 설정을 바꾼다.
		*/
		void SetRenderer(const std::shared_ptr<MnRenderer>& spRenderer);

		/**
		@brief 해당 렌더러로 메쉬를 렌더링한다.
		@param spRenderer 메쉬를 렌더링할 렌더러
		@param mesh 렌더링 대상
		@return 렌더 성공시 S_OK 반환
		*/
		HRESULT RenderMesh(const std::shared_ptr<MnRenderer>& spRenderer, const std::shared_ptr<MnMesh>& mesh);

		void SetRenderTarget(const CPD3DRenderTargetView& cpRenderTargetView);
		CPD3DRenderTargetView GetBackBufferRenderTargetView() const;

		void SetFullScreen(bool isFullscreen);
		bool IsFullScreen() const;

		void SetCullMode(bool isCCW);
		bool IsCullModeCCW() const;

		void SetVSync(bool isVsync);
		bool IsVSync() const;

		void SetDepthEnable(bool isEnable);
		bool IsDepthEnable() const;

		void SetStencilEnable(bool isEnable);
		bool IsStencilEnable() const;

		UINT GetScreenWidth() const;
		UINT GetScreenHeight() const;

	public:
		/**
		@brief D3D장치에 대한 접근 및 파이프라인 설정에 관한 API를 제공하는 객체로서 static으로 선언해 렌더 API에 대한 전역참조를 허용한다.
		*/
		static MnRenderAPI renderAPI;

	protected:
		UINT m_screenWidth; ///< 윈도우의 넓이
		UINT m_screenHeight; ///< 윈도우의 높이

	private:
		MnHardware m_hardware; ///< VGA 및 모니터에 대한 정보를 담은 객체
		MnRenderWindow m_renderWindow; ///< 백버퍼 정보와 렌더링 될 윈도우의 정보를 지닌 객체
		MnDepthStencilState m_depthStencilState; ///< 뎁스 스텐실 상태 정보를 담은 객체
		MnRasterizerState m_rasterizerState; ///< 래스터라이저 상태 정보를 담은 객체
		MnViewport m_viewport; //임시
	};
}
