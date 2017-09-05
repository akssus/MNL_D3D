#include "MnRenderer.h"

using namespace MNL;

MnRenderer::MnRenderer()
{
}


MnRenderer::~MnRenderer()
{
}

HRESULT MnRenderer::RenderModel(MnRenderAPI& renderAPI, const std::shared_ptr<MnModel>& model)
{
	renderAPI.SetVertexBuffer(model->GetVertexBuffer(),model->GetVertexBufferStride(),0);
	renderAPI.SetIndexBuffer(model->GetIndexBuffer(),model->GetIndexBufferFormat());

	//draw call
	renderAPI.DrawIndexed(model->GetIndexCount());

	return S_OK;
}

void MnRenderer::SetShaderPath(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath)
{
	renderAPI.SetVertexShader(shaderPath.GetVertexShader());
	renderAPI.SetPixelShader(shaderPath.GetPixelShader());
	renderAPI.SetInputLayout(shaderPath.GetInputLayout());

	//update constant buffers here
	/*UINT numConstantBuffers = shaderPath.GetNumConstantBuffers();

	for (int i = 0; i < numConstantBuffers; ++i)
	{
		auto constantBuffer = shaderPath.GetConstantBuffer(i);
	}
	*/
}