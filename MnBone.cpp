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
void MnBone::SetTransform(const DirectX::SimpleMath::Matrix& transform)
{
	m_transform = transform;
}

void MNL::MnBone::SetTransform(const DirectX::SimpleMath::Vector3 & position, const DirectX::SimpleMath::Quaternion & rotation, const DirectX::SimpleMath::Vector3 & scale)
{
	auto matTranslation = Matrix::CreateTranslation(position);
	auto matRotation = Matrix::CreateFromQuaternion(rotation);
	auto matScale = Matrix::CreateScale(scale);
	m_transform = matScale * matRotation * matTranslation;
}

DirectX::SimpleMath::Matrix MnBone::GetTransform() const
{
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