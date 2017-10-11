/**
@class Transform
@brief 위상 정보를 지니는 게임 오브젝트 컴포넌트
@author Akssus
@section 개요
게임 오브젝트가 기본적으로 가지는 컴포넌트로서 오브젝트의 위상정보를 명세한다.\n
컴포넌트의 명칭의 명확성을 위해 Mn 접두사가 붙지 않았다.\n
회전값은 degree를 기준으로 한다.
*/

#pragma once
#include <d3d11.h>
#include <DXTK\SimpleMath.h>
#include "MnGameObjectComponent.h"

namespace MNL
{
	class Transform : public MnGameObjectComponent
	{
	public:
		Transform();
		~Transform();

		void SetPosition(float x, float y, float z);
		void SetPosition(const DirectX::SimpleMath::Vector3& position);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);

		/**
		@brief 회전 단위: degree
		*/
		void SetRotation(float rotX, float rotY, float rotZ);
		void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
		/**
		@param axis 회전축
		@param angle degree회전값
		*/
		void SetRotation(const DirectX::SimpleMath::Vector3& axis, float angle);

		void SetScale(float scaleX, float scaleY, float scaleZ);
		void SetScale(const DirectX::SimpleMath::Vector3& scale);
		void SetScaleX(float scaleX);
		void SetScaleY(float scaleY);
		void SetScaleZ(float scaleZ);

		/**
		@brief 현재 좌표의 복사값을 반환한다
		*/
		DirectX::SimpleMath::Vector3 Position() const;
		/**
		@brief 현재 회전의 복사값을 반환한다.
		*/
		DirectX::SimpleMath::Quaternion Rotation() const;
		/**
		@brief 현재 스케일의 복사값을 반환한다.
		*/
		DirectX::SimpleMath::Vector3 Scale() const;

		DirectX::SimpleMath::Matrix GetTranslationMatrix() const;
		DirectX::SimpleMath::Matrix GetRotationMatrix() const;
		DirectX::SimpleMath::Matrix GetScalingMatrix() const;
		/**
		@brief 스케일x회전x이동 의 로컬 변환 행렬을 반환한다.
		*/
		DirectX::SimpleMath::Matrix GetTransformMatrix() const;

		/**
		@brief 주어진 벡터만큼 위치에 더한다
		*/
		void Translate(const DirectX::SimpleMath::Vector3 translation);
		/**
		@param angle degree회전값
		*/
		void Rotate(const DirectX::SimpleMath::Vector3& axis, float angle);
		/**
		@brief 회전 단위 : degree
		*/
		void Rotate(float rotX, float rotY, float rotZ);
		void Rotate(const DirectX::SimpleMath::Quaternion rotation);

	private:
		void _CalcTranslation();
		void _CalcRotation();
		void _CalcScaling();

	private:
		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Quaternion m_rotation;
		DirectX::SimpleMath::Vector3 m_scale;

		DirectX::SimpleMath::Matrix m_matTranslation; ///< 미리 계산된 이동행렬
		DirectX::SimpleMath::Matrix m_matRotation; ///< 미리 계산된 회전행렬
		DirectX::SimpleMath::Matrix m_matScaling; ///< 미리 계산된 스케일행렬
	};
}
