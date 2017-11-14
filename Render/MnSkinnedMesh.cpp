#include "MnSkinnedMesh.h"
#include "Core/MnLog.h"

using namespace MNL;

MnSkinnedMesh::MnSkinnedMesh()
{
}

MnSkinnedMesh::~MnSkinnedMesh()
{
}

HRESULT MnSkinnedMesh::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData)
{
	return MnMesh::Init(spMeshData);
}

const std::shared_ptr<MnSkeleton> MnSkinnedMesh::GetSkeleton() const
{
	return m_spSkeleton;
}