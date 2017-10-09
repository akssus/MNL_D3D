/**
@class MNL::MnD3DDevice
@author Akssus
@brief DIrectX11 ����̽��� ����̽� ���ؽ�Ʈ�� ����, �����Ѵ�.
@section ����
MnD3DDevice�� �ʱ�ȭ �ϱ� ���ؼ� �ʱ�ȭ�� MnHardware ��ü�� �ʿ��ϴ�. \n
MnD3DDevice�� MnHardware ��ü�κ��� ���� ������� �������̽��� ���� D3DDevice �������̽��� D3DDeviceContext �������̽��� �����Ѵ�. \n
�ʱ�ȭ �� MnD3DDevice�� MnRenderAPI Ŭ�������� ���� ����� ��ġ�� ��ȣ�ۿ� �ϴµ� ���ȴ�.
*/

#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"
#include "MnHardware.h"

namespace MNL
{
	class MnD3DDevice
	{
	public:
		MnD3DDevice();
		~MnD3DDevice();
		/**
		@brief D3DDevice, D3DDeviceContext �������̽��� ����, �ʱ�ȭ �Ѵ�.
		@param useDefaultAdapter ����Ʈ ���� ����� ��� ����.
		@return �ʱ�ȭ ���� ����.
		@warning ���� useDefaultAdapter ���� ���� ���� ����Ʈ ������ �ʱ�ȭ �ȴ�.
		*/
		HRESULT Init(const MnHardware& hardwareInfo, bool useDefaultAdapter);

		/**
		@brief D3DDevice �������̽��� ��ȯ�Ѵ�.
		*/
		CPD3DDevice GetDevice() const;
		/**
		@brief D3DDeviceContext �������̽��� ��ȯ�Ѵ�.
		*/
		CPD3DDeviceContext GetDeviceContext() const;

	private:
		CPD3DDevice m_cpD3DDevice; ///< D3Device �������̽�
		CPD3DDeviceContext m_cpD3DDeviceContext; ///> D3DDeviceContext �������̽�
	};
}