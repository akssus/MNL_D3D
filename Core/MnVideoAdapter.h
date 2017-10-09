/**
@class MNL::MnVideoAdapter
@author Akssus
@brief ���� ������� ������ ���÷��� ��ġ���� �����Ѵ�.

@section ����
�ϳ��� MnVideoAdapter�� �ϳ��� ����ī�� ������ ��� �ִ�.\n
���� ī���� �̸�, ���� ī�� �޸�, GPU�� �ִ� ���� Feature Level �� ������ �����Ѵ�.\n
*/

#pragma once
#include <d3d11.h>
#include "MnTypedefs.h"
#include "MnDisplayDevice.h"

namespace MNL
{
	/*
	one IDXGIAdapter represnets one MnVideoAdapter instance
	*/
	class MnVideoAdapter
	{
	public:
		MnVideoAdapter();
		~MnVideoAdapter();

		/**
		@brief CPDXGIAdapter �������̽��� ���� ���÷��� ��ġ���� ������ �����Ͽ� �ʱ�ȭ �Ѵ�.
		@param cpAdapter IDXGIFactory�� ���� ������ IDXGIAdapter �������̽�.
		@return �ʱ�ȭ ���� ����.
		*/
		HRESULT Init(CPDXGIAdapter cpAdapter);

		/**
		@brief ���� ������� �̸��� ��ȯ�Ѵ�
		*/
		std::wstring GetName() const;

		/**
		@brief ���� ������� ���� �޸� ũ�⸦ ��ȯ�Ѵ�.
		@return MB ������ �޸� ũ��.
		*/
		UINT GetMemorySize() const;
		
		/**
		@brief ���÷��� ��ġ�� ������ ��ȯ�Ѵ�.
		*/
		UINT GetNumDisplays();

		/**
		@brief ���� ������� �������̽��� ��ȯ�Ѵ�.
		@return CPDXGIAdapter �������̽�
		*/
		const CPDXGIAdapter GetInterface() const;
		
		/**
		@brief �����̳� ���� ���÷��� ��ġ�� ��ȯ�Ѵ�.
		@param ���÷��� ��ġ�� �ε���
		@warning Out of index ���۽� ũ���� �߻�.
		*/
		const MnDisplayDevice GetDisplayDevice(int index) const;

		/**
		@brief GPU�� �����ϴ� �ִ� ���� ������ ��ȯ�Ѵ�.
		*/
		D3D_FEATURE_LEVEL GetMaxSupportedFeatureLevel() const;

	private:
		/**
		@brief DXGIAdapter �������̽��κ��� �ִ� ���� ���ķ����� ���Ѵ�.
		@return ������ ���۽� S_OK ��ȯ
		*/
		HRESULT _InitMaxSupportedFeatureLevel(CPDXGIAdapter cpAdapter);

	private:
		std::wstring		m_adapterName; ///< ���� ������� �̸�
		UINT				m_videoMemorySize; ///< ���� ������� ���� �޸� ũ��
		CPDXGIAdapter		m_cpDXGIAdapter; ///< MnVideoAdapter�� �����ϴ� DXGI �������̽�
		DXGI_ADAPTER_DESC	m_desc; ///< DXGIAdapter �������̽��� ��
		D3D_FEATURE_LEVEL	m_maxFeatureLevel; ///< ���� ���� ������� �ִ� ���� ���� ����
 		std::vector<MnDisplayDevice> m_displayDevices; ///< �ʱ�ȭ�� ���÷��� ��ġ�� ����Ǵ� �����̳�
	};
}