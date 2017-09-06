#pragma once
#include <d3d11.h>
#include <memory>
#include "MnTypedefs.h"
#include "MnGpuBuffer.h"
#include "MnConstantBufferType.h"

namespace MNL
{
	enum MnConstantBufferBelong
	{
		Mn_CONSTANT_BUFFER_BELONG_NONE,
		MN_CONSTANT_BUFFER_BELONG_VS,
		MN_CONSTANT_BUFFER_BELONG_PS
	};
	class MnConstantBuffer
	{
	public:
		MnConstantBuffer();
		~MnConstantBuffer();
		
		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnConstantBufferType>& constantBufferType, UINT index, const MnConstantBufferBelong& constantBufferBelong);
		/**
		* @Usage 
		* Create D3D11_SUBRESOURCE_DATA, 
		* set pSysMem link to the user created own structrue(must be same byte size as constant buffer type),
		* then transfer as parameter.
		*/
		void UpdateBuffer(CPD3DDeviceContext cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data);

		const CPD3DBuffer GetBuffer() const;
		UINT GetBufferByteSize() const;
		UINT GetIndex() const;
		MnConstantBufferBelong GetBelong() const;

	private:
		MnGpuBuffer m_buffer;
		UINT m_index;
		MnConstantBufferBelong m_belong;
	};
}