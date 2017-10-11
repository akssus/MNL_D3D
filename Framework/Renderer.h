/**
@class Renderer
@brief ������ ���� ������Ʈ ������Ʈ�� ���̽� Ŭ����
@author Aksuss
@section ����
�������� �ʿ��� ���̴�, ����Ʈ, ���׸���, �ؽ��� �� �����͸� �����Ѵ�. \n
�ڿ� ������ ���� ���� �����ͷ� �μ��� �޴´�. \n
���̷����ϰԵ� ������ ������Ʈ�� MnRenderer �� ���Ե��� ������ �̴� ��� Ŭ�������� Fixed�� �����Ѵ�.
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

namespace MNL
{
	class Renderer : public MnWorldComponent
	{
	public:
		Renderer();
		virtual ~Renderer();


		/**
		@brief ���� ������Ʈ�� �޽ø� �������Ѵ�. �޽ð� �������� �ʰų� �������� ���õ��� �ʾ��� ��� �ƹ��ϵ� �Ͼ�� �ʴ´�.
		@todo �ﰢ ���������� ���߿� ����Ʈ�� �־ �ѹ��� �����ϴ� ������ �ٲٱ�
		*/
		virtual void Render() = 0;
	
		
	};
}
