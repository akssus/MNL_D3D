#pragma once
#include "Core\MnCustomVertexType.h"

namespace MNL
{
	class MnMeshVertexType : public MnCustomVertexType
	{
	public:
		static struct MnMeshVertexTypeStruct
		{
			float x, y, z;
			float nx, ny, nz;
			float tu, tv;
		};
	public:
		MnMeshVertexType();
		~MnMeshVertexType();
	};
}