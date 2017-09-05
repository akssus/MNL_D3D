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
	MnModel class ONLY CONTAINS GEOMETRIC DATA. Does NOT have vertex buffer and index buffer.
	Designing own drawable class using MnModel and buffers is up to users
	*/
	class MnModel
	{
	public:
		MnModel();
		~MnModel();

		HRESULT LoadModelFromFile(std::wstring modelFileName);

		const CPD3DBuffer GetVertexBuffer() const;
		UINT GetVertexBufferStride() const;
		const CPD3DBuffer GetIndexBuffer() const;
		UINT GetIndexCount() const;
		DXGI_FORMAT GetIndexBufferFormat() const;


	private:
		MnVertexBuffer m_vertexBuffer;
		MnIndexBuffer m_indexBuffer;
	};
}