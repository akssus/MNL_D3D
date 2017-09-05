#include "MnCamera.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnCamera::MnCamera():m_fov(0.0f),m_aspectRatio(0.0f),m_near(0.0f),m_far(0.0f),m_reCalculateProjection(true),m_reCalculateView(true)
{
	ZeroMemory(&m_matProjection, sizeof(Matrix));
	ZeroMemory(&m_matView, sizeof(Matrix));
	ZeroMemory(&m_position, sizeof(Vector3));
	ZeroMemory(&m_orientation, sizeof(Vector3));
	ZeroMemory(&m_upVector, sizeof(Vector3));
}


MnCamera::~MnCamera()
{
}

void MnCamera::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}
void MnCamera::SetOrientation(const DirectX::SimpleMath::Vector3& orientation)
{
	m_orientation = orientation;
	m_reCalculateView = true;
}
void MnCamera::SetUpVector(const DirectX::SimpleMath::Vector3& upVec)
{
	m_upVector = upVec;
	m_reCalculateView = true;
}
void MnCamera::LookAt(const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& upVec)
{
	m_orientation = target - m_position;
	m_upVector = upVec;
	m_reCalculateView = true;
}
void MnCamera::SetFOV(float radFOV)
{
	m_fov = radFOV;
	m_reCalculateProjection = true;
}
void MnCamera::SetAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_reCalculateProjection = true;
}
void MnCamera::SetNearDistance(float nearDist)
{
	m_near = nearDist;
	m_reCalculateProjection = true;
}
void MnCamera::SetFarDistance(float farDist)
{
	m_far = farDist;
	m_reCalculateProjection = true;
}

void MnCamera::Rotate(const DirectX::SimpleMath::Quaternion& quat)
{
	m_orientation = Vector3::Transform(m_orientation,Matrix::CreateFromQuaternion(quat));
	m_reCalculateView = true;
}
void MnCamera::Rotate(const DirectX::SimpleMath::Vector3& axis, float rad)
{
	m_orientation = Vector3::Transform(m_orientation, Matrix::CreateFromAxisAngle(axis, rad));
	m_reCalculateView = true;
}

const DirectX::SimpleMath::Vector3& MnCamera::GetPosition() const
{
	return m_position;
}
const DirectX::SimpleMath::Matrix& MnCamera::GetViewMatrix()
{
	if (m_reCalculateView)
	{
		m_matView = Matrix::CreateLookAt(m_position, m_orientation, m_upVector);
		m_reCalculateView = false;
	}

	return m_matView;
}

const DirectX::SimpleMath::Matrix& MnCamera::GetProjectionMatrix() 
{
	if (m_reCalculateProjection)
	{
		m_matProjection = Matrix::CreatePerspectiveFieldOfView(m_fov,m_aspectRatio,m_near,m_far);
		m_reCalculateProjection = false;
	}
	return m_matProjection;
}