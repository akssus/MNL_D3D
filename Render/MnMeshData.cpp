#include "MnMeshData.h"

using namespace MNL;

MnMeshData::MnMeshData():m_spParentIndex(nullptr),m_hasBone(false)
{
	ZeroMemory(&m_matTransform, sizeof(DirectX::SimpleMath::Matrix));
}


MnMeshData::~MnMeshData()
{
}

void MnMeshData::AddSubMesh(const MnSubMesh& submesh)
{
	m_lstSubMeshes.push_back(submesh);
}
void MnMeshData::SetName(const std::string& name)
{
	m_meshName = name;
}
void MnMeshData::SetSkeleton(const std::shared_ptr<MnSkeleton> spSkeleton)
{
	m_spSkeleton = spSkeleton;
}
void MnMeshData::SetTransform(const DirectX::SimpleMath::Matrix& matTransform)
{
	m_matTransform = matTransform;
}
const DirectX::SimpleMath::Matrix& MnMeshData::GetTransform() const
{
	return m_matTransform;
}
void MnMeshData::SetParentIndex(UINT index)
{
	m_spParentIndex = std::make_shared<UINT>(index);
}

void MnMeshData::SetVertexBuffer(const std::shared_ptr<MnVertexBuffer> spVertexBuffer)
{
	m_spVertexBuffer = spVertexBuffer;
}
void MnMeshData::SetIndexBuffer(const std::shared_ptr<MnIndexBuffer> spIndexBuffer)
{
	m_spIndexBuffer = spIndexBuffer;
}
void MnMeshData::AddAnimation(const MnBoneAnimation& animation)
{
	m_lstBoneAnimations.push_back(animation);
}

bool MnMeshData::HasBone() const
{
	return m_hasBone;
}

std::shared_ptr<MnVertexBuffer> MnMeshData::GetVertexBuffer() const
{
	return m_spVertexBuffer;
}
std::shared_ptr<MnIndexBuffer> MnMeshData::GetIndexBuffer() const
{
	return m_spIndexBuffer;
}
const std::string& MnMeshData::GetName() const
{
	return m_meshName;
}
const std::shared_ptr<MnSkeleton> MnMeshData::GetSkeleton() const
{
	return m_spSkeleton;
}
std::shared_ptr<UINT> MnMeshData::GetParentIndex() const
{
	return m_spParentIndex;
}
UINT MnMeshData::GetNumSubMeshes() const
{
	return m_lstSubMeshes.size();
}
const std::vector<MnSubMesh>& MnMeshData::GetSubMeshes() const
{
	return m_lstSubMeshes;
}