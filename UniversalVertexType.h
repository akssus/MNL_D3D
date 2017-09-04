#pragma once
#include "Core\MnCustomVertexType.h"

namespace MNL
{
	/*
	Universal vertex type.
	vertex shader must place IA semantics in right order
	this class is not part of MNL and it's only a sample implementation of making custom vertex type
	*/
	class UniversalVertexType : public MnCustomVertexType
	{
	public:
		UniversalVertexType();
		~UniversalVertexType();
	};
};