#pragma once

#include <d3d11.h>
#include <memory>
#include "../Core\MnRenderAPI.h"
#include "MnShaderPath.h"
#include "MnModel.h"

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
		HRESULT RenderModel(MnRenderAPI& renderAPI, const std::shared_ptr<MnModel>& model);

		void SetShaderPath(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath);
		
	//private:
		void _SetConstantBuffers(MnRenderAPI& renderAPI, const MnShaderPath& shaderPath);
	};

}