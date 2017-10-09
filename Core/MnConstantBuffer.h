/**
@class MnConstantBuffer
@brief ������۸� ����, �����Ͽ� �����Ѵ�.
@author Akssus
@section ����
MnConstantBufferType �� ���̾ƿ��� �����Ͽ� ��������� �޸𸮸� �Ҵ��ϰ� �̿� ������ �� �ִ� �������̽��� �����Ѵ�. \n
�ʱ�ȭ ���� slotIndex �� ���̴� ���� �������� ���� ��ġ�� ����Ǹ�, ���ؽ����̴��� �ȼ����̴� ����ʿ� ���ε����� MN_CONSTANT_BUFFER_BELONG �������� ���� ������ �� �ִ�. \n
������� MN_CONSTANT_BUFFER_VS , 2�� slotIndex �� �����ٸ�, ���ؽ����̴��� register(b2)�� ���ε��ȴ�. \n
�ټ��� MnConstantBuffer �� ����� ��� �������� ������ ��ġ�� �ʵ��� slotIndex �� ������ ������ ��������� �Ѵ�.\n
\n
�޸��� ���ſ��� D3D11_SUBRESOURCE_DATA ��ü�� �����ϹǷ� MnConstantBuffer �κ��� Ư�� struct�� �� �� ����. �̷��� �޸� ���̾ƿ��� ��ü�� �����ϴ� �ʿ��� ���� �����ؾ� �Ѵ�.\n
�׷��Ƿ� MnConstantBuffer ��ü�� �����Ͽ� ����ϴ� �ͺ��� Ŭ������ ����Ͽ� Ư�� ������ �°� ���� �޸𸮸� �����ϴ� �������̽��� �����ϴ� ���� ����.
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