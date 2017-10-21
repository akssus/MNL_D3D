/**
@class MNL::MnRenderAPI
@author Akssus
@brief 비디오 장치와 상호작용 하는 모든 인터페이스를 지니는 객체
@section 개요
MnRenderAPI는 MnHardware - MnRenderAPI - MnRenderWindow 로 대표되는 MNL의 3개의 핵심 클래스 중 하나이다. \n
MnRenderAPI는 D3DDevice, D3DDeviceContext 인터페이스를 통해 비디오 장치와의 상호작용에 관한 모든 인터페이스를 제공한다. \n
MnRenderAPI는 그래픽 파이프라인의 대부분의 구간에 접근 가능하며 그래픽 파이프라인의 모든 설정은 MnRenderAPI를 통해 설정된다. \n
MnRenderAPI는 DrawIndexed 드로우 콜을 통해 최종 출력을 실시할 수 있다.
*/
#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <memory>
#include "MnTypedefs.h"
#include "MnVertexBuffer.h"
#include "MnIndexBuffer.h"
#include "MnInputLayout.h"
#include "MnPixelShader.h"
#include "MnVertexShader.h"
#include "MnHardware.h"
#include "MnD3DDevice.h"

namespace MNL
{
	class MnRenderAPI
	{
	public:
		MnRenderAPI();
		~MnRenderAPI();

		/**
		@brief MnHardware 정보를 토대로 MnD3DDevice를 초기화 한다.
		@param useDefaultAdapter 디폴트 비디오 어댑터 사용 여부
		@return 초기화 성공 여부
		@warning 현재 useDefaultAdapter의 값과 상관없이 디폴트 비디오 어댑터로 초기화 된다.
		*/
		HRESULT Init(const MnHardware& hardwareInfo, bool useDefaultAdapter);

		/**
		@brief 버텍스 버퍼를 그래픽 파이프라인 Input Assembler 단계에 바인드한다.
		@param vertexBuffer 버텍스 버퍼 인터페이스
		@param stride 버텍스 stride. 버텍스 하나의 byte 크기를 뜻한다.
		@param offset 버텍스의 시작 주소로부터의 offset
		*/
		void SetVertexBuffer(const CPD3DBuffer& vertexBuffer, UINT stride, UINT offset);

		/**
		@brief 버텍스 버퍼를 그래픽 파이프라인 Input Assembler 단계에 바인드한다.
		@param vertexBuffer 초기화 된 MnVertexBuffer 객체
		*/
		void SetVertexBuffer(const MnVertexBuffer& vertexBuffer);
		
		/**
		@brief 인덱스 버퍼를 그래픽 파이프라인 Input Assembler 단계에 바인드한다.
		@param indexBuffer 인덱스 버퍼 인터페이스
		@param DXGI_FORMAT 인덱스로 사용되는 파일형. 일반적으로 4바이트 UINT가 사용된다.
		*/
		void SetIndexBuffer(const CPD3DBuffer& indexBuffer, DXGI_FORMAT format);

		/**
		@brief 인덱스 버퍼를 그래픽 파이프라인 Input Assembler 단계에 바인드한다.
		@param indexBuffer 초기화 된 MnIndexBuffer 객체
		*/
		void SetIndexBuffer(const MnIndexBuffer& indexBuffer);

		/**
		@brief 도형 토폴로지를 그래픽 파이프라인 Input Assembler 단계에 설정한다.
		@param primitiveTopology 도형 토폴로지. 통상 D3D_PRIMITIVE_TRIANGLELIST가 사용된다.
		*/
		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology);

		/**
		@brief 인풋 레이아웃을 그래픽 파이프라인 Input Assembler 단계에 설정한다.
		@param cpInputLayout 인풋 레이아웃 인터페이스. MnInputLayout 객체로부터 얻어올 수 있다.
		*/
		void SetInputLayout(const CPD3DInputLayout& cpInputLayout);

		/**
		@brief 버텍스 셰이더를 그래픽 파이프라인 Vertex Shader 단계에 설정한다.
		@param cpVertexShader 버텍스 셰이더 인터페이스. MnVertexShader 객체로부터 얻어올 수 있다.
		*/
		void SetVertexShader(const CPD3DVertexShader& cpVertexShader);

		/**
		@brief 픽셀 셰이더를 그래픽 파이프라인 Pixel Shader 단계에 설정한다.
		@param cpPixelShader 픽셀 셰이더 인터페이스. MnPixelShader 객체로부터 얻어올 수 있다.
		*/
		void SetPixelShader(const CPD3DPixelShader& cpPixelShader);

		/**
		@brief 상수 버퍼를 그래픽 파이프라인 Vertex Shader 단계에 설정한다.
		@param cpConstantBuffer 상수 버퍼 인터페이스. MnConstantBuffer 객체로부터 얻어올 수 있다.
		@param index 상수 버퍼의 레지스터 인덱스. 버텍스 셰이더 내의 register(b#)으로 바인드 된다.
		*/
		void SetConstantBufferVS(const CPD3DBuffer& cpConstantBuffer, UINT index);

		/**
		@brief 상수 버퍼를 그래픽 파이프라인 Pixel Shader 단계에 설정한다.
		@param cpConstantBuffer 상수 버퍼 인터페이스. MnConstantBuffer 객체로부터 얻어올 수 있다.
		@param index 상수 버퍼의 레지스터 인덱스. 픽셀 셰이더 내의 register(b#)으로 바인드 된다.
		*/
		void SetConstantBufferPS(const CPD3DBuffer& cpConstantBuffer, UINT index);

