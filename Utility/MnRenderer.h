#pragma once

#include <d3d11.h>
#include <memory>
#include "../Core\MnRenderAPI.h"
#include "MnShaderPathInstance.h"
#include "MnMesh.h"
#include "../MnMeshTextureCombination.h"

namespace MNL
{

	/*
	A renderer is composition of shader path, constant buffer, material, texture, etc all visible resource
	*/
	class MnRenderer
	{
	public:
		MnRenderer();
		~MnRenderer();

		/*
		Set vertex and index buffer and draw call
		*/
		HRESULT RenderMesh(MnRenderAPI& renderAPI, const std::shared_ptr<MnMesh> model);

		void AddShaderPathInstance(const std::shared_ptr<MnShaderPathInstance> shaderPathInstance);
		/*
		Apply all the shader paths to context
		It does not support more than 2 shaders for now
		*/
		void ApplyShaderPaths(MnRenderAPI& renderAPI);

		/*
		Apply all constant buffers to context.
		To map the data inside, use UpdateConstantBuffer instead
		*/
		void ApplyConstantBuffers(MnRenderAPI& renderAPI);

		UINT GetNumConstantBuffers() const;
		const std::shared_ptr<MnConstantBuffer> GetConstantBuffer(UINT index) const;
		void UpdateConstantBuffer(MnRenderAPI& renderAPI, UINT index, const D3D11_SUBRESOURCE_DATA& data);

		void SetTextureCombination(const std::shared_ptr<MnMeshTextureCombination>& spMeshTextureCombination);
		void ApplyTextures(MnRenderAPI& renderAPI);
		
	protected:
		void _AddConstantBuffer(const std::shared_ptr< MnConstantBuffer> spConstantBuffer);
		void _BindConstantBuffers(MnRenderAPI& renderAPI);
		void _ClearConstantBuffers();
		void _ResizeConstantBuffers(UINT size);

	private:
		std::vector<std::shared_ptr<MnShaderPathInstance>> m_shaderPaths;
		std::vector<std::shared_ptr<MnConstantBuffer>> m_constantBuffers;
		std::shared_ptr<MnMeshTextureCombination> m_spTextureCombination;
	};

}