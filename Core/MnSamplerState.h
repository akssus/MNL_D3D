#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"

namespace MNL
{
	class MnSamplerState
	{
	public:
		MnSamplerState();
		~MnSamplerState();

		/*
		Initialize with default sampler state;
		*/
		HRESULT Init(const CPD3DDevice& cpDevice);

		const CPD3DSamplerState GetSamplerState() const;

	private:
		CPD3DSamplerState m_cpSamplerState;
	};
}