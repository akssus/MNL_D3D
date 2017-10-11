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
		@brief ���� ������Ʈ�� �߰��Ѵ�.
		*/
		void AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent);

		/**
		@brief �ش� ������Ʈ�� ���´�.
		@return ������Ʈ�� �������� ���� ��� nullptr ��ȯ
		*/
		template <class T>
		std::shared_ptr<T> GetComponent();
		
	private:
		std::map<std::string, std::shared_ptr<MnWorldComponent>> m_tblComponents;
	};
}