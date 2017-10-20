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
���̴��� ����Ͽ� ��üȭ �� �� ���� ���� ����� m_renderedScene �� �������� �Ѵ�. (�ʼ�)
*/
#pragma once
#include <memory>
#include <list>
#include "Core/MnTypedefs.h"
#include "Render/MnMesh.h"
#include "Render/MnCustomRenderTarget.h"
#include "MnGameObject.h"


namespace MNL
{
	class MnGameWorld;
	class ShaderList;

	class Shader
	{
		friend ShaderList;
	public:
		Shader();
		virtual ~Shader();
		
		/**
		@brief ���̴� ����Ʈ�� �߰� �Ǿ�����(�ν��Ͻ�ȭ �Ǿ�����) �߻��ϴ� �̺�Ʈ
		*/
		virtual void OnAttatched();

	public:
		void AddObjectsToQueue(const std::shared_ptr<MnGameObject>& spObject);
		
		/**
		@brief ���� ���� Ÿ���� ��ȯ�Ѵ�.
		@return ������ �����߰ų� ���� �������� �ʾ��� ��� nullptr�� ��ȯ�Ѵ�. ����Ʈ ������ ���� ���� Ÿ���� ��ȯ������ SetFinalRenderTarget�� ȣ���Ͽ� ���� ����
		*/
		std::shared_ptr<MnCustomRenderTarget> GetFinalRenderTarget() const;

		/**
		@brief ť�� �ִ� ������Ʈ���� �ش� ���̴��� �����Ѵ�. ���� �� ť�� ������� �Ѵ�.
		@param prevRendererdScene �� ���̴� �ܰ迡�� ��µ� �����. ��뿩�δ� ������ ���� �ٸ���.
		*/
		virtual void Render(const std::shared_ptr<MnCustomRenderTarget>& prevRenderedScene) = 0;

		void SetID(int id);
		int GetID() const;

	protected:
		void _ClearQueue();
		MnGameWorld* _GameWorld() const;

		/**
		@brief MnMesh �� ��ο��� �ϴ� ���� �޼ҵ�
		*/
		void _RenderMesh(const std::shared_ptr<MnMesh> mesh);

	private:
		virtual void _Init(MnGameWorld* pWorld);
		void _SetGameWorld(MnGameWorld* pWorld);

	protected:
		std::list<std::shared_ptr<MnGameObject>> m_renderQueue;

	private:
		MnGameWorld* m_pWorld;
		int m_id;

		std::shared_ptr<MnCustomRenderTarget> m_spFinalRenderTarget;
	};
}
