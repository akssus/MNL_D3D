#include "Transform.h"

using namespace MNL;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Transform::Transform():
	m_position(Vector3(0.0f,0.0f,0.0f)),
	m_rotation(Quaternion(0.0f,0.0f,0.0f,0.0f)),
	m_scale(Vector3(0.0f,0.0f,0.0f)),
	m_matTranslation(Matrix::Identity),
	m_matRotation(Matrix::Identity),
	m_matScaling(Matrix::Identity)
{
}


Transform::~Transform()
{
}


void Transform::SetPosition(float x, float y, float z)
{
	m_position = Vector3(x, y, z);
	_CalcTranslation();
}
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	_CalcTranslation();
}
void Transform::SetPositionX(float x)
{
	m_position.x = x;
	_CalcTranslation();
}
void Transform::SetPositionY(float y)
{
	m_position.y = y;
	_CalcTranslation();
}
void Transform::SetPositionZ(float z)
{
	m_position.z = z;
	_CalcTranslation();
}

void Transform::SetRotation(float rotX, float rotY, float rotZ)
{
	m_rotation = Quaternion::CreateFromYawPitchRoll(XMConvertToRadians(rotX), XMConvertToRadians(rotY), XMConvertToRadians(rotZ));
	_CalcRotation();
}
void Transform::SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
{
	m_rotation = rotation;
	_CalcRotation();
}

void Transform::SetRotation(const DirectX::SimpleMath::Vector3& axis, float angle)
{
	m_rotation = Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(angle));
	_CalcRotation();
}

void Transform::SetScale(float scaleX, float scaleY, float scaleZ)
{
	m_scale = Vector3(scaleX, scaleY, scaleZ);
	_CalcScaling();
}
void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	_CalcScaling();
}
void Transform::SetScaleX(float scaleX)
{
	m_scale.x = scaleX;
	_CalcScaling();
}
void Transform::SetScaleY(float scaleY)
{
	m_scale.y = scaleY;
	_CalcScaling();
}
void Transform::SetScaleZ(float scaleZ)
{
	m_scale.z = scaleZ;
	_CalcScaling();
}


DirectX::SimpleMath::Vector3 Transform::Position() const
{
	return m_position;
}

DirectX::SimpleMath::Quaternion Transform::Rotation() const
{
	return m_rotation;
}

DirectX::SimpleMath::Vector3 Transform::Scale() const
{
	return m_scale;
}

DirectX::SimpleMath::Matrix Transform::GetTranslationMatrix() const
{
	return m_matTranslation;
};
DirectX::SimpleMath::Matrix Transform::GetRotationMatrix() const
{
	return m_matRotation;
}
DirectX::SimpleMath::Matrix Transform::GetScalingMatrix() const
{
	return m_matScaling;
}

DirectX::SimpleMath::Matrix Transform::GetTransformMatrix() const
{
	return (m_matScaling * m_matRotation) * m_matTranslation;
}
void Transform::Translate(const DirectX::SimpleMath::Vector3 translation)
{
	m_position += translation;
	_CalcTranslation();
}
void Transform::Rotate(const DirectX::SimpleMath::Vector3& axis, float angle)
{
	m_rotation = Quaternion::Concatenate(m_rotation, Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(angle)));
	_CalcRotation();
}
void Transform::Rotate(float rotX, float rotY, float rotZ)
{
	m_rotation = Quaternion::Concatenate(m_rotation, Quaternion::CreateFromYawPitchRoll(XMConvertToRadians(rotX), XMConvertToRadians(rotY), XMConvertToRadians(rotZ)));
	_CalcRotation();
}
void Transform::Rotate(const DirectX::SimpleMath::Quaternion rotation)
{
	m_rotation = Quaternion::Concatenate(m_rotation, rotation);
	_CalcRotation();
}

void Transform::_CalcTranslation()
{
	m_matTranslation = Matrix::CreateTranslation(m_position);
}
void Transform::_CalcRotation()
{
	m_matRotation = Matrix::CreateFromQuaternion(m_rotation);
}
void Transform::_CalcScaling()
{
	m_matScaling = Matrix::CreateScale(m_scale);
}