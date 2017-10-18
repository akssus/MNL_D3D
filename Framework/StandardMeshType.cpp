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
	m_matTransform = spMeshData->GetTransform();
	m_name = spMeshData->GetName();
	m_spVertexBuffer = spMeshData->GetVertexBuffer();
	m_spIndexBuffer = spMeshData->GetIndexBuffer();

	//copy sub meshes
	m_subMeshes.assign(spMeshData->GetSubMeshes().begin(), spMeshData->GetSubMeshes().end());

	m_spSkeleton = std::make_shared<MnSkeleton>();
	//���̷����� ���� �Ұ��ϹǷ� ������ �޴´�.
	*m_spSkeleton = *(spMeshData->GetSkeleton());

	return S_OK;
}

const std::shared_ptr<MnSkeleton> StandardMeshType::GetSkeleton() const
{
	return m_spSkeleton;
}