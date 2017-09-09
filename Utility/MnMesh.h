#pragma once
#include <d3d11.h>
#include <string>
#include "../Core\MnTypedefs.h"
#include "../Core\MnVertexBuffer.h"
#include "../Core\MnIndexBuffer.h"
#include "../Core\MnCustomVertexType.h"

namespace MNL
{
	/*
	MnMesh class ONLY CONTAINS GEOMETRIC DATA. Does NOT have vertex buffer and index buffer.
	Designing own drawable class using MnMesh and buffers is up to users
	*/
	class MnMesh
	{	
	public:
		MnMesh();
		~MnMesh();

		virtual HRESULT LoadModelFromFile(const CPD3DDevice& cpDevice, const std::wstring& modelFileName, const std::shared_ptr<MnCustomVertexType>& spVertexType) = 0;

		const CPD3DBuffer GetVertexBuffer() const;
		UINT GetVertexBufferStride() const;
		const CPD3DBuffer GetIndexBuffer() const;
		UINT GetIndexCount() const;
		DXGI_FORMAT GetIndexBufferFormat() const;

	protected:
		MnVertexBuffer m_vertexBuffer;
		MnIndexBuffer m_indexBuffer;
	};
}