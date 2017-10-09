/**
@class MnConstantElement
@brief ������� �� ������Ÿ�� ����
@author Akssus
@section ����
MnConstantBufferType �� �ҼӵǾ� �ϳ��� ������Ÿ���� ��Ÿ���� ���� ��ü.
��� ������ ���� �� ������Ʈ�� ���������� ����� ��� ��������� ������ ��Ʈ����(struct)�� ������ �˾ƾ� �ϴ� ���ŷο��� ���ϱ� ���� ���������.\n
���� �־��� �⺻���鸸�� ��� �����ϸ� ������� ������ ���̴� FLOAT, MATRIX, UINT ���� �� �� �ְ� �̴� MN_CONSTANT_ELEMENT_TYPE ���� ���ǵȴ�.
*/


#pragma once
#include <d3d11.h>
#include <string>
#include "DXTK\SimpleMath.h"

namespace MNL
{
	/**
	@brief ����� ������Ÿ���� �����ϴ� ������. ���������� �ʱ�ȭ ���� ���� ��Ҵ� MN_CONSTANT_ELEMENT_TYPE_NONE ���� ������.
	*/
	enum MN_CONSTANT_ELEMENT_TYPE
	{
		MN_CONSTANT_ELEMENT_TYPE_NONE,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT1,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT2,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT3,
		MN_CONSTANT_ELEMENT_TYPE_FLOAT4,
		MN_CONSTANT_ELEMENT_TYPE_MATRIX,
		MN_CONSTANT_ELEMENT_TYPE_UINT,
	};
	class MnConstantElement
	{
	public:
		MnConstantElement(const MN_CONSTANT_ELEMENT_TYPE& inputElementType);
		~MnConstantElement();

		/**
		@brief ����� element type�� ��ȯ�Ѵ�.
		*/
		MN_CONSTANT_ELEMENT_TYPE GetType() const;
		/**
		@brief ����� ����Ʈ ����� ��ȯ�Ѵ�. ��) MN_CONSTANT_ELEMENT_TYPE_FLOAT4 �� sizeof(float)*4 �� ��ȯ�Ѵ�.
		*/
		UINT GetByteSize() const;

	private:
		/**
		@brief 
		*/
		MnConstantElement();
		HRESULT _Init(const MN_CONSTANT_ELEMENT_TYPE& constantElementType);
		UINT _GetByteSizeOf(const MN_CONSTANT_ELEMENT_TYPE& constantElementType);

	private:
		std::string					m_name;
		MN_CONSTANT_ELEMENT_TYPE	m_type;
		UINT						m_byteSize;
	};
}