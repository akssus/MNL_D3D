/**
@class ForwardShader
@brief MNL에 기본 탑재된 포워드 셰이더.
@author Akssus
@section 개요
하.... 셰이더 하나 만드는건 엄청 큰 사업임;;\n
\n

@section 상수버퍼 명세
레지스터 인덱스, 용도, 바인딩 스테이지 \n
b0 : 월드변환, VS \n
b1 : 뷰 프로젝션, VS \n
b2 : 라이트, VS & PS \n
b3 : 머테리얼, PS \n
b4 : 본팔레트, VS \n

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