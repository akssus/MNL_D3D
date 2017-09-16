#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include "DXTK\SimpleMath.h"
#include "Core\MnTypedefs.h"

namespace MNL
{
	class MnMatrixPalette
	{
	public:
		MnMatrixPalette();
		~MnMatrixPalette();

		D3D11_SUBRESOURCE_DATA GetSubresourceData() const;
	private:
		std::vector<DirectX::SimpleMath::Matrix> m_matrixArray;
	};
}