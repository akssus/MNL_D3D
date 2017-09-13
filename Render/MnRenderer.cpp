#include "MnRenderer.h"

using namespace MNL;

MnRenderer::MnRenderer():m_numPsConstantBuffers(0),m_numVsConstantBuffers(0)
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
	if (spConstantBuffer->GetBelong() == MN_CONSTANT_BUFFER_BELONG_VS)
	{
		m_mapIndexToSlot[spConstantBuffer->GetIndex()] = m_numVsConstantBuffers;
		m_numVsConstantBuffers++;
	}
	else if (spConstantBuffer->GetBelong() == MN_CONSTANT_BUFFER_BELONG_PS)
	{
		m_mapIndexToSlot[spConstantBuffer->GetIndex()] = m_numPsConstantBuffers;
		m_numPsConstantBuffers++;
	}
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
		UINT slotIndex = m_mapIndexToSlot[constantBuffer->GetIndex()];
		if (belong == MN_CONSTANT_BUFFER_BELONG_PS)
		{
			renderAPI.SetConstantBufferPS(constantBuffer->GetBuffer(), slotIndex);
		}
		else if (belong == MN_CONSTANT_BUFFER_BELONG_VS)
		{
			renderAPI.SetConstantBufferVS(constantBuffer->GetBuffer(), slotIndex);
		}
	}
}
void MnRenderer::_ClearConstantBuffers()
{
	m_constantBuffers.clear();
	m_numVsConstantBuffers = 0;
	m_numPsConstantBuffers = 0;
}