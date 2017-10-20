/**
@class MNL::Sprite2D
@brief ȭ�鿡 ������� ǥ�õǴ� 2D ��������Ʈ ������ ���� ������Ʈ
@author AKssus
@section ����
Sprite2D �� ���� ���� ������Ʈ�� ���� �ؽ��İ� ������ �� ������ ���Ѵ�. \n
Sprite2DShader�� ���� Sprite2D ������Ʈ ��ü�� Texture ��ü�� �����Ǿ� Sprite2D�� x,y��ǥ, ũ��, ȸ������ ���� ȭ��� �������ȴ�.
Sprite2D ��ü�� ���� �޸� ���۸� ���� ���� ������ �׷��� ���������ο����� ��ȯ�� ���� ��ĸ��� �����Ѵ�.
@section ��ǥ��
Sprite2D�� ������ ��ũ�� �»���� (0,0) �̸� ���� ��ǥ��(-1,1)�� �ƴ� ��ũ�� ��ǥ��(0,screenWidth)�� �״�� ����Ѵ�.\n
��������Ʈ�� �ǹ��� �ؽ����� �»���� (0,0)�̴�.
*/

#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "MnGameObjectComponent.h"
#include "Core/MnVertexBuffer.h"
#include "Core/MnIndexBuffer.h"

namespace MNL
{
	struct Sprite2DData
	{
		float x, y;
		float width, height;
		float pivotX, pivotY;
		float angleDegree;
	};

	class Sprite2D : public MnGameObjectComponent
	{
	public:
		Sprite2D();
		~Sprite2D();

		void SetPosition(float x, float y);
		void SetPosition(const DirectX::SimpleMath::Vector2& position);

		void SetSize(float width, float height);
		void SetSize(const DirectX::SimpleMath::Vector2& size);

		void SetPivot(float x, float y);
		void SetPivot(const DirectX::SimpleMath::Vector2& pivot);

		/**
		@brief ��������Ʈ�� ȸ������ �����Ѵ�. ������ Degree.
		*/
		void SetAngle(float angleDegree);

		const Sprite2DData& GetData() const;
		
		const DirectX::SimpleMath::Matrix& GetTransform() const;
		
	private:
		void _CalcTransform();

	private:
		Sprite2DData m_data;
		DirectX::SimpleMath::Matrix m_transform;

	};
}