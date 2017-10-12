/**
@class Shader
@brief ������� ���Ű� ���̴��� ����� ��ο����� �ǽ��ϴ� ������Ʈ
@author Akssus
@section ����
���̴��� å���� ����. \n
ù°�� ���忡�� ������ ���� ������۸� ������Ʈ ����� �Ѵ�. ��ü���� ������ ����ؼ� �����ؾ� �Ѵ�. \n
��°�� MnShaderPath �� �̿��� ť�� �߰��� ������Ʈ�鿡 ���� �������� �ǽ��Ѵ�. \n
���������� ���� ������ ����� �ؽ��ķμ� �����Ͽ� ���� ���̴� Ȥ�� ���������� ����Ʈ�� ������ �� �ִ�. \n
�������� ���̴��� ���� ������ ������ �켱������ �����Ѵ�. ��) ���۵���̵� -> ���ͼ��̵� -> �����̵� -> 2D���̵� \n
�� �������� ��� ���� �����ϱ� ���� �� �ܰ迡 ����� ����Ÿ�ٺ�� ���� ���̴����� �Ѱ�����. �̸� ������� �������� ���� ���̴��� å��. \n
*/
#pragma once
#include <memory>
#include <list>
#include "Core/MnTypedefs.h"
#include "Render/MnCustomRenderTarget.h"
#include "MnWorldComponent.h"
#include "MnGameObject.h"

namespace MNL
{
	class Shader : MnWorldComponent
	{
	public:
		Shader();
		virtual ~Shader();

		void AddObjectsToQueue(const std::shared_ptr<MnGameObject>& spObject);
		
		/**
		@brief ���� �Ϸ� ���� ����� ��ȯ�Ѵ�.
		@return ������ �����߰ų� ���� �������� ������� �ʾ��� ��� nullptr �� ��ȯ�Ѵ�.
		*/
		CPD3DShaderResourceView GetRenderedScene() const;

		/**
		@brief ť�� �ִ� ������Ʈ���� �ش� ���̴��� �����Ѵ�. ���� �� ť�� ������� �Ѵ�.
		@param prevRendererdScene �� ���̴� �ܰ迡�� ��µ� �����. ��뿩�δ� ������ ���� �ٸ���.
		*/
		virtual void Render(const CPD3DShaderResourceView& prevRenderedScene) = 0;

	protected:
		void _ClearQueue();

	private:
		void _Init();

	private:
		std::list<const std::shared_ptr<MnGameObject>> m_renderQueue;
		MnCustomRenderTarget m_renderedScene;
	};
}