		/**
		@brief 샘플러 스테이트를 그래픽 파이프라인 Rasterizer 단계에 설정한다.
		@param cpSamplerState 샘플러 스테이트 인터페이스. MnSamplerState 객체로부터 얻어올 수 있다.
		*/
		void SetSamplerState(const CPD3DSamplerState& cpSamplerState);

		/**
		@brief 셰이더 리소스 뷰 (통상 텍스쳐)를 그래픽 파이프라인 Pixel Shader 단계에 설정한다.
		@param cpShaderResourceView 셰이더 리소스 뷰 인터페이스.
		@param slot 셰이더 리소스 뷰의 레지스터 슬롯. 픽셀 셰이더 내의 register(t#)으로 바인드된다.
		*/
		void SetShaderResoureView(const CPD3DShaderResourceView& cpShaderResourceView, UINT slot);

		/**
		@brief 렌더 타겟 및 뎁스 스텐실 뷰을 그래픽 파이프라인 Output Merger 단계에 설정한다.
		@param cpRenderTargetView 렌더타겟 뷰 인터페이스.
		@param cpDepthStencilView 뎁스 스텐실 뷰 인터페이스.
		@detail 만약 Render-to-Texture 기법을 사용하는 경우 백버퍼와 독립된 렌더타겟 뷰와 뎁스 스텐실 뷰를 생성, 설정해야 한다.
		*/
		void SetRenderTarget(const CPD3DRenderTargetView& cpRenderTargetView, const CPD3DDepthStencilView& cpDepthStencilView);

		/**
		@brief 뎁스 스텐실 스테이트를 그래픽 파이프라인 Output Merger 단계에 설정한다.
		@param cpDepthStencilState 뎁스 스텐실 스테이트 인터페이스.
		@detail 뎁스 스텐실 스테이트는 깊이 테스트와 스텐실 테스트 함수를 정의한다.
		*/
		void SetDepthStencilState(const CPD3DDepthStencilState& cpDepthStencilState);


		/**
		@brief 블렌드 스테이트를 OutputMerger 단계에 설정한다.
		*/
		void SetBlendState(const CPD3DBlendState& cpBlendState);

		/**
		@brief 래스터라이저 스테이트를 그래픽 파이프라인 Rasterizer 단계에 설정한다.
		@param cpRasterizerState 래스터라이저 스테이트 인터페이스.
		@detail 래스터라이저 스테이트는 와이어프레임, 솔리드 필 등 래스터라이즈 방식과 백페이스 컬링 방식을 정의한다.
		*/
		void SetRasterizerState(const CPD3DRasterizerState& cpRasterizerState);
		
		/**
		@brief 뷰포트를 그래픽 파이프라인 Rasterizer 단계에 설정한다.
		@param viewport 뷰포트 좌표 및 크기가 정의된 뷰포트 객체
		*/
		void SetViewport(const D3D11_VIEWPORT& viewport);

	public:
		/**
		@brief 해당 렌더타겟 뷰와 뎁스 스텐실 뷰를 초기값으로 클리어한다.
		@param renderTargetView 클리어 될 렌더 타겟 뷰. 텍스쳐 혹은 백 버퍼가 될 수 있다.
		@param depthStencilView 클리어 될 뎁스 스텐실 뷰. 텍스쳐 혹은 백 버퍼가 될 수 있다. 뎁스는 1.0f, 스텐실은 0으로 초기화된다.
		@param color 렌더 타겟 뷰를 클리어할 색상. 기본값으로 검은색이다.
		*/
		void ClearRenderTargets(CPD3DRenderTargetView renderTargetView, CPD3DDepthStencilView depthStencilView, DirectX::SimpleMath::Color color = { 0.0f, 0.0f, 0.0f, 0.0f });

		/**
		@brief 그래픽 파이프라인의 드로우 콜.
		@param indexCount 설정된 인덱스 버퍼 내의 인덱스 개수. 
		@detail 인덱스를 참조해 버텍스 버퍼의 메모리로 접근하기 때문에 인덱스의 개수만 알면 된다. 그러므로 버텍스의 개수는 인자로 받지 않는다.
		*/
		void DrawIndexed(UINT indexCount);
		/**
		@brief 그래픽 파이프라인의 드로우 콜.
		@param indexCount 설정된 인덱스 버퍼 내의 인덱스 개수.
		@param indexOffset 인덱스 버퍼 내의 시작 메모리로부터의 오프셋.
		@param vertexBase 버텍스 버퍼 내의 시작 메모리로부터의 오프셋.
		@detail 인덱스를 참조해 버텍스 버퍼의 메모리로 접근하기 때문에 인덱스의 개수만 알면 된다. 그러므로 버텍스의 개수는 인자로 받지 않는다. \n
		vertexBase는 하나의 버텍스 버퍼 안에 여러 메쉬가 선형으로 붙어 있는 경우 사용된다. \n
		예를 들어 vertexBase가 10일 경우 인덱스 0은 실제로 인덱스 10이다.\n
		이는 MnMesh의 SubMesh를 구현할 때 사용된다.
		*/
		void DrawIndexed(UINT indexCount, UINT indexOffset, UINT vertexBase);

	public:
		const CPD3DDevice GetD3DDevice() const; ///< D3DDevice 인터페이스
		const CPD3DDeviceContext GetD3DDeviceContext() const; ///<D3DDeviceContext 인터페이스

	private:		
		MnD3DDevice	m_D3DDevice;
	};
}