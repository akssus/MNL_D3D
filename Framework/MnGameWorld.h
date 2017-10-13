/**
@class MnGameWorld
@brief ���� ��� ������ �� ������Ʈ�� ����ϴ� ��ü
@author Akssus
@section ����
���� ����� �����ϸ�, ī�޶�, ����Ʈ, ���� ������Ʈ, ���̴��� ����� ������ �̸� ���� ����� �����Ѵ�.
*/


#pragma once
#include <map>
#include <memory>
#include "DXTK/SimpleMath.h"
#include "ShaderList.h"
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include "MnGameObject.h"
#include "Utility\MnIDAllocator.h"

namespace MNL
{
	class MnGameWorld
	{
	public:
		MnGameWorld();
		~MnGameWorld();


		virtual void OnInit();

		/**
		@brief ���� ������Ʈ�� �߰��Ѵ�.
		*/
		void AddComponent(const std::shared_ptr<MnWorldComponent>& spComponent);

		/**
		@brief �ش� ���� ������Ʈ�� ���´�.
		@param index �ش� ���� ������Ʈ�� ����Ʈ ���� �ε���
		@return ������Ʈ�� �������� ���� ��� nullptr ��ȯ
		*/
		template <class T>
		std::shared_ptr<T>& GetComponent();

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
		
		void SetScreenSize(float width, float height);
		void SetScreenSize(const DirectX::SimpleMath::Vector2& size);
		DirectX::SimpleMath::Vector2 GetScreenSize() const;
		
	private:
		void _Init();

	private:
		std::map<std::string, std::shared_ptr<MnWorldComponent>> m_tblComponents;
		std::map<int, std::shared_ptr<MnGameObject>> m_lstGameObjects; ///< id�� Ű�� ������Ʈ�� �߰��Ѵ�.
		MnIDAllocator m_idAllocator;
		float m_screenWidth;
		float m_screenHeight;
	};
}