#pragma once
#include "Utility\MnShaderPathInstance.h"

namespace MNL
{
	class MnMeshShaderPath : public MnShaderPathInstance
	{
	public:
		MnMeshShaderPath();
		~MnMeshShaderPath();

		HRESULT Init();
	private:
		HRESULT _InitConstantBuffers(const CPD3DDevice& cpDevice);
	};
}
