/**
@class MnGameObjectComponent
@brief 메시 데이터를 명세하는 게임 오브젝트 컴포넌트 클래스
@author Akssus
@section 개요
MnMesh 와 이름이 겹치지만 컴포넌트 사용상의 편의를 위해 Mesh란 이름을 사용. \n
*/

#pragma once
#include "MnGameObjectComponent.h"
#include "Render/MnMesh.h"
#include "Render/MnMeshData.h"
#include "Render/MnSkinnedMesh.h"
#include <memory>


namespace MNL
{
	class Mesh : public MnGameObjectComponent
	{
	public:
		Mesh();
		~Mesh();

		void SetMesh(const std::shared_ptr<MnMeshData>& meshData);

		/**
		@return 메시가 세팅되지 않았을 경우 nullptr 반환
		*/
		const std::shared_ptr<MnMesh> GetMesh() const;

		/**
		@brief 스켈레톤 포인터를 반환한다
		@return 스켈레톤이 존재하지 않는 경우 nullptr 을 반환한다
		*/
		const std::shared_ptr<MnSkeleton> GetSkeleton() const;

	private:
		std::shared_ptr<MnMesh> m_spMesh;
	};
}
