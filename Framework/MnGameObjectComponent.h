/**
@class MnGameObjectComponenet
@brief 게임 오브젝트의 각 컴포넌트의 베이스 클래스
@author Akssus
@section 개요
게임 오브젝트의 좌표, 메시, 렌더러 등 각종 컴포넌트로 사용될때 상속되는 베이스 클래스이다. \n
컴포넌트 구현을 위해 상속하는 경우 GetComponent 및 GameObject 메소드를 이용해 환경 정보를 읽는다.
*/

#pragma once
#include <d3d11.h>
#include <memory>
#include <string>
#include <cassert>


namespace MNL
{
	class MnGameObject;
	class MnGameWorld;
	
	class MnGameObjectComponent
	{
		friend class MnGameObject;
	public:
		MnGameObjectComponent();
		virtual ~MnGameObjectComponent();

		/**
		@brief 현재 컴포넌트 클래스의 이름을 반환한다.
		*/
		std::string GetComponentName() const;

		/**
		@brief 참조된 게임오브젝트로부터 다른 컴포넌트를 얻어온다.
		@return 해당 컴포넌트가 존재하지 않을 경우 nullptr 을 반환한다.
		*/
		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			assert(m_pAttatchedGameObject != nullptr);
			return m_pAttatchedGameObject->GetComponent<T>();
		}
		
		/**
		@brief 현재 컴포넌트가 게임오브젝트에 소속되어 있는지 확인한다.
		*/
		bool IsAttatched() const;

	protected:
		/**
		@brief 현재 참조된 게임 오브젝트의 포인터를 반환한다. 
		@return 참조된 오브젝트가 없을 시 nullptr 반환
		*/
		const MnGameObject* GameObject() const;

	private:
		/**
		@brief 게임오브젝트 참조를 설정한다.
		*/
		void _SetAttatchedGameObject(MnGameObject* pGameObject);

	private:
		MnGameObject* m_pAttatchedGameObject; ///< 컴포넌트 쪽에서 게임 오브젝트 정보를 얻기 위한 포인터
	};
}