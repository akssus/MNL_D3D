#pragma once

#include <d3d11.h>
#include <string>

namespace MNL
{
	class MnBoneAnimationKeyFrame
	{
	public:
		MnBoneAnimationKeyFrame();
		~MnBoneAnimationKeyFrame();

	public:
		std::string affectingMeshName;

	};
}