#pragma once
#include <d3d11.h>
#include <memory>
#include <vector>
#include "MnShaderPath.h"

namespace MNL
{
	class MnShaderPathInstance : public MnShaderPath
	{
	public:
		MnShaderPathInstance();
		~MnShaderPathInstance();

		void UpdateConstantBuffer(const CPD3DDeviceContext& cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data, UINT constBufferIndex);

	protected:
		/*
		Shader entry point must be VS_MAIN and PS_MAIN, version 5_0
		*/
		HRESULT _InitShaders(const CPD3DDevice& cpDevice, const std::wstring& vsFileName, const std::wstring& psFileName);
		HRESULT _InitInputLayout(const CPD3DDevice& cpDevice, const std::shared_ptr<MnVertexShader>& spVertexShader, const std::shared_ptr<MnCustomVertexType>& spVertexType);
	};
}