#pragma once
#include <map>
#include "MnWorldComponent.h"

namespace MNL
{
	class MnGameWorld
	{
	public:
		MnGameWorld();
		~MnGameWorld();
		
		/**
		@brief 월드 컴포넌트를 추가한다.
		*/
		void AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent);

		/**
		@brief 해당 컴포넌트를 얻어온다.
		@return 컴포넌트가 존재하지 않을 경우 nullptr 반환
		*/
		template <class T>
		std::shared_ptr<T> GetComponent();
		
	private:
		std::map<std::string, std::shared_ptr<MnWorldComponent>> m_tblComponents;
	};
}