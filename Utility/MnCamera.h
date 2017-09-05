#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	class MnCamera
	{
	public:
		MnCamera();
		~MnCamera();

		void SetPosition(const DirectX::SimpleMath::Vector3& position);
		void SetOrientation(const DirectX::SimpleMath::Vector3& orientation);
		void SetUpVector(const DirectX::SimpleMath::Vector3& upVec);
		void LookAt(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& upVec);

		void SetFOV(float radFOV);
		void SetAspectRatio(float aspectRatio);
		void SetNearDistance(float near);
		void SetFarDistance(float far);

		void Rotate(const DirectX::SimpleMath::Quaternion& quat);
		void Rotate(const DirectX::SimpleMath::Vector3& axis, float rad);

		const DirectX::SimpleMath::Vector3& GetPosition() const;
		const DirectX::SimpleMath::Matrix& GetViewMatrix();
		const DirectX::SimpleMath::Matrix& GetProjectionMatrix();

	private:
		bool m_reCalculateView;
		bool m_reCalculateProjection;

		float m_fov;
		float m_aspectRatio;
		float m_near;
		float m_far;

		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Vector3 m_orientation;
		DirectX::SimpleMath::Vector3 m_upVector;

		DirectX::SimpleMath::Matrix m_matView;
		DirectX::SimpleMath::Matrix m_matProjection;
	};
}
