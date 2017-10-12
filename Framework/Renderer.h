/**
@class Renderer
@brief 렌더러 게임 오브젝트 컴포넌트의 베이스 클래스
@author Aksuss
@section 개요
렌더러의 사양은 고정이다.\n
월드로부터 얻어오는 정보 : 라이트, 카메라의 뷰프로젝션, 셰이더 \n
오브젝트로부터 얻어오는 정보 : 월드변환, 머테리얼, 텍스쳐, 메시, 본팔레트 \n
이상의 정보를 규합해서 상수버퍼를 갱신하고 드로우콜하는 책임을 지닌다.\n
각 상수버퍼의 레지스터 인덱스는 미리 정해져 있으므로 추가 상수버퍼가 필요할 경우 셰이더측에서 미리 할당되지 않은 인덱스에 상수버퍼를 업데이트 해야한다.\n
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
