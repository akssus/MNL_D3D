/**
@class ForwardShader
@brief MNL�� �⺻ ž��� ������ ���̴�.
@author Akssus
@section ����
��.... ���̴� �ϳ� ����°� ��û ū �����;;\n
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
#include <d3d11.h>
#include "DXTK\SimpleMath.h"
#include "Shader.h"
#include "MnWorldTransformBuffer.h"
#include "MnViewProjectionTransformBuffer.h"
#include "MnLightBuffer.h"
#include "MnMaterialBuffer.h"
#include "MnBonePaletteBuffer.h"
#include "Render\MNL_Render.h"

namespace MNL
{
	class ForwardShader : public Shader
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

	public:
		ForwardShader();
		~ForwardShader();

		void SetWorldBuffer(const DirectX::SimpleMath::Matrix& matWorld);
		void SetViewProjectionBuffer(const DirectX::SimpleMath::Matrix& matView, const DirectX::SimpleMath::Matrix& matProjection);
		void SetLightBuffer(const std::shared_ptr<MnLightSource> spLight);
		void SetMaterial(const std::shared_ptr<MnMaterial> spMaterial);
		void SetBonePalette(const std::shared_ptr<MnSkeleton> spSkeleton);

		virtual void Render(const CPD3DShaderResourceView& prevRenderedScene);
	private:
		void _Init();
		HRESULT _InitShaders();
		HRESULT _InitConstantBuffers();

	private:
		std::shared_ptr<MnShaderPathInstance> m_spShaderPath;

		std::shared_ptr<MnWorldTransformBuffer> m_spWorldBuffer;
		std::shared_ptr<MnViewProjectionTransformBuffer> m_spViewProjectionBuffer;
		std::shared_ptr<MnLightBuffer> m_spLightBuffer;
		std::shared_ptr<MnMaterialBuffer> m_spMaterialBuffer;
		std::shared_ptr<MnBonePaletteBuffer> m_spBonePaletteBuffer;
	};
}