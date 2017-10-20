/**
@class Shader
@brief 상수버퍼 갱신과 셰이더가 적용된 드로우콜을 실시하는 컴포넌트
@author Akssus
@section 개요
셰이더의 책임은 많다. \n
첫째로 월드에서 정보를 얻어와 상수버퍼를 업데이트 해줘야 한다. 구체적인 내용은 상속해서 구현해야 한다. \n
둘째로 MnShaderPath 를 이용해 큐에 추가된 오브젝트들에 대해 렌더링을 실시한다. \n
마지막으로 최종 렌더링 결과를 텍스쳐로서 제공하여 다음 셰이더 혹은 렌더러에서 이펙트를 적용할 수 있다. \n
여러개의 셰이더는 월드 내에서 렌더링 우선순위가 존재한다. 예) 디퍼드셰이딩 -> 워터셰이딩 -> 블러셰이딩 -> 2D셰이딩 \n
전 렌더링의 결과 위에 적용하기 위해 전 단계에 실행된 렌더타겟뷰는 다음 셰이더에게 넘겨진다. 이를 사용할지 안할지는 다음 셰이더의 책임. \n
셰이더를 상속하여 구체화 할 때 최종 렌더 결과를 m_renderedScene 에 출력해줘야 한다. (필수)
*/
#pragma once
#include <memory>
#include <list>
#include "Core/MnTypedefs.h"
#include "Render/MnMesh.h"
#include "Render/MnCustomRenderTarget.h"
#include "MnGameObject.h"


namespace MNL
{
	class MnGameWorld;
	class ShaderList;

	class Shader
	{
		friend ShaderList;
	public:
		Shader();
		virtual ~Shader();
		
		/**
		@brief 셰이더 리스트에 추가 되었을때(인스턴스화 되었을때) 발생하는 이벤트
		*/
		virtual void OnAttatched();

	public:
		void AddObjectsToQueue(const std::shared_ptr<MnGameObject>& spObject);
		
		/**
		@brief 최종 렌더 타겟을 반환한다.
		@return 렌더가 실패했거나 아직 렌더되지 않았을 경우 nullptr을 반환한다. 디폴트 값으로 내부 렌더 타겟을 반환하지만 SetFinalRenderTarget을 호출하여 변경 가능
		*/
		std::shared_ptr<MnCustomRenderTarget> GetFinalRenderTarget() const;

		/**
		@brief 큐에 있는 오브젝트들을 해당 셰이더로 렌더한다. 렌더 후 큐는 비워져야 한다.
		@param prevRendererdScene 전 셰이더 단계에서 출력된 결과물. 사용여부는 구현에 따라 다르다.
		*/
		virtual void Render(const std::shared_ptr<MnCustomRenderTarget>& prevRenderedScene) = 0;

		void SetID(int id);
		int GetID() const;

	protected:
		void _ClearQueue();
		MnGameWorld* _GameWorld() const;

		/**
		@brief MnMesh 를 드로우콜 하는 헬퍼 메소드
		*/
		void _RenderMesh(const std::shared_ptr<MnMesh> mesh);

	private:
		virtual void _Init(MnGameWorld* pWorld);
		void _SetGameWorld(MnGameWorld* pWorld);

	protected:
		std::list<std::shared_ptr<MnGameObject>> m_renderQueue;

	private:
		MnGameWorld* m_pWorld;
		int m_id;

		std::shared_ptr<MnCustomRenderTarget> m_spFinalRenderTarget;
	};
}
