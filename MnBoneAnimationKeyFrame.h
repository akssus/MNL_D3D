#pragma once

#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <string>
#include <vector>

namespace MNL
{
	struct MnBoneAnimationKey
	{
		std::string affectingBoneName;
		DirectX::SimpleMath::Vector3 keyPosition;
		DirectX::SimpleMath::Quaternion keyRotation;
		DirectX::SimpleMath::Vector3 keyScale;
	};

	class MnBoneAnimationKeyFrame
	{
	public:
		MnBoneAnimationKeyFrame();
		~MnBoneAnimationKeyFrame();

	public:
		double keyTime;
		/**
		keys' index and bones' index is 1:1 corresponding
		*/
		std::vector<MnBoneAnimationKey> keys;
	};
}