#pragma once
#include <d3d11.h>
#include <string>
#include <memory>
#include "../Core\MnTypedefs.h"
#include "../Core\MnVertexBuffer.h"
#include "../Core\MnIndexBuffer.h"
#include "../Core\MnCustomVertexType.h"
#include "../MnMeshData.h"

namespace MNL
{
	/*
	MnMesh is instance of the MnMeshData.
	MnMesh is minimal element of drawcall and it has ONE vertex buffer and ONE index buffer
	*/
	class MnMesh
	{	
	public:
		MnMesh();
		~MnMesh();
	
		virtual HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnMeshData> spMeshData);

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

		std::shared_ptr<MnVertexBuffer> m_spVertexBuffer;
		std::shared_ptr<MnIndexBuffer> m_spIndexBuffer;
	};
}