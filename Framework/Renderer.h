/**
@class Renderer
@brief ������ ���� ������Ʈ ������Ʈ�� ���̽� Ŭ����
@author Aksuss
@section ����
�������� ����� �����̴�.\n
����κ��� ������ ���� : ����Ʈ, ī�޶��� ����������, ���̴� \n
������Ʈ�κ��� ������ ���� : ���庯ȯ, ���׸���, �ؽ���, �޽�, ���ȷ�Ʈ \n
�̻��� ������ �����ؼ� ������۸� �����ϰ� ��ο����ϴ� å���� ���Ѵ�.\n
�� ��������� �������� �ε����� �̸� ������ �����Ƿ� �߰� ������۰� �ʿ��� ��� ���̴������� �̸� �Ҵ���� ���� �ε����� ������۸� ������Ʈ �ؾ��Ѵ�.\n
\n

@section ������� ��
�������� �ε���, �뵵, ���ε� �������� \n
b0 : ���庯ȯ, VS \n
b1 : �� ��������, VS \n
b2 : ����Ʈ, VS & PS \n
b3 : ���׸���, PS \n
b4 : ���ȷ�Ʈ, VS \n
*/

#pragma once
#include <memory>
#include <vector>
#include "MnWorldComponent.h"
#include "Render/MnRenderer.h"
#include "Render/MnMeshTextureCombination.h"
#include "Render/MnShaderPathInstance.h"
#include "Render/MnLightSource.h"
#include "Render/MnMaterial.h"
#include "Render/MnSkeleton.h"
#include "Render/MnWorldTransformBuffer.h"
#include "Render/MnViewProjectionTransformBuffer.h"
#include "Render/MnLightBuffer.h"
#include "Render/MnMaterialBuffer.h"
#include "Render/MnBonePaletteBuffer.h"

namespace MNL
{
	enum _CONST_BUFFERS
	{
		_CONST_BUF_WORLD,  //register(b0)
		_CONST_BUF_VIEWPROJECTION, //register(b1)
		_CONST_BUF_LIGHT, //register(b2)
		_CONST_BUF_MATERIAL, //register(b3)
		_CONST_BUF_BONE_PALETTE, //register(b4)
		_CONST_BUF_TOTAL
	};

	class Renderer : public MnWorldComponent
	{
	public:
		Renderer();
		~Renderer();

		void Render();
	
	private:
		void _Init();
		
	private:
		MnWorldTransformBuffer m_worldBuffer;
		MnViewProjectionTransformBuffer m_viewProjectionBuffer;
		MnLightBuffer m_lightBuffer;
		MnMaterialBuffer m_materialBuffer;
		MnBonePaletteBuffer m_bonePaletteBuffer;
	};
}
