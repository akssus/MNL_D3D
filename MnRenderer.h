#pragma once

#include <d3d11.h>
#include "Core\MnRenderAPI.h"
#include "Core\MnVertexBuffer.h"
#include "Core\MnVertexShader.h"
#include "Core\MnPixelShader.h"
#include "MnModel.h"

namespace MNL
{

	class MnRenderer
	{
	public:
		MnRenderer();
		~MnRenderer();

		/*
		temp plan:
		read all semantic names from vertex shader, 
		search matched semantics in the model, 
		all the shader-needed IA input must be IASet,
		the shader-needed IA that model hasn't, set as default value with warning.

		*/
		HRESULT RenderModel(const MnRenderAPI& renderAPI, MnVertexShader& vertexShader, )
		
	};

}