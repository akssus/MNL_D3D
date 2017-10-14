/**
@class MnGameWorld
@brief 게임 장면 렌더링 및 업데이트를 담당하는 객체
@author Akssus
@section 개요
게임 장면을 구현하며, 카메라, 라이트, 게임 오브젝트, 셰이더를 멤버로 가지고 이를 토대로 장면을 렌더한다.
*/


#pragma once
#include <map>
#include <memory>
#include <d3d11.h>
#include "DXTK/SimpleMath.h"
#include "MnWorldComponent.h"
#include "Render/MnCamera.h"
#include "Utility\MnIDAllocator.h"
#include "Renderer.h"
#include "MnGameObject.h"

namespace MNL
{
	class MnGameWorld
	{
	public:
		MnGameWorld();
		~MnGameWorld();


		virtual void OnInit();

		/**
		@brief 월드 컴포넌트를 추가한다.
		*/
		void AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent);

		/**
		@brief 해당 월드 컴포넌트를 얻어온다.
		@param index 해당 월드 컴포넌트의 리스트 중의 인덱스
		@return 컴포넌트가 존재하지 않을 경우 nullptr 반환
		*/
		template <class T>
		std::shared_ptr<T>& GetComponent() const;

		/**
		@brief 게임 오브젝트의 고유 식별 ID를 할당한다.
		*/
		int AllocateGameObjectID();

		/**
		@brief 현재 월드에 존재하는 게임 오브젝트 컨테이너를 가져온다.
		*/
		std::map<int, std::shared_ptr<MnGameObject>>& GetGameObjects();

		/**
		@brief 자동으로 id를 할당하여 게임오브젝트를 컨테이너에 추가한다.
		*/
		void AddGameObject(const std::shared_ptr<MnGameObject>& spGameObject);

		/**
		@brief 해당 id로 게임오브젝트를 컨테이너에 추가한다. id에 해당하는 오브젝트가 이미 존재하는 경우 덮어쓴다.
		*/
		void AddGameObject(const std::shared_ptr<MnGameObject>& spGameObject, int id);

		/**
		@brief 해당 id를 가진 게임오브젝트를 제거한다.
		*/
		void RemoveGameObject(int id);

		/**
		@brief 해당 id를 가진 게임오브젝트를 반환한다.
		*/
		std::shared_ptr<MnGameObject> GetGameObject(int id);

		/**
		@brief 해당 태그를 가진 게임 오브젝트 리스트를 반환한다.
		*/
		std::vector<std::shared_ptr<MnGameObject>> GetGameObjectsByTag(const std::string& tag) const;
		

		/**
		@brief 월드의 메인 카메라를 설정한다. 렌더링은 메인카메라를 기준으로 실행된다.
		*/
		void SetMainCamera(const std::shared_ptr<MnCamera>& spCamera);
		/**
		@brief 월드의 메인 카메라를 반환한다.
		@return 메인카메라가 존재하지 않을 경우 nullptr 반환
		*/
		const std::shared_ptr<MnCamera>& GetMainCamera() const;

		void SetScreenSize(float width, float height);
		void SetScreenSize(const DirectX::SimpleMath::Vector2& size);
		DirectX::SimpleMath::Vector2 GetScreenSize() const;
		
	private:
		void _Init();

	private:
		std::map<std::string, std::shared_ptr<MnWorldComponent>> m_tblComponents;
		std::map<int, std::shared_ptr<MnGameObject>> m_lstGameObjects; ///< id를 키로 오브젝트를 추가한다.
		MnIDAllocator m_idAllocator;

		std::shared_ptr<MnCamera> m_spMainCamera; ///< 최종 렌더링은 메인 카메라를 기준으로 렌더링된다.
		float m_screenWidth;
		float m_screenHeight;
	};
}