#pragma once
#include <d3d11.h>
#include "MNL.h"

namespace MNL
{
	class MnViewport
	{
	public:
		MnViewport();
		~MnViewport();
		HRESULT Init(float x, float y, float width, float height);
		const D3D11_VIEWPORT GetViewport() const;
	private:
		D3D11_VIEWPORT m_viewport;
	};
}