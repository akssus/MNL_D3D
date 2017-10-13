/**
@class ShaderList
@brief �ټ��� ���̴��� ���� ������Ʈ
@author Akssus
@section ����
���̴����� ������ ������Ʈ. ���̴� �߰� �� ���������� � ���̴����� �������� ������ ������� �Ѵ�.\n
�̴� SetRenderOrder �� �̿��� ���� �����ϸ� ���̴� ���� ������ �⺻���� AddShader �� ������� �̴�.
*/
#pragma once

#include "MnWorldComponent.h"
#include <map>
#include <memory>
#include "Shader.h"
#include "Utility\MnIDAllocator.h"

namespace MNL
{
	class ShaderList : public MnWorldComponent

	{
	public:
		ShaderList();
		~ShaderList();

		/**
		@brief �ڵ��Ҵ�� id�� ���̴� �߰�
		*/
		void AddShader(const std::shared_ptr<Shader>& spShader);
		/**
		@brief �ش� id�� ���̴� �߰�. �̹� �ִ� ���� ���� ��������.
		*/
		void AddShader(const std::shared_ptr<Shader>& spShader, int id);

		void RemoveShader(int id);

		/**
		@return ���̴��� �������� �ʴ� ��� nullptr ��ȯ
		*/
		std::shared_ptr<Shader> GetShader(int id);

		/**
		@brief ���̴� ����Ʈ�� ��ȯ�Ѵ�
		@return std::map
		*/
		std::map<int, std::shared_ptr<Shader>>& GetShaders();

		/**
		@brief ���̴��� ���� ������ �����Ѵ�. ������ ������Ʈ���� �ش� ������� �������Ѵ�.
		@param idOrder ���̴��� id�� ������� �Ѱ��ش�. ��) { 0, 1, 2, 3 }
		*/
		void SetRenderOrder(std::initializer_list<int> idOrder);

		/**
		@brief ���̴��� ���� ������ ��ȯ�Ѵ�. �⺻���� AddShader �� ������� �̴�.
		*/
		const std::vector<int>& GetRenderOrder() const;

	private:
		void _Init();

	private:
		std::map<int, std::shared_ptr<Shader>> m_lstShaders;
		std::vector<int> m_renderOrder;
		MnIDAllocator m_idAllocator;
	};
}