#include "MnRenderer.h"

using namespace MNL;

MnRenderer::MnRenderer()
{
}


MnRenderer::~MnRenderer()
{
}

HRESULT MnRenderer::RenderMesh(MnRenderAPI& renderAPI, const std::shared_ptr<MnMesh> mesh)
{
	renderAPI.SetVertexBuffer(mesh->GetVertexBuffer(),mesh->GetVertexBufferStride(),0);
	renderAPI.SetIndexBuffer(mesh->GetIndexBuffer(),mesh->GetIndexBufferFormat());
	renderAPI.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw call
	//renderAPI.DrawIndexed(mesh->GetIndexCount());
	UINT numSubMeshes = mesh->GetNumSubMeshes();
	for (int i = 0; i < numSubMeshes; ++i)
	{
		auto& submesh = mesh->GetSubMesh(i);
		renderAPI.DrawIndexed(submesh.indexCount, 0, submesh.indexOffset);
	}

	return S_OK;
}
void MnRenderer::AddShaderPathInstance(const std::shared_ptr<MnShaderPathInstance> spShaderPathInstance)
{
	m_shaderPaths.push_back(spShaderPathInstance);
}
void MnRenderer::ApplyShaderPaths(MnRenderAPI& renderAPI)
{
	for (auto spShaderPath : m_shaderPaths)
	{
		renderAPI.SetVertexShader(spShaderPath->GetVertexShader());
		renderAPI.SetPixelShader(spShaderPath->GetPixelShader());
		renderAPI.SetInputLayout(spShaderPath->GetInputLayout());
		renderAPI.SetSamplerState(spShaderPath->GetSamplerState());
	}
}

void MnRenderer::_AddConstantBuffer(const std::shared_ptr< MnConstantBuffer> spConstantBuffer)
{
	assert(spConstantBuffer != nullptr);
	m_constantBuffers.push_back(spConstantBuffer);
}
void MnRenderer::ApplyConstantBuffers(MnRenderAPI& renderAPI)
{
	_BindConstantBuffers(renderAPI);
}

UINT MnRenderer::GetNumConstantBuffers() const
{
	return m_constantBuffers.size();
}
const std::shared_ptr<MnConstantBuffer> MnRenderer::GetConstantBuffer(UINT index) const
{
	return m_constantBuffers[index];
}
void MnRenderer::UpdateConstantBuffer(MnRenderAPI& renderAPI, UINT index, const D3D11_SUBRESOURCE_DATA& data)
{
	m_constantBuffers[index]->UpdateBuffer(renderAPI.GetD3DDeviceContext(), data);
}
void MnRenderer::SetTextureCombination(const std::shared_ptr<MnMeshTextureCombination>& spMeshTextureCombination)
{
	m_spTextureCombination = spMeshTextureCombination;
}
void MnRenderer::ApplyTextures(MnRenderAPI& renderAPI)
{
	const std::vector<CPD3DShaderResourceView>& shaderResourceViews = m_spTextureCombination->GetShaderResourceViews();
	for (int i = 0; i < shaderResourceViews.size(); ++i)
	{
		renderAPI.SetShaderResoureView(shaderResourceViews[i],i);
	}

}
void MnRenderer::_BindConstantBuffers(MnRenderAPI& renderAPI)
{
	UINT numConstantBuffers = m_constantBuffers.size();
	for (int i = 0; i < numConstantBuffers; ++i)
	{
		auto constantBuffer = m_constantBuffers[i];
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
void MnRenderer::_ClearConstantBuffers()
{
	m_constantBuffers.clear();
}
void MnRenderer::_ResizeConstantBuffers(UINT size)
{
	m_constantBuffers.resize(size);
}