/**
@class MNL::MnHardware
@author Akssus
@brief ���� ����� �� ���÷��� ��ġ ����.

@section ����
MnHardware�� MnD3DDevice�� �����ϱ� �� ��ǻ���� ���� �ϵ���� ������ ������ ���� ��ü�̴�.\n\n
MnHardware�� MnVideoAdapter�� MnDisplayDevice�� ���� ���� ��� ���� ��ġ(����ī�� �� �����)�� ������ ����, �����Ѵ�.\n\n
MnHardware�� MnDisplayDevice�� ���������� ����� ������ ������\n\n
MnHardware - MnVideoAdapter - MnDisplayDevice \n
1......n                         1.....n \n\n
�� ���踦 ������.\n
�̷��� ����ȭ�� ������ �� ���� ��ǻ�Ϳ��� �������� ����ī�带 ���� �� �ְ� (��� �Ѱ�����)
�� ����ī��� �������� ����Ϳ� ����� �� �ֱ� �����̴�.\n
Ư�� ������ ��� ����� �̻��� ���Ƽ� �̿� ���� ������ �Ұ����� �� �ϴ�.
*/

#pragma once
#include <d3d11.h>
#include <vector>
#include "MnTypedefs.h"
#include "MnVideoAdapter.h"
#include "MnDisplayDevice.h"

namespace MNL
{
	class MnHardware
	{
	public:
		MnHardware();
		~MnHardware();

		/** 
		@brief ��ġ ������ ���� �ʱ�ȭ �Ѵ�.
		@return �ʱ�ȭ ���� ����.
		*/
		HRESULT	Init();

		/**
		@brief ���� ������� ������ ���´�.
		*/
		UINT GetNumVideoAdapters() const;
		/**
		@brief �����̳� ���� MnVideoAdapter�� ���´�.
		@param index ���� ������� �ε���
		@warning Out of index ���۽� ũ���� �߻�
		*/
		const MnVideoAdapter GetVideoAdapter(UINT index) const;

		/**
		@brief GPU�� �����ϴ� �ִ� ���� ������ ��´�.
		@return �ּ� D3D_FEATURE_LEVEL_9_1�� ��ȯ�ȴ�.
		*/
		D3D_FEATURE_LEVEL GetMaxSupportedFeatrueLevel(UINT adapterIndex) const;
		

	private:
		std::vector<MnVideoAdapter>		m_videoAdapters; ///< �ʱ�ȭ�� ���� ����� ��ġ�� ����Ǵ� �����̳�
	};
}
