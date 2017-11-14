/**
@class MnMeshData
@brief �޽��� ���� ������ �� ���ؽ�, �ε��� ���۸� ���� ��ü.
@author Akssus
@section ����
�޽� ������ Ŭ������ ���� �����ϴ� ������ ���� �޽ø� �����ϴ� MnMesh ��ü�� ���� ���ؽ� ���ۿ� �ε��� ���۸� �����ϴ°��� �޸������� �̵��� �� �� �ְ�, \n
�ʿ��� �����Ϳ� ���ʿ��� �����͸� ������ ��� �����ͼ� �޽� �ν��Ͻ��� ������ �� �ְ� �ȴ�. \n
MnMesh �� MnMeshData �� ���ؽ� ���ۿ� �ε��� ������ �޸� �ּҸ��� ������ ������ �޽ø� ���� ��ü�� ��� ���� ���۸� �����ϰ� �ȴ�.\n
�׷��Ƿ� MnMesh�� ���������� ���� �޸��� ������ �����ؼ��� �ȵȴ�. \n
���� �ִϸ��̼��� ������ ��� ���ؽ� ������ ��ǥ�� ���� �������� �ʰ� �� �ȷ�Ʈ�� ���̴��� �ѱ����μ� ���̴� ������ ��ǥ�� ��ȯ�� �õ��Ѵ�. \n
MnSkeleton �� ���� �Ұ����� �ڿ��̹Ƿ� MnMesh ���� ���� ��� �ѹ��� Ŭ�δ��� �ʿ��ϴ�.
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
	struct MnSubMeshFragment
	{
		std::string subMeshName;
		UINT indexOffset;
		UINT indexCount;
	};

	/*
	A mesh data doesn't contain indices, only vertices. 
	Each sub mesh contains index references of the vertex array in mesh data.
	*/
	class MnSubMeshData
	{
	public:
		MnSubMeshData();
		~MnSubMeshData();

		void AddSubMeshFragment(const MnSubMeshFragment& submesh);

		void SetTransform(const DirectX::SimpleMath::Matrix& matTransform);
		void SetParentIndex(UINT index);
		void SetName(const std::string& name);
		void SetVertexBuffer(const std::shared_ptr<MnVertexBuffer> spVertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<MnIndexBuffer> spIndexBuffer);

		std::shared_ptr<UINT>	GetParentIndex() const;
		const std::string&		GetName() const;
		const DirectX::SimpleMath::Matrix& GetTransform() const;

		std::shared_ptr<MnVertexBuffer> GetVertexBuffer() const;
		std::shared_ptr<MnIndexBuffer>	GetIndexBuffer() const;

		UINT GetNumSubMeshFragments() const;
		const std::vector<MnSubMeshFragment>& GetSubMeshFragments() const;

	private:
		//properties
		DirectX::SimpleMath::Matrix m_matTransform;
		std::shared_ptr<UINT> m_spParentIndex;
		std::string m_meshName;
		std::vector<MnSubMeshFragment> m_lstSubMeshFragments;

		//buffers
		std::shared_ptr<MnVertexBuffer> m_spVertexBuffer;
		std::shared_ptr<MnIndexBuffer> m_spIndexBuffer;
		
	};

	class MnMeshData
	{
	public:
		MnMeshData();
		~MnMeshData();

		bool HasBones();
		void SetSkeleton(const std::shared_ptr<MnSkeleton>& spSkeleton);
		std::shared_ptr<MnSkeleton> GetSkeleton() const;

		void AddSubMesh(const std::shared_ptr<MnSubMeshData>& spSubMesh);
		std::shared_ptr<MnSubMeshData> GetSubMesh(UINT index);
		UINT GetNumSubMeshes() const;
		
	private:
		std::vector<std::shared_ptr<MnSubMeshData>> m_lstSubMeshes;
		bool m_hasBones;
		std::shared_ptr<MnSkeleton> m_spSkeleton;
	};


}