#pragma once

#include "Render/MnMesh.h"

namespace MNL
{
	class StandardMeshType : public MnMesh
	{
	public:
		StandardMeshType();
		~StandardMeshType();

		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData);

		const std::shared_ptr<MnSkeleton> GetSkeleton() const;

	private:
		std::shared_ptr<MnSkeleton> m_spSkeleton;
	};
}