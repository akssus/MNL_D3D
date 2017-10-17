/**
@class MnGameObject
@brief ���� �� ������ ������ ���� ó�� �⺻�����μ� ���� ������Ʈ�� �������μ� ��üȭ�ȴ�.
@author Akssus
@section ����
���� ĳ����, ��, ī�޶�, ��������Ʈ ��� ���� �� ǥ�õǴ� ��ü���� ������ ǥ�õ��� �ʴ� ��ü�鵵 ���ӿ�����Ʈ�� ǥ���� �� �ִ�.\n
Update �޼ҵ带 ���� �������� ���� ����� ������ ���� ���� ������ ������ �����Ѵ�.\n
�� ������Ʈ���� GetComponent ���ø� �޼ҵ�� ���� �� �ְ� �� ������Ʈ�� Ŭ������ ���ڿ�ȭ �Ǿ� ���� map ���̺� �����Ǿ� �ִ�.
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
		@brief ������Ʈ�� �߰��Ѵ�.
		*/
		void AddComponent(const std::shared_ptr<MnGameObjectComponent>& spComponent);

		/**
		@brief ���� ������Ʈ ������Ʈ�� �����͸� ��ȯ�Ѵ�.
		@return �ش� ������Ʈ�� �������� ���� ��� nullptr �� ��ȯ�Ѵ�.
		*/ 
		template <class T>
		std::shared_ptr<T> GetComponent() const
		{
			std::string key = typeid(T).name();
			if (m_tblComponents.count(key) == 0)
			{
				return nullptr;
			}
			//�ٿ�ĳ���� ���н� �ڵ����� nullptr ��ȯ
			return std::dynamic_pointer_cast<T>(m_tblComponents.at(key));
		}
		
		/**
		@brief �з��� �ٿ뵵 �±� ����
		*/
		void SetTag(const std::string& tag);
		std::string GetTag() const;

		/**
		@brief ���ӿ�����Ʈ�� ���� �ĺ� ID�� �����Ѵ�.
		*/
		void SetID(UINT id);
		UINT GetID() const;
			
		/**
		@brief ���� ���ӿ�����Ʈ�� �Ҽӵ� ���� ������ �����͸� ��ȯ�Ѵ�.
		*/
		MnGameWorld* GameWorld() const;

	protected:
		void _SetGameWorld(MnGameWorld* pGameWorld);

	private:
		MnGameWorld* m_pGameWorld; ///< ���� �Ҽӵ� ���ӿ����� ������
		std::map<std::string, std::shared_ptr<MnGameObjectComponent>> m_tblComponents;
		std::string m_tag; ///< �ν��Ͻ� �ٿ뵵 �±�
		UINT m_id;

	};
}
