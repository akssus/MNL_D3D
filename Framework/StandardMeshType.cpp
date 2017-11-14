#include "Framework\StandardMeshType.h"
#include "Core/MnLog.h"

using namespace MNL;


StandardMeshType::StandardMeshType()
{
}


StandardMeshType::~StandardMeshType()
{
}



HRESULT StandardMeshType::Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData)
{
	if (spMeshData == nullptr)
	{
		MnLog::MB_IsNull(MN_VAR_INFO(spMeshData));
		return E_FAIL;
	}
	for (int i = 0; i < spMeshData->GetNumSubMeshes(); ++i)
	{
		auto subMeshData = spMeshData->GetSubMesh(i);
		auto subMesh = std::make_shared<MnSubMesh>();
		subMesh->SetTransform(subMeshData->GetTransform());
		subMesh->SetName(subMeshData->GetName());
		subMesh->SetVertexBuffer(subMeshData->GetVertexBuffer());
		subMesh->SetIndexBuffer(subMeshData->GetIndexBuffer());
		subMesh->SetSubMeshFragments(subMeshData->GetSubMeshFragments());

		this->AddSubMesh(subMesh);
	}
	m_spSkeleton = std::make_shared<MnSkeleton>();
	//스켈레톤은 공유 불가하므로 복사해 받는다.
	*m_spSkeleton = *(spMeshData->GetSkeleton());

	return S_OK;
}

const std::shared_ptr<MnSkeleton> StandardMeshType::GetSkeleton() const
{
	return m_spSkeleton;
}