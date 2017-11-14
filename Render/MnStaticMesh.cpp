#include "MnStaticMesh.h"

using namespace MNL;

MnStaticMesh::MnStaticMesh()
{
}


MnStaticMesh::~MnStaticMesh()
{
}

HRESULT MnStaticMesh::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData)
{
	return MnMesh::Init(spMeshData);
}