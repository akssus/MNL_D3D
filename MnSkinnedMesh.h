#pragma once
#include <d3d11.h>
#include <memory>
#include <string>
#include "Core\MnTypedefs.h"
#include "Core\MnVertexBuffer.h"
#include "Core\MnIndexBuffer.h"
#include "Core\MnCustomVertexType.h"
#include "Render/MnMeshVertexType.h"
#include "Render/MnMeshData.h"
#include "Render/MnMesh.h"
#include "MnSkeleton.h"

namespace MNL
{
	/*
	MnSkinnedMesh is static mesh instance with no bones
	*/
	class MnSkinnedMesh : public MnMesh
	{
	public:
		MnSkinnedMesh();
		~MnSkinnedMesh();

		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData);

		const std::shared_ptr<MnSkeleton> GetSkeleton() const;

	private:
		std::shared_ptr<MnSkeleton> m_spSkeleton;
	};
}
