#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <map>
#include <vector>

namespace MNL
{
	enum MN_SEMANTICS
	{
		MN_SEMANTICS_POSITION0,
		MN_SEMANTICS_POSITION1,
		MN_SEMANTICS_COLOR0,
		MN_SEMANTICS_COLOR1,
		MN_SEMANTICS_NORMAL0,
		MN_SEMANTICS_NORMAL1,
		MN_SEMANTICS_TEXCOORD0,
		MN_SEMANTICS_TEXCOORD1,
		MN_SEMANTICS_TEXCOORD2,
		MN_SEMANTICS_TEXCOORD3,
		MN_SEMANTICS_TOTAL
	};

	class MnGenericVertexStruct
	{
	public:
		MnGenericVertexStruct();
		~MnGenericVertexStruct();

		DirectX::SimpleMath::Vector4& operator[](UINT index);

	private:
		std::vector<DirectX::SimpleMath::Vector4> m_semantics;
	};

	typedef std::vector<MnGenericVertexStruct> MnGenericVertexContainer;
}