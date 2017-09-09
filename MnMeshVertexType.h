#pragma once
#include "Core\MnCustomVertexType.h"

namespace MNL
{
	struct MnMeshVertexTypeStruct
	{
		float x, y, z;
		float nx, ny, nz;
		float tu, tv;
		float t2u, t2v;
	};
	class MnMeshVertexType : public MnCustomVertexType
	{
	public:
		MnMeshVertexType();
		~MnMeshVertexType();
	};
}