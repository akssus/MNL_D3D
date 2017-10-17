/**
@class MnGameObjectComponenet
@brief ���� ������Ʈ�� �� ������Ʈ�� ���̽� Ŭ����
@author Akssus
@section ����
���� ������Ʈ�� ��ǥ, �޽�, ������ �� ���� ������Ʈ�� ���ɶ� ��ӵǴ� ���̽� Ŭ�����̴�. \n
������Ʈ ������ ���� ����ϴ� ��� GetComponent �� GameObject �޼ҵ带 �̿��� ȯ�� ������ �д´�.
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
		@brief ���� ������Ʈ Ŭ������ �̸��� ��ȯ�Ѵ�.
		*/
		std::string GetComponentName() const;

		/**
		@brief ������ ���ӿ�����Ʈ�κ��� �ٸ� ������Ʈ�� ���´�.
		@return �ش� ������Ʈ�� �������� ���� ��� nullptr �� ��ȯ�Ѵ�.
		*/
		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			assert(m_pAttatchedGameObject != nullptr);
			return m_pAttatchedGameObject->GetComponent<T>();
		}
		
		/**
		@brief ���� ������Ʈ�� ���ӿ�����Ʈ�� �ҼӵǾ� �ִ��� Ȯ���Ѵ�.
		*/
		bool IsAttatched() const;

	protected:
		/**
		@brief ���� ������ ���� ������Ʈ�� �����͸� ��ȯ�Ѵ�. 
		@return ������ ������Ʈ�� ���� �� nullptr ��ȯ
		*/
		const MnGameObject* GameObject() const;

	private:
		/**
		@brief ���ӿ�����Ʈ ������ �����Ѵ�.
		*/
		void _SetAttatchedGameObject(MnGameObject* pGameObject);

	private:
		MnGameObject* m_pAttatchedGameObject; ///< ������Ʈ �ʿ��� ���� ������Ʈ ������ ��� ���� ������
	};
}