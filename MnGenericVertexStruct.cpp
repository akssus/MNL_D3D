#include "MnGenericVertexStruct.h"

using namespace MNL;

MnGenericVertexStruct::MnGenericVertexStruct()
{
	m_semantics.resize(MN_SEMANTICS_TOTAL);
}


MnGenericVertexStruct::~MnGenericVertexStruct()
{
}

const DirectX::SimpleMath::Vector4& MnGenericVertexStruct::operator[](MN_SEMANTICS semantic) const
{
	return m_semantics[semantic];
}
const DirectX::SimpleMath::Vector4& MnGenericVertexStruct::Get(MN_SEMANTICS semantic) const
{
	return m_semantics[semantic];
}
DirectX::SimpleMath::Vector4& MnGenericVertexStruct::operator[](MN_SEMANTICS semantic)
{
	return m_semantics[semantic];
}
DirectX::SimpleMath::Vector4& MnGenericVertexStruct::Get(MN_SEMANTICS semantic)
{
	return m_semantics[semantic];
}