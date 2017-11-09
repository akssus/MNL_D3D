/**
@class MnGameWorld
@brief ���� ��� ������ �� ������Ʈ�� ����ϴ� ��ü
@author Akssus
@section ����
���� ����� �����ϸ�, ī�޶�, ����Ʈ, ���� ������Ʈ, ���̴��� ����� ������ �̸� ���� ����� �����Ѵ�.\n
����Ƽ�� ġ�� ��?
*/


#pragma once
#include <map>
#include <memory>
#include <d3d11.h>
#include "DXTK/SimpleMath.h"
#include "MnWorldComponent.h"
#include "Render/MnCamera.h"
#include "Utility\MnIDAllocator.h"
#include "Utility\MnTimer.h"
#include "MnGameObject.h"

namespace MNL
{
	class MnGameWorld
	{
	public:
		MnGameWorld();
		~MnGameWorld();


	public:
		/**
		@brief �� ������ ����. �������̵尡 �Ұ��ϸ� OnUpdate()�� ȣ���Ѵ�.
		*/
		virtual void Update() final;

	protected:
		virtual void OnInit();
		virtual void OnUpdate();


	public:
		/**
		@brief ���� ������Ʈ�� �߰��Ѵ�. ����: �⺻ ���� ������Ʈ�� MnGameWorld �ʱ�ȭ�ɶ� �ڵ����� �߰���.
		*/
		void AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent);

		/**
		@brief �ش� ���� ������Ʈ�� ���´�.
		@param index �ش� ���� ������Ʈ�� ����Ʈ ���� �ε���
		@return ������Ʈ�� �������� ���� ��� nullptr ��ȯ
		*/
		template <class T>
		std::shared_ptr<T> GetComponent() const
		{
			std::string key = typeid(T).name();
			if (m_tblComponents.count(key) == 0)
			{
				return std::shared_ptr<T>(nullptr);
			}
			return std::dynamic_pointer_cast<T>(m_tblComponents.at(key));
		}

		/**
		@brief ���� ������Ʈ�� ���� �ĺ� ID�� �Ҵ��Ѵ�.
		*/
		int AllocateGameObjectID();

		/**
		@brief ���� ���忡 �����ϴ� ���� ������Ʈ �����̳ʸ� �����´�.
		*/
		std::map<int, std::shared_ptr<MnGameObject>>& GetGameObjects();

		/**
		@brief �ڵ����� id�� �Ҵ��Ͽ� ���ӿ�����Ʈ�� �����̳ʿ� �߰��Ѵ�.
		*/
		void AddGameObject(const std::shared_ptr<MnGameObject>& spGameObject);

		/**
		@brief �ش� id�� ���ӿ�����Ʈ�� �����̳ʿ� �߰��Ѵ�. id�� �ش��ϴ� ������Ʈ�� �̹� �����ϴ� ��� �����.
		*/
		void AddGameObject(const std::shared_ptr<MnGameObject>& spGameObject, int id);

		/**
		@brief �ش� id�� ���� ���ӿ�����Ʈ�� �����Ѵ�.
		*/
		void RemoveGameObject(int id);

		/**
		@brief �ش� id�� ���� ���ӿ�����Ʈ�� ��ȯ�Ѵ�.
		*/
		std::shared_ptr<MnGameObject> GetGameObject(int id);

		/**
		@brief �ش� �±׸� ���� ���� ������Ʈ ����Ʈ�� ��ȯ�Ѵ�.
		*/
		std::vector<std::shared_ptr<MnGameObject>> GetGameObjectsByTag(const std::string& tag) const;
		

		/**
		@brief ������ ���� ī�޶� �����Ѵ�. �������� ����ī�޶� �������� ����ȴ�.
		*/
		void SetMainCamera(const std::shared_ptr<MnCamera>& spCamera);

		/**
		@brief ������ ���� ī�޶� ��ȯ�Ѵ�.
		@return ����ī�޶� �������� ���� ��� nullptr ��ȯ
		*/
		const std::shared_ptr<MnCamera>& GetMainCamera() const;

		void SetScreenSize(float width, float height);
		void SetScreenSize(const DirectX::SimpleMath::Vector2& size);
		DirectX::SimpleMath::Vector2 GetScreenSize() const;
		
	private:
		void _Init();

	private:
		std::map<std::string, std::shared_ptr<MnWorldComponent>> m_tblComponents;
		std::map<int, std::shared_ptr<MnGameObject>> m_lstGameObjects; ///< id�� Ű�� ������Ʈ�� �߰��Ѵ�.
		MnIDAllocator m_idAllocator;

		std::shared_ptr<MnCamera> m_spMainCamera; ///< ���� �������� ���� ī�޶� �������� �������ȴ�.
		
		float m_screenWidth;
		float m_screenHeight;

	};
}