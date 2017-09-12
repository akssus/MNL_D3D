#include <Windows.h>
#include <d3d11.h>
#include <memory>
#include "DXTK\SimpleMath.h"
#include "Core\MNL_Core.h"
#include "Utility\MNL_Utility.h"
#include "BasicShaderPath.h"
#include "MnResourcePool.h"
#include "MnStaticMesh.h"
#include "MnMeshVertexType.h"
#include "MnMeshRenderer.h"

using namespace DirectX::SimpleMath;
using namespace MNL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	//initialize
	MNL::MnHardware hardware;
	HRESULT result = hardware.Init();
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	MNL::MnRenderAPI renderAPI;
	result = renderAPI.Init(hardware, true);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	MNL::MnRenderWindow renderWindow;
	result = renderWindow.Init(hInstance, nCmdShow, L"MNL", L"MNL", 100, 100, 1024, 768, WndProc,
		hardware, true, 1, 60, true, true, 1, renderAPI.GetD3DDevice(), renderAPI.GetD3DDeviceContext());
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	//init depth stencil state
	MNL::MnDepthStencilState depthStencilState;
	result = depthStencilState.Init(renderAPI.GetD3DDevice(), true, true);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetDepthStencilState(depthStencilState.GetState());

	//init depth stencil buffer
	MNL::MnDepthStencilBuffer depthStencilBuffer;
	result = depthStencilBuffer.Init(renderAPI.GetD3DDevice(), 1024, 768);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetRenderTarget(renderWindow.GetBackBufferView(), depthStencilBuffer.GetDepthStencilView());


	//init rasterizer state
	MNL::MnRasterizerState rasterizerState;
	result = rasterizerState.Init(renderAPI.GetD3DDevice(), D3D11_FILL_SOLID, true);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetRasterizerState(rasterizerState.GetState());

	//init viewport
	MNL::MnViewport viewport;
	result = viewport.Init(0, 0, 1024, 768);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderAPI.SetViewport(viewport.GetViewport());

	/**********************************************************/

	auto vertexType = std::make_shared<MnMeshVertexType>();

	auto shaderPath = std::make_shared<BasicShaderPath>();
	result = shaderPath->Init(renderAPI.GetD3DDevice(),vertexType);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}

	MNL::MnMeshRenderer renderer;
	result = renderer.Init(renderAPI.GetD3DDevice(), vertexType);
	if (FAILED(result))
	{
		//error msg
		return 0;
	}
	renderer.AddShaderPathInstance(shaderPath);

	//this functions only call when shader or renderer changed
	renderer.ApplyShaderPaths(renderAPI);
	renderer.ApplyConstantBuffers(renderAPI);

	MNL::MnCamera camera;
	camera.SetFOV(3.14f / 5.0f);
	camera.SetNearDistance(0.1f);
	camera.SetFarDistance(10000.0f);
	camera.SetAspectRatio(1024.0f/768.0f);
	camera.SetPosition(Vector3(0, 0, -1000.0f));
	camera.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));

	Matrix matWorld;
	ZeroMemory(&matWorld, sizeof(Matrix));
	matWorld = Matrix::Identity;
	float rad = 0.0f;

	MnResourcePool resourcePool;
	resourcePool.LoadModelFromFile(renderAPI.GetD3DDevice(),"rico.fbx",vertexType);

	auto mesh = std::make_shared<MnStaticMesh>();
	auto meshData = resourcePool.GetMeshData("rico.fbx", "Rico");
	mesh->Init(renderAPI.GetD3DDevice(), meshData);

	auto textureComb = std::make_shared<MnMeshTextureCombination>();
	auto texture = std::make_shared<MnMeshTexture>();
	texture->LoadFromFile(renderAPI.GetD3DDevice(), L"rico_uv.png");
	textureComb->AddMeshTexture(texture);

	renderer.SetTextureCombination(textureComb);
	renderer.ApplyTextures(renderAPI);

	/**************************************************************/


	MSG wndMsg;
	ZeroMemory(&wndMsg, sizeof(MSG));
	while (wndMsg.message != WM_QUIT)
	{
		if(PeekMessage(&wndMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&wndMsg);
			DispatchMessage(&wndMsg);
		}
		else
		{
			renderAPI.ClearRenderTargets(renderWindow.GetBackBufferView(), depthStencilBuffer.GetDepthStencilView(), Vector4(0.5f, 0.5f, 0.5f, 1.0f));
			//render here
			
			rad += 0.01f;
			//matWorld = Matrix::CreateRotationY(rad);
			matWorld = mesh->GetTransform();
			matWorld = matWorld * Matrix::CreateRotationY(rad);
			matWorld = matWorld * Matrix::CreateTranslation(0.0f, -200.0f, 0.0f);
			renderer.SetWorldBuffer(renderAPI, matWorld);
			renderer.SetViewProjectionBuffer(renderAPI, camera.GetViewMatrix(), camera.GetProjectionMatrix());
			renderer.RenderMesh(renderAPI, mesh);

			renderWindow.SwapBuffers();
		}
	}


	return 0;
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
