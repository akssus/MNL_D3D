/**
@class MnGameObject
@brief 게임 내 독립적 로직을 가진 처리 기본단위로서 각종 컴포넌트를 가짐으로서 구체화된다.
@author Akssus
@section 개요
게임 캐릭터, 맵, 카메라, 스프라이트 등등 게임 내 표시되는 개체들을 포함해 표시되지 않는 개체들도 게임오브젝트로 표현될 수 있다.\n
Update 메소드를 통해 독립적인 로직 모듈을 가지며 게임 루프 내에서 로직을 수행한다.\n
각 컴포넌트들은 GetComponent 템플릿 메소드로 구할 수 있고 각 컴포넌트의 클래스는 문자열화 되어 내부 map 테이블에 보관되어 있다.
*/

#pragma once
#include <d3d11.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <string>
#include "MnGameObjectComponent.h"

namespace MNL
{
	class MnGameWorld;

	class MnGameObject
	{
		friend MnGameWorld;
	public:
		MnGameObject();
		virtual ~MnGameObject();		

		/**
		@brief 컴포넌트를 추가한다.
		*/
		void AddComponent(const std::shared_ptr<MnGameObjectComponent>& spComponent);

		/**
		@brief 게임 오브젝트 컴포넌트의 포인터를 반환한다.
		@return 해당 컴포넌트가 존재하지 않을 경우 nullptr 을 반환한다.
		*/ 
		template <class T>
		std::shared_ptr<T> GetComponent() const
		{
			std::string key = typeid(T).name();
			if (m_tblComponents.count(key) == 0)
			{
				return nullptr;
			}
			//다운캐스팅 실패시 자동으로 nullptr 반환
			return std::dynamic_pointer_cast<T>(m_tblComponents.at(key));
		}
		
		/**
		@brief 분류용 다용도 태그 설정
		*/
		void SetTag(const std::string& tag);
		std::string GetTag() const;

		/**
		@brief 게임오브젝트의 고유 식별 ID를 설정한다.
		*/
		void SetID(UINT id);
		UINT GetID() const;
			
		/**
		@brief 현재 게임오브젝트가 소속된 게임 월드의 포인터를 반환한다.
		*/
		MnGameWorld* GameWorld() const;

	protected:
		void _SetGameWorld(MnGameWorld* pGameWorld);

	private:
		MnGameWorld* m_pGameWorld; ///< 현재 소속된 게임월드의 포인터
		std::map<std::string, std::shared_ptr<MnGameObjectComponent>> m_tblComponents;
		std::string m_tag; ///< 인스턴스 다용도 태그
		UINT m_id;

	};
}
