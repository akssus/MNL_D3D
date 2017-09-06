#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Utility\MnModel.h"

namespace MNL
{
	class SimpleModel : public MnModel
	{
	private:
		struct _VertexType
		{
			DirectX::SimpleMath::Vector3 position;
			DirectX::SimpleMath::Vector4 color;
			DirectX::SimpleMath::Vector3 normal;
			DirectX::SimpleMath::Vector2 texCoord1;
			DirectX::SimpleMath::Vector2 texCoord2;
		};
	public:
		SimpleModel();
		~SimpleModel();

		virtual HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& fileName, const std::shared_ptr<MnCustomVertexType>& spVertexType);

	private:
		HRESULT _LoadModel(const std::wstring& fileName);
		HRESULT _InitBuffers(const CPD3DDevice& cpDevice, const std::shared_ptr<MnCustomVertexType>& spVertexType);

	private:
		std::vector<_VertexType> m_lstMeshVertices;
		std::vector<UINT> m_lstIndices;
		UINT m_vertexCount;
		UINT m_indexCount;
	};
}