#include "Framework\Sprite2D.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

Sprite2D::Sprite2D()
{
	ZeroMemory(&m_data, sizeof(Sprite2DData));
	ZeroMemory(&m_transform, sizeof(Matrix));
}


Sprite2D::~Sprite2D()
{
}


void Sprite2D::SetPosition(float x, float y)
{
	m_data.x = x;
	m_data.y = y;
	_CalcTransform();
}
void Sprite2D::SetPosition(const DirectX::SimpleMath::Vector2& position)
{
	m_data.x = position.x;
	m_data.y = position.y;
	_CalcTransform();
}

void Sprite2D::SetSize(float width, float height)
{
	m_data.width = width;
	m_data.height = height;
	_CalcTransform();
}
void Sprite2D::SetSize(const DirectX::SimpleMath::Vector2& size)
{
	m_data.width = size.x;
	m_data.height = size.y;
	_CalcTransform();
}

void Sprite2D::SetPivot(float x, float y)
{
	m_data.pivotX = x;
	m_data.pivotY = y;
	_CalcTransform();
}
void Sprite2D::SetPivot(const DirectX::SimpleMath::Vector2& pivot)
{
	m_data.pivotX = pivot.x;
	m_data.pivotY = pivot.y;
	_CalcTransform();
}

void Sprite2D::SetAngle(float angleDegree)
{
	m_data.angleDegree = angleDegree;
	_CalcTransform();
}

const Sprite2DData& Sprite2D::GetData() const
{
	return m_data;
}

const DirectX::SimpleMath::Matrix& Sprite2D::GetTransform() const
{
	return m_transform;
}

void Sprite2D::_CalcTransform()
{
	Matrix pivot = Matrix::CreateTranslation(m_data.pivotX, m_data.pivotY, 0.0f);
	Matrix translation = Matrix::CreateTranslation(m_data.x, m_data.y, 0.0f);
	Matrix rotation = Matrix::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), DirectX::XMConvertToRadians(m_data.angleDegree));
	Matrix scale = Matrix::CreateScale(m_data.width, m_data.height, 1.0f);
	m_transform = ((scale * pivot) * rotation) * translation;
}