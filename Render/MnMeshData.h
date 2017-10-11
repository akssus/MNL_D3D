/**
@class MnMeshData
@brief 메시의 기하 데이터 및 버텍스, 인덱스 버퍼를 지닌 객체.
@author Akssus
@section 개요
메시 데이터 클래스가 따로 존재하는 이유는 같은 메시를 공유하는 MnMesh 객체는 같은 버텍스 버퍼와 인덱스 버퍼를 공유하는것이 메모리적으로 이득을 볼 수 있고, \n
필요한 데이터와 불필요한 데이터를 적절히 골라 가져와서 메시 인스턴스를 생성할 수 있게 된다. \n
MnMesh 는 MnMeshData 의 버텍스 버퍼와 인덱스 버퍼의 메모리 주소만을 가져가 동일한 메시를 지닌 객체의 경우 같은 버퍼를 공유하게 된다.\n
그러므로 MnMesh가 인위적으로 버퍼 메모리의 내용을 수정해서는 안된다. \n
뼈대 애니메이션의 구현의 경우 버텍스 버퍼의 좌표를 직접 변경하지 않고 본 팔레트를 셰이더로 넘김으로서 셰이더 내에서 좌표의 변환을 시도한다. \n
MnSkeleton 은 공유 불가능한 자원이므로 MnMesh 에서 얻어가는 경우 한번의 클로닝이 필요하다.
*/

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Core/MnVertexBuffer.h"
#include "Core/MnIndexBuffer.h"
#include "MnMaterial.h"
#include "MnSkeleton.h"
#include "MnBoneAnimation.h"
namespace MNL
{
	/*
	The indexOffset is base offset from the vertex array
	*/
	struct MnSubMesh
	{
		std::string subMeshName;
		UINT indexOffset;
		UINT indexCount;
	};
	/*
	A mesh data doesn't contain indices, only vertices. 
	Each sub mesh contains index references of the vertex array in mesh data.
	*/
	class MnMeshData
	{
	public:
		MnMeshData();
		~MnMeshData();

		void AddSubMesh(const MnSubMesh& submesh);

		void SetTransform(const DirectX::SimpleMath::Matrix& matTransform);
		void SetParentIndex(UINT index);
		void SetName(const std::string& name);
		void SetSkeleton(const std::shared_ptr<MnSkeleton> spSkeleton);
		void SetVertexBuffer(const std::shared_ptr<MnVertexBuffer> spVertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<MnIndexBuffer> spIndexBuffer);
		void AddAnimation(const MnBoneAnimation& animation);


		bool					HasBone() const;
		std::shared_ptr<UINT>	GetParentIndex() const;
		const std::string&		GetName() const;
		const std::shared_ptr<MnSkeleton> GetSkeleton() const;
		const DirectX::SimpleMath::Matrix& GetTransform() const;
		
		const std::vector<MnBoneAnimation>& GetAnimations() const;

		std::shared_ptr<MnVertexBuffer> GetVertexBuffer() const;
		std::shared_ptr<MnIndexBuffer>	GetIndexBuffer() const;

		UINT							GetNumSubMeshes() const;
		const std::vector<MnSubMesh>&	GetSubMeshes() const;

	private:
		//properties
		DirectX::SimpleMath::Matrix m_matTransform;
		std::shared_ptr<UINT> m_spParentIndex;
		bool m_hasBone;
		std::string m_meshName;
		std::vector<MnSubMesh> m_lstSubMeshes;
		std::shared_ptr<MnSkeleton> m_spSkeleton;
		std::vector<MnBoneAnimation> m_lstBoneAnimations;
		//material

		//buffers
		std::shared_ptr<MnVertexBuffer> m_spVertexBuffer;
		std::shared_ptr<MnIndexBuffer> m_spIndexBuffer;
		
	};
}