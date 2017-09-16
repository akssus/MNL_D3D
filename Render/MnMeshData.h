#pragma once
#include <vector>
#include <string>
#include <memory>
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "../Core/MnVertexBuffer.h"
#include "../Core/MnIndexBuffer.h"
#include "MnMaterial.h"
#include "../MnSkeleton.h"
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



		bool					HasBone() const;
		std::shared_ptr<UINT>	GetParentIndex() const;
		const std::string&		GetName() const;
		const std::shared_ptr<MnSkeleton> GetSkeleton() const;
		const DirectX::SimpleMath::Matrix& GetTransform() const;

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
		//material

		//buffers
		std::shared_ptr<MnVertexBuffer> m_spVertexBuffer;
		std::shared_ptr<MnIndexBuffer> m_spIndexBuffer;
		
	};
}