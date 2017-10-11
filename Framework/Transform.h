/**
@class Transform
@brief ���� ������ ���ϴ� ���� ������Ʈ ������Ʈ
@author Akssus
@section ����
���� ������Ʈ�� �⺻������ ������ ������Ʈ�μ� ������Ʈ�� ���������� ���Ѵ�.\n
������Ʈ�� ��Ī�� ��Ȯ���� ���� Mn ���λ簡 ���� �ʾҴ�.\n
ȸ������ degree�� �������� �Ѵ�.
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
		@brief ȸ�� ����: degree
		*/
		void SetRotation(float rotX, float rotY, float rotZ);
		void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
		/**
		@param axis ȸ����
		@param angle degreeȸ����
		*/
		void SetRotation(const DirectX::SimpleMath::Vector3& axis, float angle);

		void SetScale(float scaleX, float scaleY, float scaleZ);
		void SetScale(const DirectX::SimpleMath::Vector3& scale);
		void SetScaleX(float scaleX);
		void SetScaleY(float scaleY);
		void SetScaleZ(float scaleZ);

		/**
		@brief ���� ��ǥ�� ���簪�� ��ȯ�Ѵ�
		*/
		DirectX::SimpleMath::Vector3 Position() const;
		/**
		@brief ���� ȸ���� ���簪�� ��ȯ�Ѵ�.
		*/
		DirectX::SimpleMath::Quaternion Rotation() const;
		/**
		@brief ���� �������� ���簪�� ��ȯ�Ѵ�.
		*/
		DirectX::SimpleMath::Vector3 Scale() const;

		DirectX::SimpleMath::Matrix GetTranslationMatrix() const;
		DirectX::SimpleMath::Matrix GetRotationMatrix() const;
		DirectX::SimpleMath::Matrix GetScalingMatrix() const;
		/**
		@brief ������xȸ��x�̵� �� ���� ��ȯ ����� ��ȯ�Ѵ�.
		*/
		DirectX::SimpleMath::Matrix GetTransformMatrix() const;

		/**
		@brief �־��� ���͸�ŭ ��ġ�� ���Ѵ�
		*/
		void Translate(const DirectX::SimpleMath::Vector3 translation);
		/**
		@param angle degreeȸ����
		*/
		void Rotate(const DirectX::SimpleMath::Vector3& axis, float angle);
		/**
		@brief ȸ�� ���� : degree
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

		DirectX::SimpleMath::Matrix m_matTranslation; ///< �̸� ���� �̵����
		DirectX::SimpleMath::Matrix m_matRotation; ///< �̸� ���� ȸ�����
		DirectX::SimpleMath::Matrix m_matScaling; ///< �̸� ���� ���������
	};
}
