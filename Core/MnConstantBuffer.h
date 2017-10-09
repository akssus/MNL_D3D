/**
@class MnConstantBuffer
@brief 상수버퍼를 생성, 접근하여 갱신한다.
@author Akssus
@section 개요
MnConstantBufferType 의 레이아웃을 참조하여 상수버퍼의 메모리를 할당하고 이에 접근할 수 있는 인터페이스를 제공한다. \n
초기화 시의 slotIndex 는 셰이더 내에 레지스터 슬롯 위치에 직결되며, 버텍스셰이더와 픽셀셰이더 어느쪽에 바인딩할지 MN_CONSTANT_BUFFER_BELONG 열거형을 통해 설정할 수 있다. \n
예를들어 MN_CONSTANT_BUFFER_VS , 2의 slotIndex 를 가진다면, 버텍스셰이더의 register(b2)에 바인딩된다. \n
다수의 MnConstantBuffer 를 운용할 경우 레지스터 슬롯이 겹치지 않도록 slotIndex 를 열거형 등으로 관리해줘야 한다.\n
\n
메모리의 갱신에는 D3D11_SUBRESOURCE_DATA 객체를 참조하므로 MnConstantBuffer 로부터 특정 struct를 얻어낼 수 없다. 이러한 메모리 레이아웃은 객체를 생성하는 쪽에서 직접 정의해야 한다.\n
그러므로 MnConstantBuffer 객체를 생성하여 사용하는 것보단 클래스를 상속하여 특정 목적에 맞게 버퍼 메모리를 갱신하는 인터페이스를 구현하는 편이 좋다.
*/

#pragma once
#include <d3d11.h>
#include <memory>
#include "MnTypedefs.h"
#include "MnGpuBuffer.h"
#include "MnConstantBufferType.h"

namespace MNL
{
	enum MN_CONSTANT_BUFFER_BELONG
	{
		MN_CONSTANT_BUFFER_BELONG_NONE,
		MN_CONSTANT_BUFFER_BELONG_VS,
		MN_CONSTANT_BUFFER_BELONG_PS,
		MN_CONSTANT_BUFFER_BELONG_BOTH
	};

	class MnConstantBuffer
	{
	public:
		MnConstantBuffer();
		~MnConstantBuffer();
		
		HRESULT Init(const CPD3DDevice& cpDevice, const std::shared_ptr<MnConstantBufferType>& constantBufferType, UINT slotIndex, const MN_CONSTANT_BUFFER_BELONG& constantBufferBelong);
		/**
		* @Usage 
		* Create D3D11_SUBRESOURCE_DATA, 
		* set pSysMem link to the user created own structrue(must be same byte size as constant buffer type),
		* then transfer as parameter.
		*/
		void UpdateBuffer(CPD3DDeviceContext cpDeviceContext, const D3D11_SUBRESOURCE_DATA& data);

		const CPD3DBuffer GetBuffer() const;
		UINT GetBufferByteSize() const;
		UINT GetSlotIndex() const;
		MN_CONSTANT_BUFFER_BELONG GetBelong() const;

	private:
		MnGpuBuffer m_buffer;
		UINT m_slotIndex;
		MN_CONSTANT_BUFFER_BELONG m_belong;
	};
}