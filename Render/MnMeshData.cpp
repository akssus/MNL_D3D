#include "MnMeshData.h"

using namespace MNL;

MnSubMeshData::MnSubMeshData():m_spParentIndex(nullptr)
{
	ZeroMemory(&m_matTransform, sizeof(DirectX::SimpleMath::Matrix));
}


MnSubMeshData::~MnSubMeshData()
{
}

void MnSubMeshData::AddSubMeshFragment(const MnSubMeshFragment& submesh)
{
	m_lstSubMeshFragments.push_back(submesh);
}
void MnSubMeshData::SetName(const std::string& name)
{
	m_meshName = name;
}

void MnSubMeshData::SetTransform(const DirectX::SimpleMath::Matrix& matTransform)
{
	m_matTransform = matTransform;
}
void MnSubMeshData::SetParentIndex(UINT index)
{
	m_spParentIndex = std::make_shared<UINT>(index);
}

void MnSubMeshData::SetVertexBuffer(const std::shared_ptr<MnVertexBuffer> spVertexBuffer)
{
	m_spVertexBuffer = spVertexBuffer;
}
void MnSubMeshData::SetIndexBuffer(const std::shared_ptr<MnIndexBuffer> spIndexBuffer)
{
	m_spIndexBuffer = spIndexBuffer;
}

std::shared_ptr<MnVertexBuffer> MnSubMeshData::GetVertexBuffer() const
{
	return m_spVertexBuffer;
}
std::shared_ptr<MnIndexBuffer> MnSubMeshData::GetIndexBuffer() const
{
	return m_spIndexBuffer;
}

const std::string& MnSubMeshData::GetName() const
{
	return m_meshName;
}

const DirectX::SimpleMath::Matrix& MnSubMeshData::GetTransform() const
{
	return m_matTransform;
}

std::shared_ptr<UINT> MnSubMeshData::GetParentIndex() const
{
	return m_spParentIndex;
}
UINT MnSubMeshData::GetNumSubMeshFragments() const
{
	return m_lstSubMeshFragments.size();
}
const std::vector<MnSubMeshFragment>& MnSubMeshData::GetSubMeshFragments() const
{
	return m_lstSubMeshFragments;
}

MnMeshData::MnMeshData() : m_hasBones(false)
{

}

MnMeshData::~MnMeshData()
{

}

void MnMeshData::AddSubMesh(const std::shared_ptr<MnSubMeshData>& spSubMesh)
{
	m_lstSubMeshes.push_back(spSubMesh);
}
std::shared_ptr<MnSubMeshData> MnMeshData::GetSubMesh(UINT index)
{
	return m_lstSubMeshes[index];
}

UINT MnMeshData::GetNumSubMeshes() const
{
	return m_lstSubMeshes.size();
}

bool MnMeshData::HasBones()
{
	return m_hasBones;
}

void MnMeshData::SetSkeleton(const std::shared_ptr<MnSkeleton>& spSkeleton)
{
	if (spSkeleton != nullptr)
	{
		m_spSkeleton = spSkeleton;
		m_hasBones = true;
	}
}

std::shared_ptr<MnSkeleton> MnMeshData::GetSkeleton() const
{
	return m_spSkeleton;
}