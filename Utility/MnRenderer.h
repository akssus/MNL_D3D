#pragma once

#include <d3d11.h>
#include <memory>
#include "../Core\MnRenderAPI.h"
#include "MnShaderPathInstance.h"
#include "MnMesh.h"

namespace MNL
{

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
		It does not support more than 2 shaders for now
		*/
		void ApplyShaderPaths(MnRenderAPI& renderAPI);
		void AddConstantBuffer(const std::shared_ptr< MnConstantBuffer> spConstantBuffer);
		void ApplyConstantBuffers(MnRenderAPI& renderAPI);

		UINT GetNumConstantBuffers() const;
		const std::shared_ptr<MnConstantBuffer> GetConstantBuffer(UINT index) const;

		
	protected:
		void _BindConstantBuffers(MnRenderAPI& renderAPI);
		void _ClearConstantBuffers();
		void _ResizeConstantBuffers(UINT size);

	private:
		std::vector<std::shared_ptr<MnShaderPathInstance>> m_shaderPaths;
		std::vector<std::shared_ptr<MnConstantBuffer>> m_constantBuffers;
	};

}