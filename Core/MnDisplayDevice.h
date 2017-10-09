/**
@class MNL::MnDisplayDevice
@author Akssus
@brief ���÷��� ��ġ�� ���÷��� ��� ������ ���� �����Ѵ�.

@section ����
�ϳ��� DisplayDevice�� �ϳ��� ���÷��� ��ġ(�����)�� ������ ��� �ִ�.\n
�����ϴ� ��� �ػ��� ����, �ֻ��� ���� ������ �����ϸ� Ư�� �ػ󵵰� �����Ǵ��� ���θ� �� �� �ִ�.\n
�߰��� �־��� ���ǰ� ���� ����� �����Ǵ� Display Mode�� ã�Ƴ��� GetClosestMode �޼ҵ带 �����Ѵ�.\n
�� �޼ҵ尡 �ʿ��� ������ �̷� �޼ҵ尡 ������ ����� Ȥ�� �����ڰ� ����Ͱ� �����ϴ� �Ϻ��ϰ� ��Ȯ�� �ػ󵵿� �ֻ��� ���� �˾ƾ� �ϱ� ������ �����ϱ� �����̴�.\n
*/

#pragma once

#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <vector>
#include "MnTypedefs.h"

namespace MNL
{
	/**
	@brief ���÷��� ��� ������ ����ִ�.
	*/
	struct MnDisplayMode
	{
		UINT width, height;
		UINT numerator, denominator;
	};
	class MnDisplayDevice
	{
	public:
		MnDisplayDevice();
		~MnDisplayDevice();
		/**
		@brief DXGIOutput �������̽��� ���� ��� ���÷��� ������ ���� �ʱ�ȭ �Ѵ�.
		@return �ʱ�ȭ ���� ����.
		*/
		HRESULT Init(CPDXGIOutput cpOutput);


		/**
		@brief DXGIOutput �������̽��� ��ȯ�Ѵ�.
		*/
		const CPDXGIOutput GetInterface() const;
		
		/**
		@brief �����Ǵ� ���÷��� ��� �� ���� ����� ���÷��� ��带 ã�� ��ȯ�Ѵ�.
		@param width �ػ� ����
		@param height �ػ� ����
		@param numerator �ֻ����� ����
		@param denominator �ֻ��� �и�
		*/
		MnDisplayMode GetClosestMode(UINT width, UINT height, UINT numerator, UINT denominator) const;


		/**
		@brief �ش� �ػ󵵸� �����ϴ��� ���θ� ��ȯ�Ѵ�.
		@return ������ ��� true ��ȯ.
		*/
		bool IsSupportResolutionOf(UINT width, UINT height) const;

		/**
		���� ���÷��� ��ġ�� ���÷��� ��� ������ ��ȯ�Ѵ�.
		*/
		UINT GetNumDisplayModes() const;


	private:
		std::vector<DXGI_MODE_DESC> m_displayModeDescs; ///< ���÷��� ���� ����� �����̳�
		std::vector<MnDisplayMode>  m_displayModes; ///< ���÷��� ��尡 ����� �����̳�
		UINT						m_numDisplayModes; ///< ���÷��� ��� ����
		CPDXGIOutput				m_cpDXGIOutput; ///< DXGIOutput �������̽�
	};
}