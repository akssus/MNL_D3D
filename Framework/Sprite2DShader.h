#pragma once
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Shader.h"
#include "Core/MnVertexBuffer.h"
#include "Render/MnShaderPathInstance.h"
#include "MnWorldTransformBuffer.h"
#include "MnViewProjectionTransformBuffer.h"

namespace MNL
{

	class Sprite2DShader : public Shader
	{
		struct _VertexType
		{
			DirectX::SimpleMath::Vector3 position;
			DirectX::SimpleMath::Vector2 texCoord;
		};
	public:
		Sprite2DShader();
		~Sprite2DShader();

		virtual void OnAttatched();

		void SetScreenSize(float width, float height);
		virtual void Render(const std::shared_ptr<MnCustomRenderTarget>& prevRenderedScene);

	private:
		void _Init();
		void _CalcProjection();

	private:
		MnShaderPathInstance m_shaderPath;
		MnVertexBuffer m_vertexBuffer; ///< ÅØ½ºÃÄ ·»´õ¿ë Äõµå¸Þ½¬ ¹öÅØ½º
		MnIndexBuffer m_indexBuffer; ///< ÅØ½ºÃÄ ·»´õ¿ë Äõµå¸Þ½¬ ÀÎµ¦½º
		MnWorldTransformBuffer m_worldBuffer;
		MnViewProjectionTransformBuffer m_viewProjectionBuffer;

		float m_screenWidth;
		float m_screenHeight;
		DirectX::SimpleMath::Matrix m_projection;
	};

}