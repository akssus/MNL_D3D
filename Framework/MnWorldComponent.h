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
		~MnWorldComponent();

		/**
		@brief ���� ������Ʈ Ŭ������ �̸��� ��ȯ�Ѵ�.
		*/
		std::string GetComponentName() const;

		/**
		@brief ������ ����κ��� �ٸ� ����������Ʈ�� ���´�.
		@return �ش� ������Ʈ�� �������� ���� ��� nullptr �� ��ȯ�Ѵ�.
		*/
		template <class T>
		std::shared_ptr<T> GetComponent();

	protected:
		/**
		@brief ���� ������ ���� ������ �����͸� ��ȯ�Ѵ�.
		@return ������ ���尡 ���� �� nullptr ��ȯ
		*/
		MnGameWorld* GameWorld() const;

	private:
		/**
		@brief ���� ������ �����Ѵ�.
		*/
		void _SetAttatchedWorld(MnGameWorld* pGameWorld);

	private:
		MnGameWorld* m_pAttatchedWorld;

	};

}