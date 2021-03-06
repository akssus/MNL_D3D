#pragma once
#include <d3d11.h>
#include <string>
#include "../Core\MnTypedefs.h"
#include "../Core\MnVertexBuffer.h"
#include "../Core\MnIndexBuffer.h"
#include "../Core\MnCustomVertexType.h"
#include "MnMeshVertexType.h"
#include "MnMeshData.h"
#include "MnMesh.h"

namespace MNL
{
	/*
	MnStaticMesh is static mesh instance with no bones
	*/
	class MnStaticMesh : public MnMesh
	{
	public:
		MnStaticMesh();
		~MnStaticMesh();

		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData);
	};
}
