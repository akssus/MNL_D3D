/**
@class MnFramework
@brief ������ ������ D3D ��ġ ����, ���� ������ �����Ѵ�.
@author Akssus
@section ����
MNL Ŭ�������� ���� �ν��Ͻ̰� �ʱ�ȭ ������ ó���Ѵ�. \n
���� ���� ������ �����Լ��� �����ϸ� MnFramework �� ����Ͽ� �������� ������ �����ϴ�. \n
MNL �ھ� ��ü���� private���� ������ ������, �����ӿ�ũ�� ��üȭ �ϴ� ����ڴ� �����ӿ�ũ�� �����ϴ� �������̽��� ��� �����ϴ�.\n
\n
Framework ������ ��ü���� MnFramework�� ����� �������̸�, MnFramework�� �ʱ�ȭ ���� ���� �帧�� ���� ��κ��� ����� �����Ѵ�. \n
���� �ʱ�ȭ�� �Ǿ��ٴ� ���� �Ͽ� D3D ��ġ�� MnRenderAPI �� ���� ���� ������ �����Ѵ�.
*/

#pragma once
#include <d3d11.h>
#include "Core/MnTypedefs.h"
#include "Core/MnHardware.h"
#include "Core/MnRenderAPI.h"
#include "Core/MnDepthStencilState.h"
#include "Core/MnRasterizerState.h"
#include "Core\MnBlendState.h"
#include "Render/MnRenderWindow.h"
#include "Render/MnRenderer.h"
#include "Render/MnMesh.h"
#include "Utility\MnTimer.h"

namespace MNL
{
	class MnFramework
	{
	public:
		MnFramework();
		virtual ~MnFramework();

		/**
		@brief �����ӿ�ũ�� �ʱ�ȭ�ϰ� �����츦 �����Ѵ�.
		@param hInstance Win32 ���α׷� ��� �ڵ�
		@param messageHandler Win32 �޽��� ó�� �ݹ� �Լ�
		@return �ʱ�ȭ ���� ����
		*/
		virtual HRESULT Init(HINSTANCE hInstance, WNDPROC messageHandler, float wndX, float wndY, float wndWidth, float wndHeight, const std::wstring& windowTitle);

		/**
		@brief ���� ������ �����Ѵ�. ���� ���� �Լ��μ� �ݵ�� ����ؼ� �����Ѵ�. 
		@return ���� ����� 0�� ��ȯ�ؾ� �ϸ� �̶� ���α׷��� �����ؾ� �Ѵ�.
		*/
		virtual int Execute();

		/**
		@brief ���� �ʱ�ȭ �� ȣ��Ǵ� �ݹ��Լ�
		@return ���� ������ S_OK ��ȯ
		*/
		virtual HRESULT OnInit();

		/**
		@brief Execute ������ �ݺ� ����Ǵ� �ݹ��Լ�.
		@return ����� false ��ȯ
		*/
		virtual bool OnUpdate();
		

	protected:

		const MnRenderWindow& GetRenderWindow() const;

		/**
		@brief ����۸� �ʱ�ȭ�Ѵ�.
		@param color ������� �ʱ�ȭ �� ����
		*/
		void ClearBackBuffer(DirectX::SimpleMath::Color color = { 0.0f,0.0f,0.0f,0.0f });

		/**
		@brief ����۸� ����Ʈ���۷� �����Ͽ� ȭ�鿡 ����Ѵ�.
		*/
		void SwapBuffers();

		//-------- ���� ��ü �� �޼ҵ�
	public:
		/**
		@brief D3D��ġ�� ���� ���� �� ���������� ������ ���� API�� �����ϴ� ��ü�μ� static���� ������ ���� API�� ���� ���������� ����Ѵ�.
		*/
		static MnRenderAPI renderAPI;

		/**
		@brief ���� �׽�Ʈ ���� ���θ� �����Ѵ�.
		*/
		static void SetDepthTestEnable(bool isEnable);
		static bool IsDepthTestEnabled();

		static void SetAlphaBlendiingEnable(bool isEnable);
		static bool IsAlphaBlendingEnabled();

		void SetFullScreen(bool isFullscreen);
		bool IsFullScreen() const;

		void SetCullMode(bool isCCW);
		bool IsCullModeCCW() const;

		void SetVSync(bool isVsync);
		bool IsVSync() const;

		void SetStencilEnable(bool isEnable);
		bool IsStencilEnable() const;

		UINT GetWindowWidth() const;
		UINT GetWindowHeight() const;

		/**
		@brief Ÿ�� �������� �����Ѵ�.
		*/
		static void SetTimeScale(float scale);

		/**
		@brief �� ������Ʈ�� �� ������Ʈ�� �ð����� ��ȯ�Ѵ�.
		*/
		static MnTime GetElapsedTime();

	private:
		static bool _depthEnabled;
		static bool _stencilEnabled;
		static bool _alphaEnabled;
		static bool _fullScreenEnabled;
		static bool _isCCW;
		static bool _isVsync;

	protected:
		UINT m_windowWidth; ///< �������� ����
		UINT m_windowHeight; ///< �������� ����

	private:
		MnHardware m_hardware; ///< VGA �� ����Ϳ� ���� ������ ���� ��ü
		MnRenderWindow m_renderWindow; ///< ����� ������ ������ �� �������� ������ ���� ��ü
		MnSamplerState m_samplerState; ///< �ؽ��� ���ø� ������ ���� ��ü
		MnRasterizerState m_rasterizerState; ///< �����Ͷ����� ���� ������ ���� ��ü
		MnViewport m_viewport; //�ӽ�

		static MnDepthStencilState m_depthStencilStateWithDepth; ///< ���� ���ٽ� ���� ������ ���� ��ü. �����׽�Ʈ on
		static MnDepthStencilState m_depthStencilStateWithoutDepth; ///< ���� ���ٽ� ���� ������ ���� ��ü. �����׽�Ʈ off

		static MnBlendState m_blendStateWithAlpha; ///< ���� ���� ������ ���� ��ü. ���� ���� on
		static MnBlendState m_blendStateWithoutAlpha; ///< ���� ���� ������ ���� ��ü. ���� ���� off

		static MnTimer _timer; ///< �ð� ������ Ÿ�̸�
		static MnTime _elapsedTime; ///< �� �����Ӱ� �� �������� �ð���. milliseconds �����̸� �������� ���� ù��°�� ���ŵȴ�.
	};
}
