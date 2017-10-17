#pragma once
#include <string>
#include <memory>

namespace MNL
{
	class MnWorldComponent
	{
		friend class MnGameWorld;
	public:
		MnWorldComponent();
		virtual ~MnWorldComponent();

		/**
		@brief 현재 컴포넌트 클래스의 이름을 반환한다.
		*/
		std::string GetComponentName() const;

		/**
		@brief 참조된 월드로부터 다른 월드컴포넌트를 얻어온다.
		@return 해당 컴포넌트가 존재하지 않을 경우 nullptr 을 반환한다.
		*/
		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			assert(m_pAttatchedWorld != nullptr);
			return m_pAttatchedWorld->GetComponent<T>();
		}

	protected:
		/**
		@brief 현재 참조된 게임 월드의 포인터를 반환한다.
		@return 참조된 월드가 없을 시 nullptr 반환
		*/
		MnGameWorld* GameWorld() const;

	private:
		/**
		@brief 월드 참조를 설정한다.
		*/
		void _SetAttatchedWorld(MnGameWorld* pGameWorld);

	private:
		MnGameWorld* m_pAttatchedWorld;

	};

}