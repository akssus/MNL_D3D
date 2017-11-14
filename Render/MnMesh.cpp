#include "MnMesh.h"
#include "Core/MnLog.h"

using namespace MNL;

MnSubMesh::MnSubMesh()
{
	m_matTransform = DirectX::SimpleMath::Matrix::Identity;
}


MnSubMesh::~MnSubMesh()
{
}


HRESULT MnSubMesh::Init(const std::shared_ptr<MnSubMeshData> spSubMeshData)
{
	if (spSubMeshData == nullptr)
	{
		MnLog::MB_IsNull(MN_VAR_INFO(spSubMeshData));
		return E_FAIL;
	}

	m_matTransform = spSubMeshData->GetTransform();
	m_name = spSubMeshData->GetName();
	m_spVertexBuffer = spSubMeshData->GetVertexBuffer();
	m_spIndexBuffer = spSubMeshData->GetIndexBuffer();

	return S_OK;
}
void MnSubMesh::SetParent(const std::shared_ptr<MnSubMesh>& spMesh)
{
	m_spParent = spMesh;
}
std::shared_ptr<MnSubMesh> MnSubMesh::GetParent() const
{
	return m_spParent;
}
void MnSubMesh::SetTransform(const DirectX::SimpleMath::Matrix& matTransform)
{
	m_matTransform = matTransform;
}
const DirectX::SimpleMath::Matrix& MnSubMesh::GetTransform() const
{
	return m_matTransform;
}

void MnSubMesh::SetName(const std::string& name)
{
	m_name = name;
}
std::string MnSubMesh::GetName() const
{
	return m_name;
}

void MnSubMesh::SetVertexBuffer(const std::shared_ptr<MnVertexBuffer>& spVertexBuffer)
{
	m_spVertexBuffer = spVertexBuffer;
}
void MnSubMesh::SetIndexBuffer(const std::shared_ptr<MnIndexBuffer>& spIndexBuffer)
{
	m_spIndexBuffer = spIndexBuffer;
}

void MnSubMesh::SetSubMeshFragments(const std::vector<MnSubMeshFragment>& subMeshFragments)
{
	m_subMeshFragments.assign(subMeshFragments.begin(), subMeshFragments.end());
}
UINT MnSubMesh::GetNumSubMeshFragments() const
{
	return m_subMeshFragments.size();
}
const MnSubMeshFragment& MnSubMesh::GetSubMeshFragment(UINT index) const
{
	return m_subMeshFragments[index];
}
const CPD3DBuffer MnSubMesh::GetVertexBuffer() const
{
	return m_spVertexBuffer->GetBuffer();
}
UINT MnSubMesh::GetVertexBufferStride() const
{
	return m_spVertexBuffer->GetStride();
}
const CPD3DBuffer MnSubMesh::GetIndexBuffer() const
{
	return m_spIndexBuffer->GetBuffer();
}
UINT MnSubMesh::GetIndexCount() const
{
	return m_spIndexBuffer->GetIndexCount();
}
DXGI_FORMAT MnSubMesh::GetIndexBufferFormat() const
{
	return m_spIndexBuffer->GetFormat();
}

MnMesh::MnMesh():m_hasBones(false)
{

}
MnMesh::~MnMesh()
{

}

HRESULT MnMesh::Init(const std::shared_ptr<MnMeshData>& spMeshData)
{
	if (spMeshData == nullptr)
	{
		return E_FAIL;
	}
	
	for (int i = 0; i < spMeshData->GetNumSubMeshes();++i)
	{
		auto newSubMesh = std::make_shared<MnSubMesh>();
		auto subMeshData = spMeshData->GetSubMesh(i);
		newSubMesh->Init(subMeshData);
		AddSubMesh(newSubMesh);
	}
	if (spMeshData->HasBones())
	{
		m_hasBones = true;
		m_spSkeleton = std::make_shared<MnSkeleton>();
		//스켈레톤은 공유 불가하므로 복사해 받는다.
		*m_spSkeleton = *(spMeshData->GetSkeleton());
	}

	return S_OK;
}

void MnMesh::AddSubMesh(const std::shared_ptr<MnSubMesh>& spSubMesh)
{
	m_lstSubMeshes.push_back(spSubMesh);
}

std::shared_ptr<MnSubMesh> MnMesh::GetSubMesh(UINT index)
{
	return m_lstSubMeshes[index];
}

UINT MnMesh::GetNumSubMehses()
{
	return m_lstSubMeshes.size();
}

bool MnMesh::HasBones()
{
	return m_hasBones;
}
void MnMesh::SetSkeleton(const std::shared_ptr<MnSkeleton>& spSkeleton)
{
	m_spSkeleton = spSkeleton;
}

std::shared_ptr<MnSkeleton> MnMesh::GetSkeleton()
{
	return m_spSkeleton;
}
