#include "MnGenericVertexStruct.h"

using namespace MNL;

MnGenericVertexStruct::MnGenericVertexStruct()
{
	m_semantics.resize(MN_SEMANTICS_TOTAL);
}


MnGenericVertexStruct::~MnGenericVertexStruct()
{
}

DirectX::SimpleMath::Vector4& MnGenericVertexStruct::operator[](UINT index)
{
	return m_semantics[index];
}