#include "MnBone.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnBone::MnBone()
{
	ZeroMemory(&m_position, sizeof(Vector3));
	ZeroMemory(&m_rotation, sizeof(Quaternion));
	ZeroMemory(&m_scale, sizeof(Vector3));
	m_toBoneLocalMatrix = Matrix::Identity;
	m_transform = Matrix::Identity;
}


MnBone::~MnBone()
{
}

void MnBone::SetOffsetMatrix(const DirectX::SimpleMath::Matrix& offsetMatrix)
{
	m_toBoneLocalMatrix = offsetMatrix;
}
void MnBone::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}
void MnBone::SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
{
	m_rotation = rotation;
}
void MnBone::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
}
void MnBone::SetTransform(const DirectX::SimpleMath::Matrix& transform)
{
	m_transform = transform;
}

DirectX::SimpleMath::Matrix MnBone::GetTransform() const
{
	auto matTranslation = Matrix::CreateTranslation(m_position);
	auto matRotation = Matrix::CreateFromQuaternion(m_rotation);
	auto matScale = Matrix::CreateScale(m_scale);
	//m_transform = matScale * matRotation * matTranslation;

	return m_toBoneLocalMatrix * m_transform;
}
void MnBone::SetName(const std::string& name)
{
	m_name = name;
}

std::string MnBone::GetName() const
{
	return m_name;
}