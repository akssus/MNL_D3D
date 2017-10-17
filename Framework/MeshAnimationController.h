/**
@section 개요
애니메이션 컨트롤러는 스켈레톤 자체를 갖지는 않는다. \n
애니메이션 컨트롤러는 애니메이션 정보(키프레임 당 각 Bone의 로컬 트랜스폼) 만을 리스트로 가지며,
Mesh 컴포넌트의 스켈레톤에 대해 업데이트를 진행한다. 이에 Mesh 컴포넌트의 스켈레톤의 각 Bone의 로컬 트랜스폼 값은 변경되며, 메시의 버텍스는 변경되지 않는다.
*/


#pragma once

#include "MnGameObjectComponent.h"
#include <map>
#include <memory>
#include "Render/MnBoneAnimation.h"
#include "Render/MnBoneAnimationTracker.h"


namespace MNL
{
	class MeshAnimationController : public MnGameObjectComponent
	{
	public:
		MeshAnimationController();
		~MeshAnimationController();

		/**
		@brief 애니메이션을 해당 이름을 Key로서 추가한다. 이미 Key가 존재하는 경우 덮어씌운다.
		*/
		void AddAnimation(const std::string& animName, const std::shared_ptr<MnBoneAnimation>& spAnimation);

		/**
		@brief 현재 애니메이션을 해당 애니메이션으로 설정한다. Key가 존재하지 않을 경우 동작하지 않는다.
		*/
		void SetAnimation(const std::string& animName);

		/**
		@brief 해당 애니메이션을 제거한다.
		*/
		void RemoveAnimation(const std::string& animName);

		std::shared_ptr<MnBoneAnimation>& GetAnimation(const std::string&);

		/**
		@brief 현재 오브젝트의 메시를 확인하여 본을 업데이트한다.
		*/
		void UpdateBones();

		/**
		@brief 애니메이션 재생 완료 시 루프 여부를 설정한다.
		*/
		void SetLoop(bool isLoop);

		
	private:
		void _Init();

	private:
		std::map<std::string, std::shared_ptr<MnBoneAnimation>> m_tblAnimations;
		MnBoneAnimationTracker m_tracker;
	};
}