#pragma once
#include <d3d11.h>
#include <string>
#include "../Core\MnTypedefs.h"
#include "../Core\MnVertexBuffer.h"
#include "../Core\MnIndexBuffer.h"
#include "../Core\MnCustomVertexType.h"
#include "../MnMeshData.h"

namespace MNL
{
	struct MnSubMesh
	{
		std::string subMeshName;
		std::string materialName;
		UINT indexOffset;
		UINT indexCount;
	};
	/*
	MnMesh is instance of the MnMeshData.
	MnMesh is minimal element of drawcall and it has ONE vertex buffer and ONE index buffer
	*/
	class MnMesh
	{	
	public:
		MnMesh();
		~MnMesh();
	
		virtual HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData, const std::shared_ptr<MnCustomVertexType>& spVertexType);

		void SetParent(const std::shared_ptr<MnMesh>& spMesh);
		std::shared_ptr<MnMesh> GetParent() const;

		UINT GetNumSubMeshes() const;
		const MnSubMesh& GetSubMesh(UINT index) const;

		const CPD3DBuffer GetVertexBuffer() const;
		UINT GetVertexBufferStride() const;
		const CPD3DBuffer GetIndexBuffer() const;
		UINT GetIndexCount() const;
		DXGI_FORMAT GetIndexBufferFormat() const;

	protected:
		std::string m_name;
		std::shared_ptr<MnMesh> m_spParent;
		std::vector<MnSubMesh> m_subMeshes;

		MnVertexBuffer m_vertexBuffer;
		MnIndexBuffer m_indexBuffer;
	};
}