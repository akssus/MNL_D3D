/**
@class Renderer
@brief ������ ���� ������Ʈ ������Ʈ�� ���̽� Ŭ����
@author Aksuss
@section ����
���̴��� ������ ����Ÿ���� ���������� ����۷� �ѱ�� ������ ���.\n
ȭ�鿡 ��ó�� ����Ʈ�� �ʿ��� ��� ���������� ó��. ��) �ο������н� �� \n
���̴��� �������� ����Ʈ�� ���̴����� ó���ϴ°� ����, ������������ ����Ʈ�� ȭ�� ��ü�� ������ ��� �������� ����.
*/

#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include <memory>
#include <vector>
#include "MnWorldComponent.h"
#include "Render/MnRenderWindow.h"
#include "Render/MnRenderer.h"
#include "Render/MnMeshTextureCombination.h"
#include "Render/MnShaderPathInstance.h"
#include "Render/MnLightSource.h"
#include "Render/MnMaterial.h"
#include "Render/MnSkeleton.h"
#include "Render/MnCustomRenderTarget.h"

namespace MNL
{
	class Renderer : public MnWorldComponent
	{
		struct _BackBufferShaderVertex
		{
			DirectX::SimpleMath::Vector3 position;
		};
	public:
		Renderer();
		~Renderer();

		/**
		@brief �ش� ���� �����쿡 ���� �������Ѵ�.
		@param pRenderWindow ���� ������ �� ���� ������
		*/
		void Render(const MnRenderWindow& renderWindow);
	
	private:
		void _Init();
		void _RenderToBackBuffer(const std::shared_ptr<MnCustomRenderTarget>& spRenderTarget, const MnRenderWindow& renderWindow);
		
	private:
		MnShaderPathInstance m_backBufferShader;
		MnVertexBuffer m_vertexBuffer;
		MnInputLayout m_inputLayout;
		MnIndexBuffer m_indexBuffer;
	};
}
