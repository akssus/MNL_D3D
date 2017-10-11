/**
@class Renderer
@brief 렌더러 게임 오브젝트 컴포넌트의 베이스 클래스
@author Aksuss
@section 개요
렌더링에 필요한 셰이더, 라이트, 머테리얼, 텍스쳐 등 데이터를 세팅한다. \n
자원 공유를 위해 전부 포인터로 인수를 받는다. \n
아이러니하게도 렌더러 컴포넌트엔 MnRenderer 가 포함되지 않으며 이는 상속 클래스에서 Fixed로 구현한다.
*/

#pragma once
#include <memory>
#include <vector>
#include "MnWorldComponent.h"
#include "Render/MnRenderer.h"
#include "Render/MnMeshTextureCombination.h"
#include "Render/MnShaderPathInstance.h"
#include "Render/MnLightSource.h"
#include "Render/MnMaterial.h"

namespace MNL
{
	class Renderer : public MnWorldComponent
	{
	public:
		Renderer();
		virtual ~Renderer();


		/**
		@brief 게임 오브젝트의 메시를 렌더링한다. 메시가 존재하지 않거나 렌더러가 세팅되지 않았을 경우 아무일도 일어나지 않는다.
		@todo 즉각 렌더링보다 나중에 리스트에 넣어서 한번에 렌더하는 식으로 바꾸기
		*/
		virtual void Render() = 0;
	
		
	};
}
