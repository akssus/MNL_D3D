#pragma once
#include <d3d11.h>
#include <wrl\client.h>
namespace MNL
{
	typedef Microsoft::WRL::ComPtr<ID3D11Device>			CPD3DDevice;
	typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext>		CPD3DDeviceContext;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilState> CPD3DDepthStencilState;
	typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	CPD3DDepthStencilView;
	typedef Microsoft::WRL::ComPtr<ID3D11RasterizerState>	CPD3DRasterizerState;

	typedef Microsoft::WRL::ComPtr<ID3D11VertexShader>		CPD3DVertexShader;
	typedef Microsoft::WRL::ComPtr<ID3D11PixelShader>		CPD3DPixelShader;

	typedef Microsoft::WRL::ComPtr<ID3D10Blob>				CPD3DBlob;

	typedef Microsoft::WRL::ComPtr<ID3D11Buffer>			CPD3DBuffer;
	typedef Microsoft::WRL::ComPtr<ID3D11Texture2D>			CPD3DTexture2D;
	typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	CPD3DRenderTargetView;

	typedef Microsoft::WRL::ComPtr<ID3D11InputLayout>		CPD3DInputLayout;

	typedef Microsoft::WRL::ComPtr<IDXGISwapChain>		CPDXGISwapChain;
	typedef Microsoft::WRL::ComPtr<IDXGIFactory>		CPDXGIFactory;
	typedef Microsoft::WRL::ComPtr<IDXGIAdapter>		CPDXGIAdapter;
	typedef Microsoft::WRL::ComPtr<IDXGIOutput>			CPDXGIOutput;

}