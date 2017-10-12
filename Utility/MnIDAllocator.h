/**
@class MnIDAllocator
@brief ID 값을 할당하기 위한 헬퍼 클래스
@author Akssus
@section 개요
ID값을 자동으로 할당해준다. 범위 지정 가능.
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
		@brief 아이디가 할당될 범위를 설정한다.
		@param min 0 보다 큰 값
		@param max min보다 큰 값
		*/
		void SetRange(int min, int max);
		
		
		/**
		@brief 현재 비어있는 ID를 오름순으로 할당한다.
		@return 할당 실패시 -1 반환
		*/
		int Allocate();

		/**
		@brief 해당 id를 사용중으로 등록한다.
		*/
		void Register(int id);
		
		/**
		@brief 해당 ID를 사용 해제한다.
		*/
		void Deallocate(int id);
		
	private:
		std::vector<bool> m_idPool;
		int m_offset;
		int m_length;
		
		
	};
}
