#include "Mesh.h"
#include "MnFramework.h"
#include "Core/MnLog.h"

using namespace MNL;

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::SetMesh(const std::shared_ptr<MnMeshData>& meshData)
{
	m_spMesh = std::make_shared<MnMesh>();
	HRESULT setResult = m_spMesh->Init(MnFramework::renderAPI.GetD3DDevice(), meshData);
	if (FAILED(setResult))
	{
		//�ʱ�ȭ ���н� �޸� ����
		MnLog::MB_InitFailed(MN_VAR_INFO(m_spMesh));
		m_spMesh.reset();
	}
}
const std::shared_ptr<MnMesh> Mesh::GetMesh() const
{
	return m_spMesh;
}

const std::shared_ptr<MnSkeleton> Mesh::GetSkeleton() const
{
	const MnSkinnedMesh* castedMesh = dynamic_cast<MnSkinnedMesh*>(m_spMesh.get());
	if (castedMesh == nullptr)
	{
		//ĳ���� ���� == �޽ð� ���ų� ��Ų��޽ð� �ƴ� ���
		return nullptr;
	}
	return castedMesh->GetSkeleton();
}