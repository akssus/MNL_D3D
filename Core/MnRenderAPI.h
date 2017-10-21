/**
@class MNL::MnRenderAPI
@author Akssus
@brief ���� ��ġ�� ��ȣ�ۿ� �ϴ� ��� �������̽��� ���ϴ� ��ü
@section ����
MnRenderAPI�� MnHardware - MnRenderAPI - MnRenderWindow �� ��ǥ�Ǵ� MNL�� 3���� �ٽ� Ŭ���� �� �ϳ��̴�. \n
MnRenderAPI�� D3DDevice, D3DDeviceContext �������̽��� ���� ���� ��ġ���� ��ȣ�ۿ뿡 ���� ��� �������̽��� �����Ѵ�. \n
MnRenderAPI�� �׷��� ������������ ��κ��� ������ ���� �����ϸ� �׷��� ������������ ��� ������ MnRenderAPI�� ���� �����ȴ�. \n
MnRenderAPI�� DrawIndexed ��ο� ���� ���� ���� ����� �ǽ��� �� �ִ�.
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
		@brief MnHardware ������ ���� MnD3DDevice�� �ʱ�ȭ �Ѵ�.
		@param useDefaultAdapter ����Ʈ ���� ����� ��� ����
		@return �ʱ�ȭ ���� ����
		@warning ���� useDefaultAdapter�� ���� ������� ����Ʈ ���� ����ͷ� �ʱ�ȭ �ȴ�.
		*/
		HRESULT Init(const MnHardware& hardwareInfo, bool useDefaultAdapter);

		/**
		@brief ���ؽ� ���۸� �׷��� ���������� Input Assembler �ܰ迡 ���ε��Ѵ�.
		@param vertexBuffer ���ؽ� ���� �������̽�
		@param stride ���ؽ� stride. ���ؽ� �ϳ��� byte ũ�⸦ ���Ѵ�.
		@param offset ���ؽ��� ���� �ּҷκ����� offset
		*/
		void SetVertexBuffer(const CPD3DBuffer& vertexBuffer, UINT stride, UINT offset);

		/**
		@brief ���ؽ� ���۸� �׷��� ���������� Input Assembler �ܰ迡 ���ε��Ѵ�.
		@param vertexBuffer �ʱ�ȭ �� MnVertexBuffer ��ü
		*/
		void SetVertexBuffer(const MnVertexBuffer& vertexBuffer);
		
		/**
		@brief �ε��� ���۸� �׷��� ���������� Input Assembler �ܰ迡 ���ε��Ѵ�.
		@param indexBuffer �ε��� ���� �������̽�
		@param DXGI_FORMAT �ε����� ���Ǵ� ������. �Ϲ������� 4����Ʈ UINT�� ���ȴ�.
		*/
		void SetIndexBuffer(const CPD3DBuffer& indexBuffer, DXGI_FORMAT format);

		/**
		@brief �ε��� ���۸� �׷��� ���������� Input Assembler �ܰ迡 ���ε��Ѵ�.
		@param indexBuffer �ʱ�ȭ �� MnIndexBuffer ��ü
		*/
		void SetIndexBuffer(const MnIndexBuffer& indexBuffer);

		/**
		@brief ���� ���������� �׷��� ���������� Input Assembler �ܰ迡 �����Ѵ�.
		@param primitiveTopology ���� ��������. ��� D3D_PRIMITIVE_TRIANGLELIST�� ���ȴ�.
		*/
		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology);

		/**
		@brief ��ǲ ���̾ƿ��� �׷��� ���������� Input Assembler �ܰ迡 �����Ѵ�.
		@param cpInputLayout ��ǲ ���̾ƿ� �������̽�. MnInputLayout ��ü�κ��� ���� �� �ִ�.
		*/
		void SetInputLayout(const CPD3DInputLayout& cpInputLayout);

		/**
		@brief ���ؽ� ���̴��� �׷��� ���������� Vertex Shader �ܰ迡 �����Ѵ�.
		@param cpVertexShader ���ؽ� ���̴� �������̽�. MnVertexShader ��ü�κ��� ���� �� �ִ�.
		*/
		void SetVertexShader(const CPD3DVertexShader& cpVertexShader);

		/**
		@brief �ȼ� ���̴��� �׷��� ���������� Pixel Shader �ܰ迡 �����Ѵ�.
		@param cpPixelShader �ȼ� ���̴� �������̽�. MnPixelShader ��ü�κ��� ���� �� �ִ�.
		*/
		void SetPixelShader(const CPD3DPixelShader& cpPixelShader);

		/**
		@brief ��� ���۸� �׷��� ���������� Vertex Shader �ܰ迡 �����Ѵ�.
		@param cpConstantBuffer ��� ���� �������̽�. MnConstantBuffer ��ü�κ��� ���� �� �ִ�.
		@param index ��� ������ �������� �ε���. ���ؽ� ���̴� ���� register(b#)���� ���ε� �ȴ�.
		*/
		void SetConstantBufferVS(const CPD3DBuffer& cpConstantBuffer, UINT index);

		/**
		@brief ��� ���۸� �׷��� ���������� Pixel Shader �ܰ迡 �����Ѵ�.
		@param cpConstantBuffer ��� ���� �������̽�. MnConstantBuffer ��ü�κ��� ���� �� �ִ�.
		@param index ��� ������ �������� �ε���. �ȼ� ���̴� ���� register(b#)���� ���ε� �ȴ�.
		*/
		void SetConstantBufferPS(const CPD3DBuffer& cpConstantBuffer, UINT index);

		/**
		@brief ���÷� ������Ʈ�� �׷��� ���������� Rasterizer �ܰ迡 �����Ѵ�.
		@param cpSamplerState ���÷� ������Ʈ �������̽�. MnSamplerState ��ü�κ��� ���� �� �ִ�.
		*/
		void SetSamplerState(const CPD3DSamplerState& cpSamplerState);

		/**
		@brief ���̴� ���ҽ� �� (��� �ؽ���)�� �׷��� ���������� Pixel Shader �ܰ迡 �����Ѵ�.
		@param cpShaderResourceView ���̴� ���ҽ� �� �������̽�.
		@param slot ���̴� ���ҽ� ���� �������� ����. �ȼ� ���̴� ���� register(t#)���� ���ε�ȴ�.
		*/
		void SetShaderResoureView(const CPD3DShaderResourceView& cpShaderResourceView, UINT slot);

		/**
		@brief ���� Ÿ�� �� ���� ���ٽ� ���� �׷��� ���������� Output Merger �ܰ迡 �����Ѵ�.
		@param cpRenderTargetView ����Ÿ�� �� �������̽�.
		@param cpDepthStencilView ���� ���ٽ� �� �������̽�.
		@detail ���� Render-to-Texture ����� ����ϴ� ��� ����ۿ� ������ ����Ÿ�� ��� ���� ���ٽ� �並 ����, �����ؾ� �Ѵ�.
		*/
		void SetRenderTarget(const CPD3DRenderTargetView& cpRenderTargetView, const CPD3DDepthStencilView& cpDepthStencilView);

		/**
		@brief ���� ���ٽ� ������Ʈ�� �׷��� ���������� Output Merger �ܰ迡 �����Ѵ�.
		@param cpDepthStencilState ���� ���ٽ� ������Ʈ �������̽�.
		@detail ���� ���ٽ� ������Ʈ�� ���� �׽�Ʈ�� ���ٽ� �׽�Ʈ �Լ��� �����Ѵ�.
		*/
		void SetDepthStencilState(const CPD3DDepthStencilState& cpDepthStencilState);


		/**
		@brief ���� ������Ʈ�� OutputMerger �ܰ迡 �����Ѵ�.
		*/
		void SetBlendState(const CPD3DBlendState& cpBlendState);

		/**
		@brief �����Ͷ����� ������Ʈ�� �׷��� ���������� Rasterizer �ܰ迡 �����Ѵ�.
		@param cpRasterizerState �����Ͷ����� ������Ʈ �������̽�.
		@detail �����Ͷ����� ������Ʈ�� ���̾�������, �ָ��� �� �� �����Ͷ����� ��İ� �����̽� �ø� ����� �����Ѵ�.
		*/
		void SetRasterizerState(const CPD3DRasterizerState& cpRasterizerState);
		
		/**
		@brief ����Ʈ�� �׷��� ���������� Rasterizer �ܰ迡 �����Ѵ�.
		@param viewport ����Ʈ ��ǥ �� ũ�Ⱑ ���ǵ� ����Ʈ ��ü
		*/
		void SetViewport(const D3D11_VIEWPORT& viewport);

	public:
		/**
		@brief �ش� ����Ÿ�� ��� ���� ���ٽ� �並 �ʱⰪ���� Ŭ�����Ѵ�.
		@param renderTargetView Ŭ���� �� ���� Ÿ�� ��. �ؽ��� Ȥ�� �� ���۰� �� �� �ִ�.
		@param depthStencilView Ŭ���� �� ���� ���ٽ� ��. �ؽ��� Ȥ�� �� ���۰� �� �� �ִ�. ������ 1.0f, ���ٽ��� 0���� �ʱ�ȭ�ȴ�.
		@param color ���� Ÿ�� �並 Ŭ������ ����. �⺻������ �������̴�.
		*/
		void ClearRenderTargets(CPD3DRenderTargetView renderTargetView, CPD3DDepthStencilView depthStencilView, DirectX::SimpleMath::Color color = { 0.0f, 0.0f, 0.0f, 0.0f });

		/**
		@brief �׷��� ������������ ��ο� ��.
		@param indexCount ������ �ε��� ���� ���� �ε��� ����. 
		@detail �ε����� ������ ���ؽ� ������ �޸𸮷� �����ϱ� ������ �ε����� ������ �˸� �ȴ�. �׷��Ƿ� ���ؽ��� ������ ���ڷ� ���� �ʴ´�.
		*/
		void DrawIndexed(UINT indexCount);
		/**
		@brief �׷��� ������������ ��ο� ��.
		@param indexCount ������ �ε��� ���� ���� �ε��� ����.
		@param indexOffset �ε��� ���� ���� ���� �޸𸮷κ����� ������.
		@param vertexBase ���ؽ� ���� ���� ���� �޸𸮷κ����� ������.
		@detail �ε����� ������ ���ؽ� ������ �޸𸮷� �����ϱ� ������ �ε����� ������ �˸� �ȴ�. �׷��Ƿ� ���ؽ��� ������ ���ڷ� ���� �ʴ´�. \n
		vertexBase�� �ϳ��� ���ؽ� ���� �ȿ� ���� �޽��� �������� �پ� �ִ� ��� ���ȴ�. \n
		���� ��� vertexBase�� 10�� ��� �ε��� 0�� ������ �ε��� 10�̴�.\n
		�̴� MnMesh�� SubMesh�� ������ �� ���ȴ�.
		*/
		void DrawIndexed(UINT indexCount, UINT indexOffset, UINT vertexBase);

	public:
		const CPD3DDevice GetD3DDevice() const; ///< D3DDevice �������̽�
		const CPD3DDeviceContext GetD3DDeviceContext() const; ///<D3DDeviceContext �������̽�

	private:		
		MnD3DDevice	m_D3DDevice;
	};
}