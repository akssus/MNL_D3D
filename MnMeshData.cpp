#include "MnMeshData.h"

using namespace MNL;

MnMeshData::MnMeshData():m_spParentIndex(nullptr),m_hasBone(false)
{

}


MnMeshData::~MnMeshData()
{
}


void MnMeshData::AddVertex(const MnGenericVertexStruct& vertex)
{
	m_lstVertices.push_back(vertex);
}
void MnMeshData::AddSubMesh(const MnSubMeshData& submesh)
{
	m_lstSubMeshes.push_back(submesh);
}
void MnMeshData::SetName(const std::string& name)
{
	m_meshName = name;
}

void MnMeshData::SetParentIndex(UINT index)
{
	m_spParentIndex = std::make_shared<UINT>(index);
}
bool MnMeshData::HasBone() const
{
	return m_hasBone;
}
const MnGenericVertexStruct&  MnMeshData::GetVertex(UINT index) const
{
	return m_lstVertices[index];
}
UINT MnMeshData::GetNumVertices() const
{
	return m_lstVertices.size();
}
const std::string& MnMeshData::GetName() const
{
	return m_meshName;
}
std::shared_ptr<UINT> MnMeshData::GetParentIndex() const
{
	return m_spParentIndex;
}
UINT MnMeshData::GetNumSubMeshes() const
{
	return m_lstSubMeshes.size();
}
const MnSubMeshData& MnMeshData::GetSubMesh(UINT index) const
{
	return m_lstSubMeshes[index];
}