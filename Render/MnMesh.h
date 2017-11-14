#pragma once
#include <d3d11.h>
#include <string>
#include <memory>
#include "../Core\MnTypedefs.h"
#include "../Core\MnVertexBuffer.h"
#include "../Core\MnIndexBuffer.h"
#include "../Core\MnCustomVertexType.h"
#include "MnMeshData.h"

namespace MNL
{
	/*
	MnMesh is instance of the MnMeshData.
	MnMesh is minimal element of drawcall and it has ONE vertex buffer and ONE index buffer
	*/

	class MnSubMesh
	{	
	public:
		MnSubMesh();
		~MnSubMesh();
	
		virtual HRESULT Init(const std::shared_ptr<MnSubMeshData> spMeshData);

		void SetParent(const std::shared_ptr<MnSubMesh>& spMesh);
		std::shared_ptr<MnSubMesh> GetParent() const;

		void SetTransform(const DirectX::SimpleMath::Matrix& matTransform);
		const DirectX::SimpleMath::Matrix& GetTransform() const;

		void SetName(const std::string& name);
		std::string GetName() const;

		void SetVertexBuffer(const std::shared_ptr<MnVertexBuffer>& spVertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<MnIndexBuffer>& spIndexBuffer);


		void SetSubMeshFragments(const std::vector<MnSubMeshFragment>& subMeshFragments);
		UINT GetNumSubMeshFragments() const;
		const MnSubMeshFragment& GetSubMeshFragment(UINT index) const;

		const CPD3DBuffer GetVertexBuffer() const;
		UINT GetVertexBufferStride() const;
		const CPD3DBuffer GetIndexBuffer() const;
		UINT GetIndexCount() const;
		DXGI_FORMAT GetIndexBufferFormat() const;

	protected:
		DirectX::SimpleMath::Matrix m_matTransform;
		std::string m_name;
		std::shared_ptr<MnSubMesh> m_spParent;
		std::vector<MnSubMeshFragment> m_subMeshFragments;

		std::shared_ptr<MnVertexBuffer> m_spVertexBuffer;
		std::shared_ptr<MnIndexBuffer> m_spIndexBuffer;
	};

	class MnMesh
	{
	public:
		MnMesh();
		~MnMesh();

		HRESULT Init(const std::shared_ptr<MnMeshData>& spMeshData);

		void AddSubMesh(const std::shared_ptr<MnSubMesh>& spSubMesh);
		std::shared_ptr<MnSubMesh> GetSubMesh(UINT index);
		UINT GetNumSubMehses();

		bool HasBones();
		void SetSkeleton(const std::shared_ptr<MnSkeleton>& spSkeleton);
		std::shared_ptr<MnSkeleton> GetSkeleton();

	private:
		std::vector<std::shared_ptr<MnSubMesh>> m_lstSubMeshes;
		std::shared_ptr<MnSkeleton> m_spSkeleton;
		bool m_hasBones;
	};
}