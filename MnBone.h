#pragma once
#include <d3d11.h>
#include <vector>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	/*
	A bone actually has no hirarchy. 
	The model format may has a parent-child relations but it is independent after reading models.
	This is identical only by it's name
	*/
	class MnBone
	{
	public:
		MnBone();
		~MnBone();

		void SetPosition(const DirectX::SimpleMath::Vector3& position);
		void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
		void SetScale(const DirectX::SimpleMath::Vector3& scale);
		/**
		Get bone's transformation from the mesh's local space.
		Notice that the transformation is NOT RELATIVE TO ITS PARENT
		*/
		DirectX::SimpleMath::Matrix GetTransform() const;

		void SetName(const std::string& name);
		std::string GetName() const;
	private:
		std::string m_name;
		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Quaternion m_rotation;
		DirectX::SimpleMath::Vector3 m_scale;
	};
}
