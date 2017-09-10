#pragma once

#include <d3d11.h>
#include <memory>
#include "../Core\MnRenderAPI.h"
#include "MnShaderPath.h"
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
		HRESULT RenderMesh(MnRenderAPI& renderAPI, const std::shared_ptr<MnMesh>& model);

		void SetShaderPath(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath);
		
	//private:
		void _SetConstantBuffers(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath);
	};

}