#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	class MnD3DDevice
	{
	public:
		MnD3DDevice();
		~MnD3DDevice();

		CPD3DDevice GetDevice() const;
		CPD3DDeviceContext GetDeviceContext() const;


	private:
		CPD3DDevice m_cpD3DDevice;
		CPD3DDeviceContext m_cpD3DDeviceContext;
	};
}