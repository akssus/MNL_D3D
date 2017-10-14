/**
@class Renderer
@brief 렌더러 게임 오브젝트 컴포넌트의 베이스 클래스
@author Aksuss
@section 개요
셰이더가 렌더한 렌더타겟을 최종적으로 백버퍼로 넘기는 역할을 담당.\n
화면에 후처리 이펙트가 필요한 경우 렌더러에서 처리. 예) 로우필터패스 등 \n
셰이더에 종속적인 이펙트는 셰이더에서 처리하는게 좋고, 렌더러에서의 이펙트는 화면 전체가 범위일 경우 쓰는편이 좋다.
*/

#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <memory>
#include <vector>
#include "MnWorldComponent.h"
#include "Render/MnRenderWindow.h"
#include "Render/MnRenderer.h"
#include "Render/MnMeshTextureCombination.h"
#include "Render/MnShaderPathInstance.h"
#include "Render/MnLightSource.h"
#include "Render/MnMaterial.h"
#include "Render/MnSkeleton.h"
#include "Render/MnCustomRenderTarget.h"

namespace MNL
{
	class Renderer : public MnWorldComponent
	{
		struct _BackBufferShaderVertex
		{
			DirectX::SimpleMath::Vector3 position;
		};
	public:
		Renderer();
		~Renderer();

		/**
		@brief 해당 렌더 윈도우에 씬을 렌더링한다.
		@param pRenderWindow 씬이 렌더링 될 렌더 윈도우
		*/
		void Render(const MnRenderWindow& renderWindow);
	
	private:
		void _Init();
		void _RenderToBackBuffer(const std::shared_ptr<MnCustomRenderTarget>& spRenderTarget, const MnRenderWindow& renderWindow);
		
	private:
		MnShaderPathInstance m_backBufferShader;
		MnVertexBuffer m_vertexBuffer;
		MnInputLayout m_inputLayout;
		MnIndexBuffer m_indexBuffer;
	};
}
