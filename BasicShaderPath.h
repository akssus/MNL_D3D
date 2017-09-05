#pragma once
#include "Utility\MnShaderPath.h"
#include "Core/MnConstantBuffer.h"

namespace MNL
{
	class BasicShaderPath : public MnShaderPath
	{
	public:
		BasicShaderPath();
		~BasicShaderPath();
		HRESULT Init(const CPD3DDevice& cpDevice);
		

	private:
		void _InitConstantBuffers(const CPD3DDevice& cpDevice);

	private:
		MnConstantBuffer m_transformBuffer;
	};
}
