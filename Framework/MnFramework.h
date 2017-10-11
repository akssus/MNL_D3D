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
		/**
		@brief ����۸� �ʱ�ȭ�Ѵ�.
		@param color ������� �ʱ�ȭ �� ����
		*/
		void ClearBackBuffer(DirectX::SimpleMath::Color color = { 0.0f,0.0f,0.0f,0.0f });

		/**
		@brief ����۸� ����Ʈ���۷� �����Ͽ� ȭ�鿡 ����Ѵ�.
		*/
		void SwapBuffers();

		/**
		@brief �ش� �������� �������� ������������ ������ �ٲ۴�.
		*/
		void SetRenderer(const std::shared_ptr<MnRenderer>& spRenderer);

		/**
		@brief �ش� �������� �޽��� �������Ѵ�.
		@param spRenderer �޽��� �������� ������
		@param mesh ������ ���
		@return ���� ������ S_OK ��ȯ
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
		@brief D3D��ġ�� ���� ���� �� ���������� ������ ���� API�� �����ϴ� ��ü�μ� static���� ������ ���� API�� ���� ���������� ����Ѵ�.
		*/
		static MnRenderAPI renderAPI;

	protected:
		UINT m_screenWidth; ///< �������� ����
		UINT m_screenHeight; ///< �������� ����

	private:
		MnHardware m_hardware; ///< VGA �� ����Ϳ� ���� ������ ���� ��ü
		MnRenderWindow m_renderWindow; ///< ����� ������ ������ �� �������� ������ ���� ��ü
		MnDepthStencilState m_depthStencilState; ///< ���� ���ٽ� ���� ������ ���� ��ü
		MnRasterizerState m_rasterizerState; ///< �����Ͷ����� ���� ������ ���� ��ü
		MnViewport m_viewport; //�ӽ�
	};
}
