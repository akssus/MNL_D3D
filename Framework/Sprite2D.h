/**
@class MNL::Sprite2D
@brief 화면에 평면으로 표시되는 2D 스프라이트 정보를 담은 컴포넌트
@author AKssus
@section 개요
Sprite2D 는 현재 게임 오브젝트가 가진 텍스쳐가 렌더링 될 공간을 명세한다. \n
Sprite2DShader에 의해 Sprite2D 컴포넌트 객체와 Texture 객체가 참조되어 Sprite2D의 x,y좌표, 크기, 회전값에 따라 화면상에 렌더링된다.
Sprite2D 자체는 따로 메모리 버퍼를 갖고 있지 않으며 그래픽 파이프라인에서의 변환을 위한 행렬만을 제공한다.
@section 좌표계
Sprite2D의 원점은 스크린 좌상단이 (0,0) 이며 투영 좌표계(-1,1)가 아닌 스크린 좌표계(0,screenWidth)를 그대로 사용한다.\n
스프라이트의 피벗은 텍스쳐의 좌상단이 (0,0)이다.
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
		@brief 스프라이트의 회전값을 설정한다. 단위는 Degree.
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