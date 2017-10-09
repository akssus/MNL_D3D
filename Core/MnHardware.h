/**
@class MNL::MnHardware
@author Akssus
@brief 비디오 어댑터 및 디스플레이 장치 관리.

@section 개요
MnHardware는 MnD3DDevice를 생성하기 전 컴퓨터의 비디오 하드웨어 정보를 얻어오기 위한 객체이다.\n\n
MnHardware는 MnVideoAdapter와 MnDisplayDevice를 통해 비디오 출력 관련 장치(비디오카드 및 모니터)의 정보를 저장, 관리한다.\n\n
MnHardware는 MnDisplayDevice를 직접적으로 멤버로 가지지 않으며\n\n
MnHardware - MnVideoAdapter - MnDisplayDevice \n
1......n                         1.....n \n\n
의 관계를 가진다.\n
이렇게 구조화된 이유는 한 대의 컴퓨터에서 여러개의 비디오카드를 가질 수 있고 (통상 한개지만)
각 비디오카드는 여러대의 모니터에 출력할 수 있기 때문이다.\n
특히 요즘은 듀얼 모니터 이상이 많아서 이에 대한 관리는 불가피한 듯 하다.
*/

#pragma once
#include <d3d11.h>
#include <vector>
#include "MnTypedefs.h"
#include "MnVideoAdapter.h"
#include "MnDisplayDevice.h"

namespace MNL
{
	class MnHardware
	{
	public:
		MnHardware();
		~MnHardware();

		/** 
		@brief 장치 정보를 얻어와 초기화 한다.
		@return 초기화 성공 여부.
		*/
		HRESULT	Init();

		/**
		@brief 비디오 어댑터의 개수를 얻어온다.
		*/
		UINT GetNumVideoAdapters() const;
		/**
		@brief 컨테이너 내의 MnVideoAdapter를 얻어온다.
		@param index 비디오 어댑터의 인덱스
		@warning Out of index 동작시 크래시 발생
		*/
		const MnVideoAdapter GetVideoAdapter(UINT index) const;

		/**
		@brief GPU가 지원하는 최대 피쳐 레벨을 얻는다.
		@return 최소 D3D_FEATURE_LEVEL_9_1가 반환된다.
		*/
		D3D_FEATURE_LEVEL GetMaxSupportedFeatrueLevel(UINT adapterIndex) const;
		

	private:
		std::vector<MnVideoAdapter>		m_videoAdapters; ///< 초기화된 비디오 어댑터 장치가 저장되는 컨테이너
	};
}
