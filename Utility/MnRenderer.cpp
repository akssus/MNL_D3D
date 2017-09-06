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
	renderAPI.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw call
	renderAPI.DrawIndexed(model->GetIndexCount());

	return S_OK;
}

void MnRenderer::SetShaderPath(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath)
{
	renderAPI.SetVertexShader(shaderPath.GetVertexShader());
	renderAPI.SetPixelShader(shaderPath.GetPixelShader());
	renderAPI.SetInputLayout(shaderPath.GetInputLayout());

	_SetConstantBuffers(renderAPI, shaderPath);

	//update constant buffers here
	/*UINT numConstantBuffers = shaderPath.GetNumConstantBuffers();

	for (int i = 0; i < numConstantBuffers; ++i)
	{
		auto constantBuffer = shaderPath.GetConstantBuffer(i);
	}
	*/
}

void MnRenderer::_SetConstantBuffers(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath)
{
	UINT numConstantBuffers = shaderPath.GetNumConstantBuffers();
	for (int i = 0; i < numConstantBuffers; ++i)
	{
		auto constantBuffer = shaderPath.GetConstantBuffer(i);
		auto belong = constantBuffer->GetBelong();
		if (belong == MN_CONSTANT_BUFFER_BELONG_PS)
		{
			renderAPI.SetConstantBufferPS(constantBuffer->GetBuffer(), constantBuffer->GetIndex());
		}
		else if (belong == MN_CONSTANT_BUFFER_BELONG_VS)
		{
			renderAPI.SetConstantBufferVS(constantBuffer->GetBuffer(), constantBuffer->GetIndex());
		}
	}
}