#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	enum MN_LIGHT_TYPE
	{
		MN_LIGHT_DIRECTIONAL,
		MN_LIGHT_POINT,
	};
	class MnLightSource
	{
	public:
		MnLightSource();
		~MnLightSource();
		
		void SetPosition(const DirectX::SimpleMath::Vector3& position);
		void SetPosition(float x, float y, float z);
		const DirectX::SimpleMath::Vector3& GetPosition() const;

		void SetDirection(const DirectX::SimpleMath::Vector3& direction);
		void SetDirection(float x, float y, float z);
		const DirectX::SimpleMath::Vector3& GetDirection() const;

		const MN_LIGHT_TYPE GetLightType() const;

	private:
		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Vector3 m_direction;
		MN_LIGHT_TYPE m_lightType;
	};
}
