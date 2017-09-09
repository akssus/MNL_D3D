#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <string>
#include "Core\MnTypedefs.h"
#include "Core\MnCustomVertexType.h"
#include "Utility\MnMesh.h"
#include "assimp\Importer.hpp"


class AssimpModel : public MNL::MnMesh
{
	struct _VertexType
	{
		DirectX::SimpleMath::Vector3 position;
		DirectX::SimpleMath::Vector4 color;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector2 texCoord1;
		DirectX::SimpleMath::Vector2 texCoord2;
	};


public:
	AssimpModel();
	~AssimpModel();
	HRESULT AssimpModel::LoadModelFromFile(const MNL::CPD3DDevice& cpDevice, const std::wstring& modelFileName, const std::shared_ptr<MNL::MnCustomVertexType>& spVertexType);

private:
	HRESULT _LoadModel(const std::wstring& fileName);
	HRESULT _InitBuffers(const MNL::CPD3DDevice& cpDevice, const std::shared_ptr<MNL::MnCustomVertexType>& spVertexType);

private:
	std::vector<_VertexType> m_lstMeshVertices;
	std::vector<UINT> m_lstIndices;
	UINT m_vertexCount;
	UINT m_indexCount;
};