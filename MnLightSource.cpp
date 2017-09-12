#include "MnLightSource.h"

using namespace MNL;
using namespace DirectX::SimpleMath;

MnLightSource::MnLightSource()
{
	ZeroMemory(&m_position, sizeof(Vector3));
	ZeroMemory(&m_direction, sizeof(Vector3));
	m_lightType = MN_LIGHT_DIRECTIONAL;
}


MnLightSource::~MnLightSource()
{
}


void MnLightSource::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}
void MnLightSource::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
const DirectX::SimpleMath::Vector3& MnLightSource::GetPosition() const
{
	return m_position;
}

void MnLightSource::SetDirection(const DirectX::SimpleMath::Vector3& direction)
{
	m_direction = direction;
}
void MnLightSource::SetDirection(float x, float y, float z)
{
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;
}
const DirectX::SimpleMath::Vector3& MnLightSource::GetDirection() const
{
	return m_direction;
}

const MN_LIGHT_TYPE MnLightSource::GetLightType() const
{
	return m_lightType;
}