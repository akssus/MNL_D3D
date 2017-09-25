#pragma once
#include <d3d11.h>
#include <memory>
#include <string>
#include "Core\MnTypedefs.h"
#include "Core\MnVertexBuffer.h"
#include "Core\MnIndexBuffer.h"
#include "Core\MnCustomVertexType.h"
#include "MnMeshVertexType.h"
#include "MnMeshData.h"
#include "MnMesh.h"
#include "MnSkeleton.h"
#include "MnBoneAnimation.h"

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
