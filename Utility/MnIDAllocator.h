/**
@class MnIDAllocator
@brief ID ���� �Ҵ��ϱ� ���� ���� Ŭ����
@author Akssus
@section ����
ID���� �ڵ����� �Ҵ����ش�. ���� ���� ����.
*/

#pragma once

#include <vector>

namespace MNL
{
	class MnIDAllocator
	{
	public:
		MnIDAllocator();
		~MnIDAllocator();

		/**
		@brief ���̵� �Ҵ�� ������ �����Ѵ�.
		@param min 0 ���� ū ��
		@param max min���� ū ��
		*/
		void SetRange(int min, int max);
		
		
		/**
		@brief ���� ����ִ� ID�� ���������� �Ҵ��Ѵ�.
		@return �Ҵ� ���н� -1 ��ȯ
		*/
		int Allocate();

		/**
		@brief �ش� id�� ��������� ����Ѵ�.
		*/
		void Register(int id);
		
		/**
		@brief �ش� ID�� ��� �����Ѵ�.
		*/
		void Deallocate(int id);
		
	private:
		std::vector<bool> m_idPool;
		int m_offset;
		int m_length;
		
		
	};
}
