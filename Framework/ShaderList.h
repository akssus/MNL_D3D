/**
@class ShaderList
@brief 다수의 셰이더를 갖는 컴포넌트
@author Akssus
@section 개요
셰이더들을 가지는 컴포넌트. 셰이더 추가 후 렌더러에서 어떤 셰이더부터 실행할지 순서를 정해줘야 한다.\n
이는 SetRenderOrder 를 이용해 정의 가능하며 셰이더 실행 순서의 기본값은 AddShader 된 순서대로 이다.
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
		@brief 자동할당된 id로 셰이더 추가
		*/
		void AddShader(const std::shared_ptr<Shader>& spShader);
		/**
		@brief 해당 id에 셰이더 추가. 이미 있던 것은 덮어 씌워진다.
		*/
		void AddShader(const std::shared_ptr<Shader>& spShader, int id);

		void RemoveShader(int id);

		/**
		@return 셰이더가 존재하지 않는 경우 nullptr 반환
		*/
		std::shared_ptr<Shader> GetShader(int id);

		/**
		@brief 셰이더 리스트를 반환한다
		@return std::map
		*/
		std::map<int, std::shared_ptr<Shader>>& GetShaders();

		/**
		@brief 셰이더의 실행 순서를 정의한다. 렌더러 컴포넌트에서 해당 순서대로 렌더링한다.
		@param idOrder 셰이더의 id를 순서대로 넘겨준다. 예) { 0, 1, 2, 3 }
		*/
		void SetRenderOrder(std::initializer_list<int> idOrder);

		/**
		@brief 셰이더의 실행 순서를 반환한다. 기본값은 AddShader 된 순서대로 이다.
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